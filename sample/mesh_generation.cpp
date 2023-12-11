#include <raylib.h>

#define NUM_MODELS  3 

// gen triangle 3d mesh
// need to parameterize
static Mesh GenMeshCustom();

int main() {

    const int screenWidth = 720;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "mesh generator");

    // image for texturing meshes
    Image checked = GenImageChecked(2, 2, 1, 1, RED, BLUE);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    Model models[NUM_MODELS] = { 0 };

    // model is more general than mesh
    // which one should use textures and shaders???
    models[0] = LoadModelFromMesh(GenMeshPoly(5, 2.0f));
    models[1] = LoadModelFromMesh(GenMeshCube(2.0f, 1.0f, 2.0f));
    models[2] = LoadModelFromMesh(GenMeshCustom());
    // meshes can be exported

    // setting textures to models
    for (int i = 0; i < NUM_MODELS; ++i)
        models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // camera angle
    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,0 };

    // pos where mesh is located
    Vector3 position = { 0.0f, 0.0f, 0.0f };

    int currentModel = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentModel = (currentModel + 1) % NUM_MODELS;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        // drawing 3d shapes
        DrawModel(models[currentModel], position, 1.0f, WHITE);
        DrawGrid(10, 1.0);

        EndMode3D();

        EndDrawing();
    }

    UnloadTexture(texture);

    for (int i = 0; i < NUM_MODELS; ++i) UnloadModel(models[i]);
    
    CloseWindow();

    return 0;

}

static Mesh GenMeshCustom() {
    // init mesh characteristics
    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    // manually setting cords

    // vert at (0,0,0)
    // why do we need normals for vertexes
    // not for the whole triangle?
    // and how UV cords work here?
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] = 0;

    UploadMesh(&mesh, false);

    return mesh;
}