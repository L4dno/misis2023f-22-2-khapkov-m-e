#include <raylib.h>
//#define GRAPHICS_API_OPENGL_43
//rlGetVersion
#include <rlgl.h>

#include <iostream>

int main() {

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "show triangle");
	rlViewport(0, 0, 800, 600);		

	SetTargetFPS(60);
	//std::cout << "\n" << rlGetVersion() << "\n";
	while (!WindowShouldClose()) {

		

	}

	return 0;
}