// =======
// vbo.cpp
// =======

#include "vbo.h"

using namespace render;

VBO::VBO()
{
	glGenBuffers(1, &_buffer);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &_buffer);
}

void VBO::loadFloats(std::vector<utils::Vec2f>& data)
{
	_drawCount = data.size();

	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(utils::Vec2f), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::drawPoints()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_POINTS, 0, _drawCount);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
