#include "include/material_lib/material.hpp"

#include <raymath.h>

#include <string>
#include <sstream>
#include <vector>

#define GLSL_VERSION            330

void Renderer::DrawSelf() {

    // here create shader
    // initialize it
    // and before blur and normalize maps

    Camera camera = { 0 };
    camera.position = Vector3{ 3.0f, 3.0f, 3.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    Shader shader = LoadShader(0, TextFormat("D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/texture_blending.frag", GLSL_VERSION));

    
    if (!IsShaderReady(shader)) {
        throw std::exception("cant compile a shader");
    }

    /*model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textures[0];
    model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = textures[1];
    model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = textures[2];*/

    // i have only images but i need textures



    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture3"), textures[0]);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture4"), textures[1]);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture5"), textures[2]);

    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture6"), masks[0]);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture7"), masks[1]);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture8"), masks[2]);

    model.materials[0].shader = shader;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        /*DrawTexture(masks[0], 0, 0, WHITE);
        DrawTexture(masks[1], 250, 250, WHITE);
        DrawTexture(masks[2], 512, 512, WHITE);*/
        BeginMode3D(camera);
        DrawModel(model, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }
}

Renderer::Renderer() {
    InitWindow(kWindowWidth, kWindowHeight, "grid landscape");
    for (int i_text = 0; i_text < kNumOfTextureBinds; i_text++) {
        textures[i_text] = LoadTextureFromImage(GenImageColor(1, 1, BLANK));
        masks[i_text] = LoadTextureFromImage(GenImageColor(1, 1, BLANK));
    }
}
Renderer::~Renderer() {
    UnloadShader(shader); // Unload shader
    for (int text_ind = 0; text_ind < kNumOfTextureBinds; ++text_ind) {
        UnloadTexture(textures[text_ind]);
        UnloadTexture(masks[text_ind]);
    }
    UnloadModel(model);
    CloseWindow();
}

// load data from files and upload to vram
void Renderer::SetMesh(std::string path) {

    //model = LoadModel(path.c_str());
    model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
    if (model.meshCount != 1) {
        throw std::exception("cant load mesh file");
    }

}

void Renderer::SetTexture(int ind, std::string path) {

    if (ind < 0 || ind > 2)
        throw std::exception("wrong texture index");

    Image img = LoadImage(path.c_str());

    if (!IsImageReady(img)) {
        throw std::exception("cant load a texture");
    }

    textures[ind] = LoadTextureFromImage(img);

}

void Renderer::SetMask(int ind, std::string path) {
    if (ind < 0 || ind > 2)
        throw std::exception("wrong texture index");

    Image img = LoadImage(path.c_str());
    //ImageColorGrayscale(&img);

    //ImageBlurGaussian(&img, 1);

    if (!IsImageReady(img)) {
        throw std::exception("cant load a mask texture");
    }

    masks[ind] = LoadTextureFromImage(img);

}
