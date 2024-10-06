#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

// x and y are coordinates and z is a color
using Grid = std::vector<std::vector<Vector3>>;
// Function to calculate the positions of hexes in a 2D hexagonal grid
Grid CalculateHexGridPositions(int numRows, int numCols, double hexSize) {
    Grid gridPositions(numRows, std::vector<Vector3>(numCols));

    // Hexagon width and height (pointy-topped orientation)
    float hexWidth = 2 * hexSize;
    float hexHeight = sqrt(3) * hexSize;

    float xOffset = hexWidth * 0.5f;
    float yOffset = hexHeight * 0.5f;

    // Calculate the positions of the hexes
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // X coordinate shifts by hexWidth
            float x = col * hexWidth * 0.75 + xOffset; // 0.75 factor for staggered columns

            // Y coordinate shifts by hexHeight
            float y = row * hexHeight + (col % 2 == 1 ? hexHeight / 2 : 0) + yOffset; // Offset for every other column

            gridPositions[row][col] = Vector3{ x, y };
        }
    }

    return gridPositions;
}

void ColorizeTextMap(Grid& grid) {
    if (grid.size() == 0)
        throw std::exception("ColorizeTextMap received empty grid");
    std::random_device rd;
    std::mt19937 gen(rd());

    // random coloring from 1 to 3 textures when 0 is a bases
    std::uniform_int_distribution<> dis(1, 3);
    for (auto& row : grid) {
        for (auto& hex : row) {
            hex.z = dis(gen);
        }
    }
}

int main() {
    
    const int screenWidth = 1024;
    const int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "Honeycomb Pattern Export");

    // Create a RenderTexture2D to draw on (as a canvas)
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    // Begin drawing to the texture
    BeginTextureMode(target);
    ClearBackground(WHITE);

    // all changes in algo only between such lines
    //-------------------------------------------------------------------

    int numRows = 5;
    int numCols = 7;
    float hexSize = 60.0; // Adjust the size of the hexes

    Grid hexGrid = 
            CalculateHexGridPositions(numRows, numCols, hexSize);
    ColorizeTextMap(hexGrid);

    for (auto row: hexGrid) {
        for (auto center : row) {
            Color tmp;
            switch (int(center.z)) {
            case 0: 
                throw std::exception("when drawing hexes on text colors are unitialized");
                break;
            case 1: tmp = RED; break;
            case 2: tmp = BLUE; break;
            case 3: tmp = GREEN; break;
            }
            DrawPoly({ center.x,center.y }, 6, hexSize, 0, tmp);
        }
    }

    
    // End drawing to the texture
    EndTextureMode();


    //-----------------------------------------------------------------



    // Export the texture as a PNG file
    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    ImageBlurGaussian(&image, 5);
    //ImageColorGrayscale(&image);
    //  exe in bin/Debug  png needs to be in prj.cw/resources
    ExportImage(image, "../resources/painting.png");
    UnloadImage(image);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // method for drawing texture as rectangle
        DrawTextureRec(target.texture, Rectangle {
            0, 0, (float)target.texture.width,
                (float)-target.texture.height
        }, Vector2 { 0, 0 }, WHITE);
        EndDrawing();
    }

    // Clean up
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

