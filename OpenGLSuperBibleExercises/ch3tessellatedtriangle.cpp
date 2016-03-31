#include "ch3tessellatedtriangle.h"
#include "shadercreator.h"

Ch3TessellatedTriangle::Ch3TessellatedTriangle() : window{ glfwCreateWindow(640, 480, "Tessellated Triangle", nullptr, nullptr) } {
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW window failed to initialize.");
	}
}

void Ch3TessellatedTriangle::run(void) {
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	rendering_program = glCreateProgram();
	ShaderCreator::attach_shader(GL_VERTEX_SHADER, ".\\Shader Files\\Chapter 2\\triangle.vert", rendering_program);
	ShaderCreator::attach_shader(GL_TESS_CONTROL_SHADER, ".\\Shader Files\\Chapter 3\\tessellatedtriangle.tesc", rendering_program);
	ShaderCreator::attach_shader(GL_TESS_EVALUATION_SHADER, ".\\Shader Files\\Chapter 3\\tessellatedtriangle.tese", rendering_program);
	ShaderCreator::attach_shader(GL_GEOMETRY_SHADER, ".\\Shader Files\\Chapter 3\\tessellatedtriangle.geom", rendering_program);
	ShaderCreator::attach_shader(GL_FRAGMENT_SHADER, ".\\Shader Files\\Chapter 2\\triangle.frag", rendering_program);

	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	/* render loop */
	while (!glfwWindowShouldClose(window)) {
		static const GLfloat green[] { 0.0f, 0.25f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, green);

		glUseProgram(rendering_program);

		glPointSize(5.0f);

		glDrawArrays(GL_PATCHES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Ch3TessellatedTriangle::~Ch3TessellatedTriangle() {
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glfwDestroyWindow(window);
}
