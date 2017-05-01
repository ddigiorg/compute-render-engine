// =====
// vbo.h
// =====

#ifndef VBO_H
#define VBO_H

#include "../utils/utils.h"

#include <GL/glew.h>

#include <vector>

namespace render
{
	class VBO
	{
	public:
		VBO();
		~VBO();

		void loadFloats(std::vector<utils::Vec2f>& data);
		void drawPoints();

		unsigned int getID()
		{
			return _buffer;
		}

	private:
		GLuint _buffer;

		unsigned int _drawCount;
	};
}

#endif
