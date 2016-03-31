#include "exercisebase.h"
#include <iostream>

void ExerciseBase::error_callback(int error, const char* description) {
	std::cerr << description << '\n';
}

void ExerciseBase::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

ExerciseBase::ExerciseBase() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		throw std::runtime_error("GLFW failed to initialize.");
}

ExerciseBase::~ExerciseBase() {
	glfwTerminate();
}
