// ==========
// retina.cpp
// ==========

#include "engine/utils/utils.h"
#include "engine/input/input-video.h"
#include "engine/render/display.h"
#include "engine/render/camera.h"
#include "engine/render/shader.h"
#include "engine/render/vbo.h"
#include "engine/render/texture2D.h"
#include "engine/render/image-mesh.h"
#include "engine/compute/compute-system.h"
#include "engine/compute/compute-program.h"
#include "engine/compute/helpers.h"

#include <iostream>
#include <vector>

int main()
{
	// Define file name variables
	std::string videoFile = "resources/sample.avi";

	std::string test_vs = "source/apps/retina/retina.vs";
	std::string test_fs = "source/apps/retina/retina.fs";
	std::string test_cl = "source/apps/retina/retina.cl";

	// Define input variables
	input::InputVideo video(videoFile);
	unsigned int videoX = video.getWidth();
	unsigned int videoY = video.getHeight();

	// Define compute variables
	compute::ComputeSystem cs;
	compute::ComputeProgram cp;

	std::vector<cl::Memory> clMemory(2);
	cl::ImageGL clTex2D_input;
	cl::ImageGL clTex2D_retinaBW;

	cl::NDRange clGlobalNDRange(videoX, videoY);
	cl::Kernel clKernel_retina;

	// Define render variables
	const unsigned int DISPLAY_X = 1000;
	const unsigned int DISPLAY_Y = 800;

	render::Display glDisplay(DISPLAY_X, DISPLAY_Y, "Retina App");
	render::Camera glCamera(render::Camera::_2D, DISPLAY_X, DISPLAY_Y);
	render::Shader glShader(test_vs, test_fs);
	render::ImageMesh glImageMesh_input(0);
	render::ImageMesh glImageMesh_retinaBW(1);
	render::Texture2D glTex2D_input(0);
	render::Texture2D glTex2D_retinaBW(1);

	// Initialize compute system
	cs.init(compute::ComputeSystem::_gpu);

	// Initialize OpenGL image locations and sizes
	unsigned int MESH_X = videoX; // controls image X size
	unsigned int MESH_Y = videoY; // controls image Y size

	glImageMesh_input.update(10, 30, MESH_X, MESH_Y);
	glImageMesh_retinaBW.update(10, 30 + MESH_Y + 10, MESH_X, MESH_Y);
	//glImageMesh_retinaBW.update(10 + MESH_X + 10, 30, MESH_X, MESH_Y);

	// Initialize OpenGL textures
	glTex2D_input.nullRGBA32F(videoX, videoY);
	glTex2D_retinaBW.nullRG32F(videoX, videoY);

	// Initialize OpenCL textures from OpenGL textures
	clTex2D_input = compute::createBuffer2DGL(cs, glTex2D_input.getID());
	clTex2D_retinaBW = compute::createBuffer2DGL(cs, glTex2D_retinaBW.getID());

	// Initialize OpenCL memory vector
	clMemory[0] = clTex2D_input;
	clMemory[1] = clTex2D_retinaBW;

	// Load compute kernels from compute program
	cp.loadProgramFromSourceFile(cs, test_cl);

	// Print OpenCV, OpenGL, and OpenCL information
	video.printInfo();
	glDisplay.printGLInfo();
	cs.printCLInfo();

	// Compute and Render Loop
	while (glDisplay.isRunning())
	{
		// Input
		glTex2D_input.updateRGBA32F(videoX, videoY, video.getNextFramePixels());
		clTex2D_input = compute::createBuffer2DGL(cs, glTex2D_input.getID());
		clMemory[0] = clTex2D_input;

		clKernel_retina = cl::Kernel(cp.getProgram(), "getRetinaOutput");
		clKernel_retina.setArg(0, clMemory[0]);
		clKernel_retina.setArg(1, clMemory[1]);
		cs.getQueue().finish();

		// Compute

		// OpenCL Aquires Texture from OpenGL
		cs.getQueue().enqueueAcquireGLObjects(&clMemory, NULL);
		cs.getQueue().finish();

		// Execute the kernel program on the Compute System
		cs.getQueue().enqueueNDRangeKernel(clKernel_retina, cl::NullRange, clGlobalNDRange);
		cs.getQueue().finish();

		// OpenCL Releases Texture to OpenGL
		cs.getQueue().enqueueReleaseGLObjects(&clMemory, NULL);
		cs.getQueue().finish();

		// Render
		glShader.bind();
		glShader.update(glCamera.getViewMatrix(), glCamera.getProjMatrix());

		glDisplay.clear(0.0f, 0.0f, 0.0f, 1.0f);

		glTex2D_input.bind();
		glImageMesh_input.draw();

		glTex2D_retinaBW.bind();
		glImageMesh_retinaBW.draw();

		glDisplay.drawFPS();
		glDisplay.run();
		glDisplay.handleUserInput();
	}
}