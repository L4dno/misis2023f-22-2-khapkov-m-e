#include "include/material_lib/material.hpp"

#include <raymath.h>

#include <string>
#include <sstream>
#include <vector>

std::string Renderer::GetObjName(const std::string path, int mesh_ind) {
    std::ostringstream buffer;
    buffer << path << "mesh" << mesh_ind << ".obj";
    return buffer.str();
}

void Renderer::DrawSelf() {
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
        DrawModel(model, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }
}

Renderer::Renderer() {
    InitWindow(kWindowWidth, kWindowHeight, "grid landscape");
}
Renderer::~Renderer() {
    UnloadModel(model);
    // UnloadMeshes
    // Unload textures
    CloseWindow();
}

// load data from files and upload to vram
void Renderer::LoadMeshData(std::string path, int count) {

    model.meshCount = count;
    model.transform = MatrixIdentity();
    model.meshes = (Mesh*)MemAlloc(sizeof(Mesh) * model.meshCount);

    model.boneCount = 0;
    model.bones = NULL;
    model.bindPose = NULL;

    for (int i = 0; i < model.meshCount; ++i) {
        Model tmp = LoadModel(GetObjName(path, i).c_str());
        model.meshes[i] = tmp.meshes[0];
        //UploadMesh(&model.meshes[i], false);
    }

}

void Renderer::LoadTexturesData(std::vector<std::string> file_names) {

    model.materialCount = file_names.size();
    model.materials = (Material*)MemAlloc(sizeof(Material) * model.materialCount);

    for (int i = 0; i < model.materialCount; ++i) {
        model.materials[i] = LoadMaterialDefault();
        Image img = LoadImage(file_names[i].c_str());
        if (!IsImageReady(img)) {
            throw std::exception("cant load image");
        }
        Texture2D text = LoadTextureFromImage(img);
        UnloadImage(img);
        model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = text;
    }
}

void Renderer::LoadHexToMaterialMap(std::vector<int> hex_mat) {
    if (hex_mat.size() != model.meshCount) {
        throw std::exception("size of material map is different from mesh count");
    }
    model.meshMaterial = (int*)MemAlloc(sizeof(int) * model.meshCount);

    for (int i = 0; i < model.meshCount; ++i) {
        model.meshMaterial[i] = hex_mat[i];
    }
}






