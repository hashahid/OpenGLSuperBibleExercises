#pragma once

#include "exercisebase.h"

class Ch3TessellatedTriangle : protected ExerciseBase {
	GLFWwindow* window;
	GLuint rendering_program, vertex_array_object;
public:
	Ch3TessellatedTriangle();
	void run(void) override;
	~Ch3TessellatedTriangle();
};
