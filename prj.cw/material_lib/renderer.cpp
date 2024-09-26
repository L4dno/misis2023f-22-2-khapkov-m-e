#include "include/material_lib/material.hpp"

#include <raymath.h>

#include <string>
#include <sstream>
#include <vector>

#define GLSL_VERSION            330


int main()
{
    InitWindow(1280, 800, "My terrain");


    TerrainSector sector;
    sector.Setup();

    // here we can change Image for Terraing gen
    // --------------------------------------------------------------------

    Image img = LoadImage("../sample/resources/terrain/terrain.png");
    //Image img = LoadImage("../sample/map_drawer/painting.png");
    sector.SetupImage(img);


    //---------------------------------------------------------------------

    // here we change mesh for drawing
    //------------------------------------------------------------------


    Mesh mesh = { 0 };
    sector.BuildMesh(mesh);


    // 
    //------------------------------------------------------------------

    UploadMesh(&mesh, false);

    Texture baseTexture = LoadTexture("../sample/resources/terrain/dirt.png");
    GenTextureMipmaps(&baseTexture);
    SetTextureFilter(baseTexture, TEXTURE_FILTER_TRILINEAR);

    Texture texture1 = LoadTexture("../sample/resources/terrain/grass.png");
    GenTextureMipmaps(&texture1);
    SetTextureFilter(texture1, TEXTURE_FILTER_TRILINEAR);

    Texture texture2 = LoadTexture("../sample/resources/terrain/sand.png");
    GenTextureMipmaps(&texture2);
    SetTextureFilter(texture2, TEXTURE_FILTER_TRILINEAR);

    Texture texture3 = LoadTexture("../sample/resources/terrain/mud.png");
    GenTextureMipmaps(&texture3);
    SetTextureFilter(texture3, TEXTURE_FILTER_TRILINEAR);

    //Texture maskTexture = LoadTexture("../sample/resources/terrain/mask.png");
    Texture maskTexture = LoadTexture("../sample/map_drawer/painting.png");
    SetTextureFilter(maskTexture, TEXTURE_FILTER_BILINEAR);

    rlFPCamera viewCamera;
    viewCamera.HideCursor = false;
    viewCamera.Setup(50, Vector3{ 0,-10,20 }, true);
    viewCamera.MoveSpeed.x = 20;
    viewCamera.MoveSpeed.y = 20;
    viewCamera.MoveSpeed.z = 20;

    Material mat = LoadMaterialDefault();

    Material wireMat = LoadMaterialDefault();
    wireMat.maps[MATERIAL_MAP_ALBEDO].color = BLACK;

    // load basic lighting
    Shader lightShader = LoadShader("../sample/resources/shaders/base_lighting.vs", "../sample/resources/shaders/lighting.fs");

    lightShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightShader, "viewPos");



    int texture1Loc = GetShaderLocation(lightShader, "texture1");
    SetShaderValueTexture(lightShader, texture1Loc, texture1);

    int texture2Loc = GetShaderLocation(lightShader, "texture2");
    SetShaderValueTexture(lightShader, texture2Loc, texture2);

    int texture3Loc = GetShaderLocation(lightShader, "texture3");
    SetShaderValueTexture(lightShader, texture3Loc, texture3);

    int maskLoc = GetShaderLocation(lightShader, "mask0");
    SetShaderValueTexture(lightShader, maskLoc, maskTexture);

    mat.shader = lightShader;
    mat.maps[MATERIAL_MAP_ALBEDO].texture = baseTexture;


    // game loop
    while (!WindowShouldClose())
    {
        // to block mouse when button is unpressed
        viewCamera.UseMouseX = viewCamera.UseMouseY = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        viewCamera.Update();


        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        SetShaderValue(lightShader, lightShader.locs[SHADER_LOC_VECTOR_VIEW], &viewCamera.GetCameraPosition(), SHADER_UNIFORM_VEC3);

        // drawing
        BeginDrawing();
        // this may be not useful
        //DrawTexture(maskTexture, 0, 0, WHITE);
        Texture2D uploaded_img = LoadTextureFromImage(img);
        DrawTexture(uploaded_img, 0, 0, WHITE);
        ClearBackground(SKYBLUE);

        //BeginMode3D(viewCamera.GetCamera());
        viewCamera.BeginMode3D();

        rlPushMatrix();

        SetShaderValueTexture(lightShader, texture1Loc, texture1);
        SetShaderValueTexture(lightShader, texture2Loc, texture2);
        SetShaderValueTexture(lightShader, texture3Loc, texture3);
        SetShaderValueTexture(lightShader, maskLoc, maskTexture);

        DrawMesh(mesh, mat, MatrixIdentity());


        rlPopMatrix();

        EndMode3D();

        DrawFPS(0, 0);

        DrawText(TextFormat("x%0.2f y%0.2f z%0.2f", viewCamera.GetCamera().position.y, viewCamera.GetCamera().position.x, viewCamera.GetCamera().position.z), 10, 40, 20, WHITE);

        EndDrawing();
    }

    UnloadImage(img);
    // cleanup
    CloseWindow();
    return 0;
}

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
