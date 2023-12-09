#define SUPPORT_FILEFORMAT_JPG 
#define GLSL_VERSION            330

#include <raylib.h>
#include <raymath.h>

int main() {

    const int kScreenWidth = 1080;
    const int kScreenHeight = 720;

    InitWindow(kScreenWidth, kScreenHeight, "my little window");

    SetTargetFPS(60);

    Vector2 rect_pos = { GetScreenWidth() / 3.0f,GetScreenHeight() / 3.0f };
    Vector2 rect_shape = { GetScreenWidth() / 3.0f, GetScreenHeight() / 3.0f };

    Image image = LoadImage("../../../../resources/grass.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    Rectangle rect;

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawTexture(texture, (kScreenWidth / 2 - texture.width / 2), 
        //    kScreenHeight / 2 - texture.height / 2, WHITE);
        //DrawRectangleV(rect_pos, rect_shape, GREEN);

        EndDrawing();

    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}