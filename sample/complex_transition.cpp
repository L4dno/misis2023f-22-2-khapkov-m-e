#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <cmath>

#define MAX_POINTS 7

Vector2 GetHexVertI(const Vector2 center, const float size, const int i) {
    float angle_rad = i / 6.0 * 2 * PI;
    return Vector2{ center.x + size * std::cos(angle_rad), 
                    center.y + size * std::sin(angle_rad) };
}

Vector2* GetHexPoints(Vector2 res[], const Vector2 center, const float size) {;
    for (int i = 0; i < MAX_POINTS; ++i) {
        res[i] = GetHexVertI(center, size, i);
    }
    return res;
}

void DrawTexturePoly(Texture2D texture, Vector2 center,
    Vector2* points, Vector2* texcoords,
    int pointCount, Color tint) {
    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);

    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    for (int i = 0; i < pointCount - 1; ++i) {
        rlTexCoord2f(0.5f, 0.5f);
        rlVertex2f(center.x, center.y);

        rlTexCoord2f(texcoords[i].x, texcoords[i].y);
        rlVertex2f(points[i].x + center.x, points[i].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
    }
    rlEnd();
    rlSetTexture(0);
}

int main() {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2d hexagon");
    SetTargetFPS(60);

    float rotation = 0;

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircle(screenWidth / 5, 120, 35, DARKBLUE);

        DrawTriangle(Vector2 { screenWidth / 4.0f * 3.0f, 80.0f },
            Vector2 { screenWidth / 4.0f * 3.0f - 60.0f, 150.0f},
            Vector2 { screenWidth / 4.0f * 3.0f + 60.0f, 150.0f}, VIOLET);
        
        DrawPoly(Vector2{ screenWidth / 4.0f * 3, 330 }, 6, 120, 0, MAGENTA);
        //DrawPoly(Vector2{ screenWidth / 4.0f * 3, 330 }, 6, 90, 0, GREEN);

        // rotation += 2.0f;
        //DrawPoly(Vector2{ screenWidth / 4.0f * 3, 330 }, 6, 30, 1000, RED);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}

//int main()
//{
//    
//    const int screenWidth = 1080;
//    const int screenHeight = 720;
//
//    InitWindow(screenWidth, screenHeight, "hexagonalistic!");
//
//    const float hex_size = 1.0;
//
//    Vector2 first_hex_cords = { 0.0f,0.0f };
//    Vector2 tex_coords[MAX_POINTS];
//    GetHexPoints(tex_coords, first_hex_cords, hex_size);
//    
//    Vector2 points[MAX_POINTS] = { 0 };
//    for (int i = 0; i < MAX_POINTS; ++i) {
//        points[i].x = (tex_coords[i].x - 0.5f) * 256.0f;
//        points[i].y = (tex_coords[i].y - 0.5f) * 256.0f;
//    }
//
//    Vector2 positions[MAX_POINTS] = { 0 };
//    for (int i = 0; i < MAX_POINTS; ++i)
//        positions[i] = points[i];
//
//    Texture texture = LoadTexture("../../../../resources/grass.png");
//
//    SetTargetFPS(60);
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//        DrawTexturePoly(texture, Vector2{ GetScreenWidth() / 2.0f,
//            GetScreenHeight() / 2.0f }, positions, tex_coords, MAX_POINTS, WHITE);
//        EndDrawing();
//    }
//
//    UnloadTexture(texture);
//    CloseWindow();
//
//    return 0;
//}