#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class ExerciseBase {
public:
	ExerciseBase();
	virtual void run(void) = 0;
	virtual ~ExerciseBase();
protected:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static void error_callback(int error, const char* description);
};
