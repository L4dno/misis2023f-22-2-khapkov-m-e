#include <material_lib/material.hpp>

#include <vector>
#include <string>


// test app
int main() {

    /*Renderer r;
    
    std::vector<std::string> textures = 
    { "D:/_Projects/misis2023f-22-2-khapkov-m-e/prj.cw/resources/grass.png", 
        "D:/_Projects/misis2023f-22-2-khapkov-m-e/prj.cw/resources/sand.png" };
    std::vector<int> map = { 0,1,0,1,0,1,0 };

    r.LoadMeshData("D:/_Projects/misis2023f-22-2-khapkov-m-e/prj.cw/resources/mesh_out/", 7);
    r.LoadTexturesData(textures);
    r.LoadHexToMaterialMap(map);

    r.DrawSelf();*/
    
    InitWindow(720, 480, "grid landscape");
    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_ORBITAL };
    Vector3 position = { 0.0f, 0.0f, -1.0f };

    Vector3 enemyBoxSize = { 2.0f, 2.0f, 2.0f };

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawCube(position, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, GRAY);
        //DrawModel(model, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }

    return 0;
}
