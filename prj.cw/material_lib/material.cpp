#include "include/material_lib/material.hpp"

#include <raymath.h>

#include <string>
#include <sstream>
#include <vector>


//void Renderer::BlendMasks() {
//    for (int i = 0; i < kNumOfTextureBinds; ++i) {
//        ApplyGaussianBlur(masks[i], 5, 0.5);
//    }
//    for (int im_y = 0; im_y < masks[0].height; ++im_y) {
//        for (int im_x = 0; im_x < masks[0].width; ++im_x) {
//            
//        }
//    }

// shader created by gpt

//void Renderer::DrawSelf() {
//
//    // here create shader
//    // initialize it
//    // and before blur and normalize maps
//
//    Camera camera = { 0 };
//    camera.position = Vector3{ 3.0f, 3.0f, 3.0f };
//    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
//    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
//    camera.fovy = 45.0f;
//    
//    Vector3 position = { 0.0f, 0.0f, 0.0f };
//
//    Shader shader = LoadShader(0, TextFormat("D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/texture_blending.fs", GLSL_VERSION));
//
//    // i have only images but i need textures
//
//    SetImageToShader("texture0", shader);
//
//    SetShaderValue(shader, GetShaderLocation(shader, "texture0"), &textures[0], SHADER_UNIFORM_SAMPLER2D);
//    SetShaderValue(shader, GetShaderLocation(shader, "texture1"), &textures[1], SHADER_UNIFORM_SAMPLER2D);
//    SetShaderValue(shader, GetShaderLocation(shader, "texture2"), &textures[2], SHADER_UNIFORM_SAMPLER2D);
//
//    SetShaderValue(shader, GetShaderLocation(shader, "weight0"), &masks[0], SHADER_UNIFORM_SAMPLER2D);
//    SetShaderValue(shader, GetShaderLocation(shader, "weight1"), &masks[1], SHADER_UNIFORM_SAMPLER2D);
//    SetShaderValue(shader, GetShaderLocation(shader, "weight2"), &masks[2], SHADER_UNIFORM_SAMPLER2D);
//
//    SetTargetFPS(60);
//    while (!WindowShouldClose()) {
//        UpdateCamera(&camera, CAMERA_FREE);
//
//        BeginDrawing();
//
//        ClearBackground(RAYWHITE);
//
//        BeginMode3D(camera);
//
//        BeginShaderMode(shader);
//
//        DrawModel(model, position, 1.0f, BLUE);
//
//        EndShaderMode();
//
//        EndMode3D();
//
//        EndDrawing();
//    }
//}

// shader created from raylib sample

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

    model.materials[0].shader = shader;
    // i have only images but i need textures

    

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        SetShaderValue(shader, GetShaderLocation(shader, "texture0"), &textures[0], SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(shader, GetShaderLocation(shader, "texture1"), &textures[1], SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(shader, GetShaderLocation(shader, "texture2"), &textures[2], SHADER_UNIFORM_SAMPLER2D);

        SetShaderValue(shader, GetShaderLocation(shader, "weight0"), &masks[0], SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(shader, GetShaderLocation(shader, "weight1"), &masks[1], SHADER_UNIFORM_SAMPLER2D);
        SetShaderValue(shader, GetShaderLocation(shader, "weight2"), &masks[2], SHADER_UNIFORM_SAMPLER2D);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(model, position, 1.0f, BLUE);

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

    model = LoadModel(path.c_str());

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

    if (!IsImageReady(img)) {
        throw std::exception("cant load a mask texture");
    }

    masks[ind] = LoadTextureFromImage(img);

}






