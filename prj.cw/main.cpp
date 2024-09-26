#include "include/material_lib/material.hpp"

//
//#include <material_lib/material.hpp>
//
//#include <vector>
//#include <string>



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

    

    int texture1Loc = GetShaderLocation(shader, "texture1");
    SetShaderValueTexture(shader, texture1Loc, textures[1]);

    int texture2Loc = GetShaderLocation(shader, "texture2");
    SetShaderValueTexture(shader, texture2Loc, textures[2]);

    //int texture3Loc = GetShaderLocation(shader, "texture3");
    //SetShaderValueTexture(shader, texture3Loc, texture3);

    int maskLoc = GetShaderLocation(shader, "mask0");
    SetShaderValueTexture(shader, maskLoc, mask);

    model.materials[0].shader = shader;
    model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = textures[0];

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);
        SetShaderValueTexture(shader, texture1Loc, textures[1]);
        SetShaderValueTexture(shader, texture2Loc, textures[2]);
        //SetShaderValueTexture(shader, texture3Loc, texture3);
        SetShaderValueTexture(shader, maskLoc, mask);
        DrawModel(model, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }
}

Renderer::Renderer() {
    InitWindow(kWindowWidth, kWindowHeight, "grid landscape");
    for (int i_text = 0; i_text < kNumOfTextureBinds; i_text++) {
        textures[i_text] = LoadTextureFromImage(GenImageColor(1, 1, BLANK));
        mask = LoadTextureFromImage(GenImageColor(1, 1, BLANK));
    }
}
Renderer::~Renderer() {
    UnloadShader(shader); // Unload shader
    for (int text_ind = 0; text_ind < kNumOfTextureBinds; ++text_ind) {
        UnloadTexture(textures[text_ind]);
        UnloadTexture(mask);
    }
    UnloadModel(model);
    CloseWindow();
}

// load data from files and upload to vram
void Renderer::SetMesh(std::string path) {

    model = LoadModel(path.c_str());
    // model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));
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
    GenTextureMipmaps(&textures[ind]);
    SetTextureFilter(textures[ind], TEXTURE_FILTER_TRILINEAR);
}

void Renderer::SetMask(std::string path) {

    Image img = LoadImage(path.c_str());
    //ImageColorGrayscale(&img);

    //ImageBlurGaussian(&img, 1);

    if (!IsImageReady(img)) {
        throw std::exception("cant load a mask texture");
    }

    mask = LoadTextureFromImage(img);
    SetTextureFilter(mask, TEXTURE_FILTER_BILINEAR);
}


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