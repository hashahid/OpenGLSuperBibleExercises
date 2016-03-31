#pragma once

#include <GL\glew.h>
#include <string>

class ShaderCreator {
public:
	static void attach_shader(GLenum shader_type, const char *shader_filename, GLuint program);
private:
	static std::string read_shader_file(const char *filename);
};
