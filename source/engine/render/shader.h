// ========
// shader.h
// ========

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <vector>

namespace render
{
	class Shader
	{
	public:
		Shader();
		Shader(std::string& file_name_vs, std::string& file_name_fs);
		~Shader();

		void bind();
		void unbind();
		void update(std::vector<float> viewMatrix, std::vector<float> projMatrix);

	private:
		enum shader
		{
			VS,
			FS
		};

		GLuint _program;
		GLuint _shaders[2];
		GLuint _uniforms[2];

		std::string loadShader(const std::string& fileName);
		GLuint createShader(const std::string& text, unsigned int type);
		void linkProgram();
	};
}

#endif
