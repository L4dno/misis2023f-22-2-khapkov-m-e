#include <raylib.h>

#define GLSL_VERSION 330

int main() {
    const int screenWiedth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWiedth, screenHeight, "let's interpolate");

    Image grass = LoadImage("../../../../resources/grass.png");
    Texture texGrass = LoadTextureFromImage(grass);
    UnloadImage(grass);

    Image sand = LoadImage("../../../../resources/sand.png");
    Texture texSand = LoadTextureFromImage(sand);
    UnloadImage(sand);

    Shader shader = LoadShader(0, TextFormat("../../../../resources/texture_mix.frag",GLSL_VERSION));
    
    // we need to get all textures location to put them in uniform later
    int texSandLoc = GetShaderLocation(shader, "texture1");
    
    int dividerLoc = GetShaderLocation(shader, "divider");
    float dividerValue = 0.5f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_RIGHT))
            dividerValue += 0.01f;
        else if (IsKeyDown(KEY_LEFT))
            dividerValue -= 0.01f;

        if (dividerValue < 0.0f) dividerValue = 0.0f;
        else if (dividerValue > 1.0f) dividerValue = 1.0f;

        SetShaderValue(shader, dividerLoc, &dividerValue, SHADER_UNIFORM_FLOAT);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginShaderMode(shader);

        // setting shader uniform for texture (sampler2d)
        // maybe here we've sent second texture to shader
        // to combine with another, drawn as usual
        SetShaderValueTexture(shader, texSandLoc, texSand);

        DrawTexture(texGrass, 0, 0, WHITE);

        EndShaderMode();

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadTexture(texGrass);
    UnloadTexture(texSand);

    CloseWindow();

    return 0;

}