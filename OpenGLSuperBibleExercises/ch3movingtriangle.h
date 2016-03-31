#pragma once

#include "exercisebase.h"

class Ch3MovingTriangle : protected ExerciseBase {
	GLFWwindow* window;
	GLuint rendering_program, vertex_array_object;
public:
	Ch3MovingTriangle();
	void run(void) override;
	~Ch3MovingTriangle();
};
