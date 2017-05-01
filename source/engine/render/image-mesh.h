// ============
// image-mesh.h
// ============

#ifndef IMAGEMESH_H
#define IMAGEMESH_H

#include "../utils/utils.h"

#include <GL/glew.h>

#include <vector>

namespace render
{
	class ImageMesh
	{
	public:
		ImageMesh();
		ImageMesh(unsigned int id);
		~ImageMesh();

		void update(int posX, int posY, unsigned int sizeX, unsigned int sizeY);
		void draw();

	private:
		const unsigned int _NUM_VBOS = 3;

		GLuint _posVBO;
		GLuint _texVBO;
		GLuint _indVBO;

		std::vector<utils::Vec2f> _pos;
		std::vector<utils::Vec2f> _tex;
		std::vector<unsigned int> _ind;
	};
}

#endif
