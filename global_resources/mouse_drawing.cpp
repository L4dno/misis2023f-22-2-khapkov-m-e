
#include "raylib.h"

#define MAX_COLORS_COUNT    23          // Number of colors available

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - mouse painting");

    // Create a RenderTexture2D to use as a canvas
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    // Clear render texture before entering the game loop
    BeginTextureMode(target);
    ClearBackground(colors[0]);
    EndTextureMode();

    SetTargetFPS(120);              // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Vector2 mousePos = GetMousePosition();

        if ((btnSaveMouseHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_S))
        {
            Image image = LoadImageFromTexture(target.texture);
            ImageFlipVertical(&image);
            ExportImage(image, "my_amazing_texture_painting.png");
            UnloadImage(image);
            showSaveMessage = true;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);

        // Draw drawing circle for reference
        if (mousePos.y > 50)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) DrawCircleLines((int)mousePos.x, (int)mousePos.y, brushSize, GRAY);
            else DrawCircle(GetMouseX(), GetMouseY(), brushSize, colors[colorSelected]);
        }

        // Draw top panel
        DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
        DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

        // Draw color selection rectangles
        for (int i = 0; i < MAX_COLORS_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);
        DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

        if (colorMouseHover >= 0) DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));

        DrawRectangleLinesEx((Rectangle) {
            colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
                colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4
        }, 2, BLACK);

        // Draw save image button
        DrawRectangleLinesEx(btnSaveRec, 2, btnSaveMouseHover ? RED : BLACK);
        DrawText("SAVE!", 755, 20, 10, btnSaveMouseHover ? RED : BLACK);

        // Draw save image message
        if (showSaveMessage)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
            DrawText("IMAGE SAVED:  my_amazing_texture_painting.png", 150, 180, 20, RAYWHITE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);    // Unload render texture

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}