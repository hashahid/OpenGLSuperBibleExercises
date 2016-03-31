#pragma once

#include "exercisebase.h"

class Ch2Triangle : protected ExerciseBase {
	GLFWwindow* window;
	GLuint rendering_program, vertex_array_object;
public:
	Ch2Triangle();
	void run(void) override;
	~Ch2Triangle();
};
