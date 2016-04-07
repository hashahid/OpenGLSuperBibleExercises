#pragma once

#include "exercisebase.h"

#include <glm\glm.hpp>
#include <glm\mat4x4.hpp>

class Ch4SpinningCube : protected ExerciseBase {
	GLFWwindow*			window;
	GLuint				rendering_program,
						vertex_array_object,
						buffer;
	GLint				mv_location,
						proj_location;
	glm::mat4			mv_matrix;
	static glm::mat4	Ch4SpinningCube::proj_matrix;
public:
	Ch4SpinningCube();
	void run(void) override;
	~Ch4SpinningCube();
private:
	static void window_size_callback(GLFWwindow* window, int width, int height);
};
