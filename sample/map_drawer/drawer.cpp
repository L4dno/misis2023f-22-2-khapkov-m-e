#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>


// Function to draw a hexagon
void DrawHexagon(Vector2 center, float size, Color color) {
    Vector2 points[6];
    for (int i = 0; i < 6; i++) {
        float angleDeg = 60 * i;
        float angleRad = DEG2RAD * angleDeg;
        points[i].x = center.x + size * std::cosf(angleRad);
        points[i].y = center.y + size * std::sinf(angleRad);
        //DrawCircle(points[i].x, points[i].y, 5, YELLOW);
    }
    // maybe way of rotation is incorrect
    //DrawTriangleFan(points, 6, color);
    DrawPolyLines(center, 6, size, 0, BLACK);
}

// Structure to represent a Vector2 (x, y) in 2D space

// Function to calculate the positions of hexes in a 2D hexagonal grid
std::vector<std::vector<Vector2>> calculateHexGridPositions(int numRows, int numCols, double hexSize) {
    std::vector<std::vector<Vector2>> gridPositions(numRows, std::vector<Vector2>(numCols));

    // Hexagon width and height (pointy-topped orientation)
    float hexWidth = 2 * hexSize;
    float hexHeight = sqrt(3) * hexSize;

    // Calculate the positions of the hexes
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // X coordinate shifts by hexWidth
            float x = col * hexWidth * 0.75; // 0.75 factor for staggered columns

            // Y coordinate shifts by hexHeight
            float y = row * hexHeight + (col % 2 == 1 ? hexHeight / 2 : 0); // Offset for every other column

            gridPositions[row][col] = Vector2{ x, y };
        }
    }

    return gridPositions;
}

int main() {
    
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Honeycomb Pattern Export");

    // Create a RenderTexture2D to draw on (as a canvas)
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    // Begin drawing to the texture
    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    //-------------------------------------------------------------------

    int numRows = 5;
    int numCols = 7;
    float hexSize = 30.0; // Adjust the size of the hexes

    std::vector<std::vector<Vector2>> hexGrid = 
            calculateHexGridPositions(numRows, numCols, hexSize);


    for (auto row: hexGrid) {
        for (auto center : row) {
            DrawHexagon(center, hexSize, BLACK);
            //std::cout << center.x << " " << center.y << std::endl;
        }
    }

    // Draw a honeycomb pattern
    // it can draw
    // but specific pattern doesnt show

    //int hexSize = 50;
    //int hexSpacing = 10;
    //for (int y = 0; y < screenHeight; y += hexSize + hexSpacing) {
    //    for (int x = 0; x < screenWidth; x += hexSize * 1.5f + hexSpacing) {
    //        // centers are suited good
    //        Vector2 center = { x + hexSize / 2.0f, y + hexSize / 2.0f };
    //        DrawHexagon(center, hexSize, BLACK);
    //        DrawPolyLines(center, 6, hexSize, 30, BLACK);
    //    }
    //}

    //DrawPoly(Vector2{ screenHeight /2.0f, screenWidth/2.0f}, 6,hexSize, 30, BLACK);
    // End drawing to the texture
    EndTextureMode();


    //-----------------------------------------------------------------



    // Export the texture as a PNG file
    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    ImageBlurGaussian(&image, 10);
    ImageColorGrayscale(&image);
    ExportImage(image, "../sample/map_drawer/painting.png");
    UnloadImage(image);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // рисование идет, но на текстуре, видимо, ничего нет
        //DrawRectangle(0, 0, 400, 200, RED);
        DrawTextureRec(target.texture, Rectangle {
            0, 0, (float)target.texture.width,
                (float)-target.texture.height
        }, Vector2 { 0, 0 }, WHITE);
        //DrawRectangle(0, 0, 200, 400, BLUE);
        EndDrawing();
    }

    // Clean up
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

