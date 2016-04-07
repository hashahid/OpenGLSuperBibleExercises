#include "shadercreator.h"
#include <fstream>

std::string ShaderCreator::read_shader_file(const char *filename) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	std::string err {"Failed to read shader file "};
	throw std::runtime_error(err + filename);
}

void ShaderCreator::attach_shader(GLenum shader_type, const char *shader_filename, GLuint program) {
	/* read in source and create shader object */
	std::string shader_source {read_shader_file(shader_filename)};
	GLuint shader = glCreateShader(shader_type);

	/* attach source to shader and compile */
	const GLchar *source {(const GLchar *)shader_source.c_str()};
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	/* error check shader compilation */
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		throw std::runtime_error("Error in shader compilation.");

	/* attach shaders to the program and link */
	glAttachShader(program, shader);
	glLinkProgram(program);

	/* error check shader linking */
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
		throw std::runtime_error("Error in linking shader program.");

	glDeleteShader(shader);
}
