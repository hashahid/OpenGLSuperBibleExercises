#include "ch2triangle.h"
#include "ch3movingtriangle.h"
#include "ch3tessellatedtriangle.h"
#include "ch4spinningcube.h"
#include "ch4manyspinningcubes.h"
#include <iostream>

int main(void) {
	try {
		// Ch2Triangle app;
		// Ch3MovingTriangle app;
		// Ch3TessellatedTriangle app;
		// Ch4SpinningCube app;
		Ch4ManySpinningCubes app;
		app.run();
		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Runtime exception occurred: " << e.what() << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Unexpected exception occurred: " << e.what() << '\n';
	}
	return EXIT_FAILURE;
}
