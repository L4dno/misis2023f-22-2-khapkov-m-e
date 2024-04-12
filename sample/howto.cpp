#include "raylib.h"

#define GLSL_VERSION 330

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Multitexture with GLSL Example");

    // Load model and textures
    Model model = LoadModel("grid_mesh.obj");
    Texture2D texture1 = LoadTexture("snow.png");
    Texture2D texture2 = LoadTexture("grass.png");
    Texture2D texture3 = LoadTexture("sand.png");

    // Load weight maps
    Texture2D weightMap1 = LoadTexture("t.png");
    Texture2D weightMap2 = LoadTexture("r.png");
    Texture2D weightMap3 = LoadTexture("i.png");

    // Load shader
    Shader shader = LoadShader(0, 
        TextFormat("D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/texture_blending.frag", GLSL_VERSION));

    // Set shader values
    /*SetShaderValueTexture(shader, GetShaderLocation(shader, "texture1"), texture1);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture2"), texture2);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "texture3"), texture3);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "weightMap1"), weightMap1);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "weightMap2"), weightMap2);
    SetShaderValueTexture(shader, GetShaderLocation(shader, "weightMap3"), weightMap3);*/

    // Main loop
    while (!WindowShouldClose()) {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginShaderMode(shader);

        // Draw model with shader applied
        DrawModel(model, Vector3 { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

        EndShaderMode();

        EndDrawing();
    }

    // Cleanup
    UnloadTexture(texture1);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
    UnloadTexture(weightMap1);
    UnloadTexture(weightMap2);
    UnloadTexture(weightMap3);
    UnloadModel(model);
    UnloadShader(shader);

    CloseWindow();

    return 0;
}