#include "ch4manyspinningcubes.h"
#include "shadercreator.h"

#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

glm::mat4 Ch4ManySpinningCubes::proj_matrix{ glm::perspective(50.0f, (float)1024 / (float)720, 0.1f, 1000.0f) };

Ch4ManySpinningCubes::Ch4ManySpinningCubes() : window{ glfwCreateWindow(1024, 720, "Many Spinning Cubes", nullptr, nullptr) } {
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW window failed to initialize.");
	}

	glfwMakeContextCurrent(window);
	/* swap buffers once per frame */
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	GLenum err{ glewInit() };
	if (err != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
	}
}

void Ch4ManySpinningCubes::run(void) {
	rendering_program = glCreateProgram();
	ShaderCreator::attach_shader(GL_VERTEX_SHADER, ".\\Shader Files\\Chapter 4\\spinningcube.vert", rendering_program);
	ShaderCreator::attach_shader(GL_FRAGMENT_SHADER, ".\\Shader Files\\Chapter 4\\spinningcube.frag", rendering_program);

	mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_location = glGetUniformLocation(rendering_program, "proj_matrix");

	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	static const GLfloat vertex_positions[]{
		-0.25f,  0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		 0.25f, -0.25f, -0.25f,

		 0.25f, -0.25f, -0.25f,
		 0.25f,  0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f,

		 0.25f, -0.25f, -0.25f,
		 0.25f, -0.25f,  0.25f,
		 0.25f,  0.25f, -0.25f,

		 0.25f, -0.25f,  0.25f,
		 0.25f,  0.25f,  0.25f,
		 0.25f,  0.25f, -0.25f,

		 0.25f, -0.25f,  0.25f,
		-0.25f, -0.25f,  0.25f,
		 0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f,
		-0.25f,  0.25f,  0.25f,
		 0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f,
		-0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f,
		 0.25f, -0.25f,  0.25f,
		 0.25f, -0.25f, -0.25f,

		 0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f, -0.25f,
		-0.25f, -0.25f,  0.25f,

		-0.25f,  0.25f, -0.25f,
		 0.25f,  0.25f, -0.25f,
		 0.25f,  0.25f,  0.25f,

		 0.25f,  0.25f,  0.25f,
		-0.25f,  0.25f,  0.25f,
		-0.25f,  0.25f, -0.25f
	};

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* render loop */
	while (!glfwWindowShouldClose(window)) {
		static const GLfloat green[]{ 0.0f, 0.25f, 0.0f, 1.0f };
		static const GLfloat one = 1.0f;

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
		glClearBufferfv(GL_COLOR, 0, green);
		glClearBufferfv(GL_DEPTH, 0, &one);

		glUseProgram(rendering_program);

		glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(Ch4ManySpinningCubes::proj_matrix));

		for (int i = 0; i != 24; ++i) {
			float f{ (float)i + (float)glfwGetTime() * 0.3f };
			glm::mat4 mv_matrix{ glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)) *
				glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(21.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::translate(glm::mat4(1.0f), glm::vec3(sinf(2.1f * f) * 2.0f, cosf(1.7f * f) * 2.0f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f)) };

			glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Ch4ManySpinningCubes::window_size_callback(GLFWwindow* window, int width, int height) {
	float aspect{ (float)width / (float)height };
	Ch4ManySpinningCubes::proj_matrix = glm::perspective(50.0f, aspect, 0.1f, 1000.0f);
}

Ch4ManySpinningCubes::~Ch4ManySpinningCubes() {
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glDeleteBuffers(1, &buffer);
	glfwDestroyWindow(window);
}
