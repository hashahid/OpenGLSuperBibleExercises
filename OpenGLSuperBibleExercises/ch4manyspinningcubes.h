#pragma once

#include "exercisebase.h"

#include <glm\glm.hpp>
#include <glm\mat4x4.hpp>

class Ch4ManySpinningCubes : protected ExerciseBase {
	GLFWwindow*			window;
	GLuint				rendering_program,
		vertex_array_object,
		buffer;
	GLint				mv_location,
		proj_location;
	static glm::mat4	Ch4ManySpinningCubes::proj_matrix;
public:
	Ch4ManySpinningCubes();
	void run(void) override;
	~Ch4ManySpinningCubes();
private:
	static void window_size_callback(GLFWwindow* window, int width, int height);
};
