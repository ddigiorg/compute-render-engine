// ==========
// camera.cpp
// ==========

#include "camera.h"

#include <iostream>

using namespace render;

Camera::Camera()
{

}

Camera::Camera(Projection proj, const unsigned int window_width, const unsigned int window_height)
{
	_viewMatrix.resize(16);
	_projMatrix.resize(16);

	setViewMatrix();

	setProjMatrix2D((float)window_width, (float)window_height);
}

Camera::~Camera()
{

}

void Camera::setViewMatrix()
{
	_viewMatrix[0] = 1.0; // scale x
	_viewMatrix[1] = 0.0;
	_viewMatrix[2] = 0.0;
	_viewMatrix[3] = 0.0;

	_viewMatrix[4] = 0.0;
	_viewMatrix[5] = 1.0; // scale y
	_viewMatrix[6] = 0.0;
	_viewMatrix[7] = 0.0;

	_viewMatrix[8] = 0.0;
	_viewMatrix[9] = 0.0;
	_viewMatrix[10] = 1.0; // scale z
	_viewMatrix[11] = 0.0;

	_viewMatrix[12] = 0.0; // x
	_viewMatrix[13] = 0.0; // y
	_viewMatrix[14] = 0.0; // z
	_viewMatrix[15] = 1.0;
}

void Camera::setViewMatrixPos(float x, float y, float z)
{
	_viewMatrix[12] = x;
	_viewMatrix[13] = y;
	_viewMatrix[14] = z;
}

void Camera::setProjMatrix2D(const float& r, const float& b)
{
	const float l = 0.0f;
	const float t = 0.0f;
	const float n = -1.0f;
	const float f = 1.0f;

	_projMatrix[0] = 2.0f / (r - l);
	_projMatrix[1] = 0.0f;
	_projMatrix[2] = 0.0f;
	_projMatrix[3] = 0.0f;

	_projMatrix[4] = 0.0f;
	_projMatrix[5] = 2.0f / (t - b);
	_projMatrix[6] = 0.0f;
	_projMatrix[7] = 0.0f;

	_projMatrix[8] = 0.0f;
	_projMatrix[9] = 0.0f;
	_projMatrix[10] = -2.0f / (f - n);
	_projMatrix[11] = 0.0f;

	_projMatrix[12] = -(r + l) / (r - l); 
	_projMatrix[13] = -(t + b) / (t - b); 
	_projMatrix[14] = -(f + n) / (f - n); 
	_projMatrix[15] = 1.0f;
}
