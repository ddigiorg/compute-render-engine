// ===========
// texture2D.h
// ===========

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../utils/utils.h"

#include <GL/glew.h>

#include <vector>

namespace render
{
	class Texture2D
	{
	public:
		Texture2D();
		Texture2D(unsigned int id);
		~Texture2D();

		void nullR32F(unsigned int width, unsigned int height);
		void updateR32F(unsigned int width, unsigned int height, std::vector<float> pixels);

		void nullRG32F(unsigned int width, unsigned int height);
		void updateRG32F(unsigned int width, unsigned int height, std::vector<utils::Vec2f> pixels);

		void nullRGBA32F(unsigned int width, unsigned int height);
		void updateRGBA32F(unsigned int width, unsigned int height, std::vector<utils::Vec4f> pixels);

		void bind();
		void unbind();

		unsigned int getID()
		{
			return _texture;
		}

	private:
		GLuint _texture;

		void initTexture2D();
	};
}

#endif
