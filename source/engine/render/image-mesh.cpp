// ==============
// image-mesh.cpp
// ==============

#include "image-mesh.h"
#include <iostream>

using namespace render;

ImageMesh::ImageMesh(unsigned int id)
{
	_posVBO = 0 + id * _NUM_VBOS;
	_texVBO = 1 + id * _NUM_VBOS;
	_indVBO = 2 + id * _NUM_VBOS;

	glGenBuffers(1, &_posVBO);
	glGenBuffers(1, &_texVBO);
	glGenBuffers(1, &_indVBO);

	_pos.resize(4);
	_tex.resize(4);
	_ind.resize(6);

	_tex[0] = utils::Vec2f(0.0f, 0.0f); // Top Left Vertex
	_tex[1] = utils::Vec2f(1.0f, 0.0f); // Top Right Vertex
	_tex[2] = utils::Vec2f(1.0f, 1.0f); // Bottom Right Vertex
	_tex[3] = utils::Vec2f(0.0f, 1.0f); // Bottom Left Vertex

	_ind = {
		0, 1, 3,  // Upper Left Triangle
		1, 2, 3}; // Lower Right Triangle
}

ImageMesh::~ImageMesh()
{
	glDeleteBuffers(1, &_posVBO);
	glDeleteBuffers(1, &_texVBO);
	glDeleteBuffers(1, &_indVBO);
}

void ImageMesh::update(int posX, int posY, unsigned int sizeX, unsigned int sizeY)
{
	_pos[0] = utils::Vec2f(posX        , posY        ); // Top Left Vertex
	_pos[1] = utils::Vec2f(posX + sizeX, posY        ); // Top Right Vertex
	_pos[2] = utils::Vec2f(posX + sizeX, posY + sizeY); // Bottom Right Vertex
	_pos[3] = utils::Vec2f(posX        , posY + sizeY); // Bottom Left Vertex

	// VBO XY Mesh Positions
	glBindBuffer(GL_ARRAY_BUFFER, _posVBO);
		glBufferData(GL_ARRAY_BUFFER, _pos.size() * sizeof(utils::Vec2f), &_pos[0], GL_STATIC_DRAW);

	// VBO UV Texture Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, _texVBO);
		glBufferData(GL_ARRAY_BUFFER, _tex.size() * sizeof(utils::Vec2f), &_tex[0], GL_STATIC_DRAW);

	// VBO Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _ind.size() * sizeof(unsigned int), &_ind[0], GL_STATIC_DRAW);

	// Unbind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ImageMesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _posVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _texVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indVBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
