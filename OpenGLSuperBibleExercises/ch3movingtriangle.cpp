#include "ch3movingtriangle.h"
#include "shadercreator.h"

Ch3MovingTriangle::Ch3MovingTriangle() : window{ glfwCreateWindow(640, 480, "Moving Triangle", nullptr, nullptr) } {
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW window failed to initialize.");
	}
}

void Ch3MovingTriangle::run(void) {
	glfwMakeContextCurrent(window);
	/* swap buffers once per frame */
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	rendering_program = glCreateProgram();
	ShaderCreator::attach_shader(GL_VERTEX_SHADER, ".\\Shader Files\\Chapter 3\\movingtriangle.vert", rendering_program);
	ShaderCreator::attach_shader(GL_FRAGMENT_SHADER, ".\\Shader Files\\Chapter 2\\triangle.frag", rendering_program);

	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	/* render loop */
	while (!glfwWindowShouldClose(window)) {
		const GLfloat color[]{ (float)sin(glfwGetTime()) * 0.5f + 0.5f,
								(float)cos(glfwGetTime()) * 0.5f + 0.5f,
								0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(rendering_program);

		GLfloat attrib[]{ (float)sin(glfwGetTime()) * 0.5f,
						  (float)cos(glfwGetTime()) * 0.6f,
						  0.0f, 0.0f };
		glVertexAttrib4fv(0, attrib);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Ch3MovingTriangle::~Ch3MovingTriangle() {
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glfwDestroyWindow(window);
}
