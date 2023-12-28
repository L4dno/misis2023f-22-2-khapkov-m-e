#include "mesh_generator.hpp"
#include <raylib.h>

Mesh TranslateMesh(std::vector<Vertex> tmp) {
    Mesh mesh = { 0 };
    mesh.triangleCount = tmp.size() / 3;
    mesh.vertexCount = tmp.size();
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    for (int i = 0; i < tmp.size(); ++i) {
        mesh.vertices[i * 3] = tmp[i].x;
        mesh.vertices[i * 3 + 1] = tmp[i].y;
        mesh.vertices[i * 3 + 2] = 0;
    }
    UploadMesh(&mesh, false);
    return mesh;
}

void ShowMesh(Mesh m) {
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");

    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_PERSPECTIVE };

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    Model ter = LoadModelFromMesh(m);
    /*Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    ter.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;*/


    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        // drawing 3d shapes
        DrawModel(ter, position, 1.0f, WHITE);

        DrawGrid(10, 1.0);
        DrawLine3D({ 0,0,0 }, { 0,5.0f,0.0f }, GOLD);
        DrawLine3D({ 0,0,0 }, { 5.0f,0.0f,0.0f }, LIME);
        DrawLine3D({ 0,0,0 }, { 0,0.0f,5.0f }, RED);
        //DrawPoint3D({ 5.0f,5.0f,5.0f }, PURPLE);

        EndMode3D();

        EndDrawing();
    }
    UnloadModel(ter);
    CloseWindow();
}

int main() {
    Hexagon g({ 0,0 }, 10);
    auto mesh = g.GetMeshData();
    ShowMesh(TranslateMesh(mesh));
    return 0;
}