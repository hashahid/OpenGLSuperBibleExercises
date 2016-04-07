#include "ch2triangle.h"
#include "shadercreator.h"

Ch2Triangle::Ch2Triangle() : window {glfwCreateWindow(640, 480, "Simple Triangle", nullptr, nullptr)} {
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW window failed to initialize.");
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
	}
}

void Ch2Triangle::run(void) {
	rendering_program = glCreateProgram();
	ShaderCreator::attach_shader(GL_VERTEX_SHADER, ".\\Shader Files\\Chapter 2\\triangle.vert", rendering_program);
	ShaderCreator::attach_shader(GL_FRAGMENT_SHADER, ".\\Shader Files\\Chapter 2\\triangle.frag", rendering_program);

	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	/* render loop */
	while (!glfwWindowShouldClose(window)) {
		const GLfloat color[] {0.0f, 0.2f, 0.0f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(rendering_program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Ch2Triangle::~Ch2Triangle() {
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glfwDestroyWindow(window);
}
