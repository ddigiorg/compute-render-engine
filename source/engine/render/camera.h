// ========
// camera.h
// ========

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

#include <vector>

namespace render
{
	class Camera
	{
	public:
		enum Projection {_2D, _3D};

		Camera();
		Camera(Projection proj, const unsigned int windowWidth, const unsigned int windowHeight);
		~Camera();

		const std::vector<float>& getViewMatrix()
		{
			return _viewMatrix;
		}
	
		const std::vector<float>& getProjMatrix()
		{
			return _projMatrix;
		}

	private:
		std::vector<float> _viewMatrix;
		std::vector<float> _projMatrix;

		void setViewMatrix();
		void setViewMatrixPos(float x, float y, float z);
		void setProjMatrix2D(const float& r, const float& b);
	};
}

#endif
