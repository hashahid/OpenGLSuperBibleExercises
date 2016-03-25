#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

using namespace std;

static void error_callback(int error, const char* description) {
	cerr << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint compile_shaders(void) {
	static const GLchar * vertex_shader_source[] = {
		"#version 450 core													\n"
		"void main(void) {													\n"
		"	const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),	\n"
		"									 vec4(-0.25, -0.25, 0.5, 1.0),	\n"
		"									 vec4( 0.25,  0.25, 0.5, 1.0));	\n"
		"	gl_Position = vertices[gl_VertexID];							\n"
		"}																	\n"
	};
	static const GLchar * fragment_shader_source[] = {
		"#version 450 core													\n"
		"out vec4 color;													\n"
		"void main(void) {													\n"
		"	color = vec4(0.0, 0.8, 1.0, 1.0);								\n"
		"}																	\n"
	};

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}

void startup(void) {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);
}

void shutdown(GLuint vao, GLuint program, GLFWwindow* window) {
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(program);
	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

int main(void) {
	startup();

	GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << glewGetErrorString(err);
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	GLuint rendering_program = compile_shaders();

	GLuint vertex_array_object;
	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	while (!glfwWindowShouldClose(window)) {
		const GLfloat color[] { 0.0f, 0.2f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(rendering_program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shutdown(vertex_array_object, rendering_program, window);
}
