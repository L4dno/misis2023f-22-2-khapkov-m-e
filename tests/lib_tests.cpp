#include "../prj.cw/material_lib/include/material_lib/material.hpp"

#include <raylib.h>
#include <rlgl.h>
#include <iostream>


int main() {

	
	Renderer rd;

	std::string pref = "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/";

	rd.SetMesh("D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/grid_mesh.obj");
	
	rd.SetTexture(0, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/snow.png");
	rd.SetTexture(1, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/grass.png");
	rd.SetTexture(2, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/sand.png");
	//rd.SetMask(0, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/heightmap.png");
	//rd.SetMask(0, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/mask.png");
	rd.SetMask(0, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/t.png");
	rd.SetMask(1, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/r.png");
	rd.SetMask(2, "D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/l.png");
	rd.DrawSelf();

	return 0;
}