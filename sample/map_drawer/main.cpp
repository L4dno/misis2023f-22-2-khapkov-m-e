#include "raylib.h"
#include <cmath>
// Function to draw a hexagon
void DrawHexagon(Vector2 center, float size, Color color) {
    Vector2 points[6];
    for (int i = 0; i < 6; i++) {
        float angleDeg = 60 * i - 30;
        float angleRad = DEG2RAD * angleDeg;
        points[i].x = center.x + size * std::cosf(angleRad);
        points[i].y = center.y + size * std::sinf(angleRad);
        DrawCircle(points[i].x, points[i].y, 5, YELLOW);
    }
    // maybe way of rotation is incorrect
    DrawTriangleFan(points, 6, color);
}

int main() {
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Honeycomb Pattern Export");

    // Create a RenderTexture2D to draw on (as a canvas)
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    // Begin drawing to the texture
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    // Draw a honeycomb pattern
    // it can draw
    // but specific pattern doesnt show
    int hexSize = 50;
    int hexSpacing = 10;
    for (int y = 0; y < screenHeight; y += hexSize + hexSpacing) {
        for (int x = 0; x < screenWidth; x += hexSize * 1.5f + hexSpacing) {
            // centers are suited good
            Vector2 center = { x + hexSize / 2.0f, y + hexSize / 2.0f };
            DrawHexagon(center, hexSize, PURPLE);
            //DrawCircle(center.x, center.y, 5, YELLOW);
        }
    }

    // End drawing to the texture
    EndTextureMode();

    // Export the texture as a PNG file
    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    ExportImage(image, "my_amazing_texture_painting.png");
    UnloadImage(image);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // рисование идет, но на текстуре, видимо, ничего нет
        DrawRectangle(0, 0, 400, 200, RED);
        DrawTextureRec(target.texture, Rectangle {
            0, 0, (float)target.texture.width,
                (float)-target.texture.height
        }, Vector2 { 0, 0 }, WHITE);
        DrawRectangle(0, 0, 200, 400, BLUE);
        EndDrawing();
    }

    // Clean up
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

