// ==========
// shader.cpp
// ==========

#include "shader.h"

#include <iostream>
#include <fstream>

using namespace render;

Shader::Shader()
{

}

Shader::Shader(std::string& fileName_vs, std::string& fileName_fs)
{
	_program = glCreateProgram();
	_shaders[0] = createShader(loadShader(fileName_vs), GL_VERTEX_SHADER);
	_shaders[1] = createShader(loadShader(fileName_fs), GL_FRAGMENT_SHADER);

	glBindAttribLocation(_program, 0, "vertexXY"); // position coordinates
	glBindAttribLocation(_program, 1, "vertexUV"); // texture coordinates

	linkProgram();

	_uniforms[0] = glGetUniformLocation(_program, "viewMatrix");
	_uniforms[1] = glGetUniformLocation(_program, "projMatrix");
}

Shader::~Shader()
{
	glDetachShader(_program, _shaders[0]);
	glDeleteShader(_shaders[0]);

	glDetachShader(_program, _shaders[1]);
	glDeleteShader(_shaders[1]);

	glDeleteProgram(_program);
}

void Shader::bind()
{
	glUseProgram(_program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::update(const std::vector<float> viewMatrix, const std::vector<float> projMatrix)
{
	glUniformMatrix4fv(_uniforms[0], 1, GL_FALSE, &viewMatrix[0]);
	glUniformMatrix4fv(_uniforms[1], 1, GL_FALSE, &projMatrix[0]);
}

std::string Shader::loadShader(const std::string& fileName)
{
	std::ifstream file;

	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
		std::cerr << "[r] Unable to load shader: " << fileName << std::endl;

	return output;
}

GLuint Shader::createShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);	

	if(shader == 0)
		std::cerr << "[r] Error creating shader: " << type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	GLint isCompiled = 0;
	GLchar error[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << "[r] Error compiling shader: " << error <<  std::endl;
	}

	return shader;
}

void Shader::linkProgram()
{
	glAttachShader(_program, _shaders[0]);
	glAttachShader(_program, _shaders[1]);
	glLinkProgram(_program);

	GLint isLinked = 0;
	GLchar error[1024] = { 0 };

	glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		glGetProgramInfoLog(_program, sizeof(error), NULL, error);
		std::cerr << "[r] Error linking shaders:" << error << std::endl;
	}

	glValidateProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		glGetProgramInfoLog(_program, sizeof(error), NULL, error);
		std::cerr << "[r] Invalid shader program:" << error << std::endl;
	}
}
