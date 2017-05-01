// =============
// particles.cpp
// =============

#include "engine/utils/utils.h"
#include "engine/render/display.h"
#include "engine/render/camera.h"
#include "engine/render/shader.h"
#include "engine/render/vbo.h"
#include "engine/compute/compute-system.h"
#include "engine/compute/compute-program.h"
#include "engine/compute/helpers.h"

#include <iostream>
#include <vector>
#include <ctime>

const unsigned int DISPLAY_WIDTH = 800;
const unsigned int DISPLAY_HEIGHT = 600;

const unsigned int NUM_PARTICLES =  8000000; // gets ~55-60 FPS on GeForce GTX 750 Ti
//const unsigned int NUM_PARTICLES = 27000000; // gets ~55-60 FPS on GeForce GTX 1070

// File Names
std::string particles_vs = "source/apps/particles/particles.vs";
std::string particles_fs = "source/apps/particles/particles.fs";
std::string particles_cl = "source/apps/particles/particles.cl";

// Application Variables
std::vector<utils::Vec2f> positions(NUM_PARTICLES);
std::vector<utils::Vec2f> velocities(NUM_PARTICLES);
utils::Vec2i32 mousePos;
utils::Vec2i32 windowDims;

// Render Variables
render::Display glDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Particles App");
render::Camera glCamera(render::Camera::_2D, DISPLAY_WIDTH, DISPLAY_HEIGHT);
render::Shader glShader(particles_vs, particles_fs);
render::VBO glPositions;

// Compute Variables
compute::ComputeSystem cs;
compute::ComputeProgram cp;

std::vector<cl::Memory> clMemory(1);

cl::BufferGL clPositions;
cl::Buffer clVelocities;
cl::Buffer clMousePos;
cl::Buffer clWindowDims;

// OpenCL Kernel Variables
cl::NDRange globalNDRange;
cl::Kernel physicsKernel;

float randomFloat(float min, float max)
{
	float ran = (float) rand() / RAND_MAX;
	return min + (max - min) * ran;
}

int main()
{
	// Initialize Compute System and load kernel source file
	cs.init(compute::ComputeSystem::_gpu);
	cp.loadProgramFromSourceFile(cs, particles_cl);

	// Setup Render environment options
	glDisplay.setMousePosition(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	glDisplay.enableBlending();

	srand(time(NULL));

	// Initialize window dimensions for use in kernel
	windowDims.x = DISPLAY_WIDTH;
	windowDims.y = DISPLAY_HEIGHT;

	// Initialize vertex positions and velocities for use in kernel
	for(int i = 0; i < NUM_PARTICLES; i++)
	{
		positions[i].x = randomFloat(0.0f, (float)DISPLAY_WIDTH);
		positions[i].y = randomFloat(0.0f, (float)DISPLAY_HEIGHT);
		velocities[i].x = 0.0f;
		velocities[i].y = 0.0f;
	}

	glPositions.loadFloats(positions);

	size_t sizeVelocity = sizeof(utils::Vec2f) * NUM_PARTICLES;
	size_t sizeMousePos = sizeof(utils::Vec2i32);
	size_t sizeWindowDims = sizeof(utils::Vec2i32);

	// Load OpenCL buffers
	clPositions  = compute::createBuffer1DGL(cs, glPositions.getID());
	clVelocities = compute::createBuffer1D(cs, sizeVelocity);
	clMousePos   = compute::createBuffer1D(cs, sizeMousePos);
	clWindowDims = compute::createBuffer1D(cs, sizeWindowDims);

	// Push data to OpenCL buffers
	compute::writeBuffer1D(cs, clVelocities, sizeVelocity, &velocities[0]);
	compute::writeBuffer1D(cs, clWindowDims, sizeWindowDims, &windowDims);

	// Load OpenCL Kernel
	clMemory[0] = clPositions;

	physicsKernel = cl::Kernel(cp.getProgram(), "physics2D");

	physicsKernel.setArg(0, clMemory[0]);
	physicsKernel.setArg(1, clVelocities);
	physicsKernel.setArg(2, clMousePos);
	physicsKernel.setArg(3, clWindowDims);

	cs.getQueue().finish();

	// Print OpenGL and OpenCL Information
	glDisplay.printGLInfo();
	cs.printCLInfo();

	// Compute and Render Loop
	while (glDisplay.isRunning())
	{
		// Compute
		globalNDRange = cl::NDRange(NUM_PARTICLES);

		// Push OpenCL mouse position buffer to Compute Device
		mousePos = glDisplay.getMousePosition();
		compute::writeBuffer1D(cs, clMousePos, sizeMousePos, &mousePos);

		// OpenCL Aquires buffer from OpenGL
		cs.getQueue().enqueueAcquireGLObjects(&clMemory, NULL);
		cs.getQueue().finish();

		// Execute the kernel program on the Compute System
		cs.getQueue().enqueueNDRangeKernel(physicsKernel, cl::NullRange, globalNDRange);
		cs.getQueue().finish();

		// OpenCL Releases buffer to OpenGL
		cs.getQueue().enqueueReleaseGLObjects(&clMemory, NULL);
		cs.getQueue().finish();

		// Render
		glDisplay.handleUserInput();
		glShader.bind();
		glShader.update(glCamera.getViewMatrix(), glCamera.getProjMatrix());
		glDisplay.clear(0.0f, 0.0f, 0.06f, 1.0f);
		glPositions.drawPoints();
		glDisplay.drawFPS();
		glDisplay.run();
	}
}
