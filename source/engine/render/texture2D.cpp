// =============
// texture2D.cpp
// =============

#include "texture2D.h"

#include <iostream>

using namespace render;

Texture2D::Texture2D(unsigned int id)
{
	_texture = id;
	glGenTextures(1, &_texture);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_texture);
}

// R32F
void Texture2D::nullR32F(unsigned int width, unsigned int height)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
	unbind();
}

void Texture2D::updateR32F(unsigned int width, unsigned int height, std::vector<float> pixels)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, &pixels[0]);
	unbind();
}

// RG32F
void Texture2D::nullRG32F(unsigned int width, unsigned int height)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, NULL);
	unbind();
}

void Texture2D::updateRG32F(unsigned int width, unsigned int height, std::vector<utils::Vec2f> pixels)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, &pixels[0]);
	unbind();
}

// RGBA32F
void Texture2D::nullRGBA32F(unsigned int width, unsigned int height)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	unbind();
}

void Texture2D::updateRGBA32F(unsigned int width, unsigned int height, std::vector<utils::Vec4f> pixels)
{
	initTexture2D();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, &pixels[0]);
	unbind();
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
	glFinish();
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glFinish();
}

void Texture2D::initTexture2D()
{
	glDeleteTextures(1, &_texture);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
