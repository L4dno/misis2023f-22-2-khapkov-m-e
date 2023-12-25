#include <raylib.h>
#include <string>
#include "earcut.hpp"   

#define NUM_MODELS  3 



class Triangle {
protected:
    Mesh trig = { 0 };
    Vector3 pos = { 0 };
    Model model = { 0 };
    const float scale = 2.0f;
public:
    // which fields and methods did i miss?
    Triangle() {}
    // in which order to set vertices?
    // where to set UV
    Triangle(Vector3 a, Vector3 b, Vector3 c, Vector3 origin) {
        pos = origin;

        trig.triangleCount = 1;
        trig.vertexCount = trig.triangleCount * 3;
        trig.vertices = (float*)MemAlloc(trig.vertexCount * 3 * sizeof(float));
        trig.texcoords = (float*)MemAlloc(trig.vertexCount * 2 * sizeof(float));
        //mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

        trig.vertices[0] = a.x;
        trig.vertices[1] = a.y;
        trig.vertices[2] = a.z;

        trig.vertices[3] = b.x;
        trig.vertices[4] = b.y;
        trig.vertices[5] = b.z;

        trig.vertices[6] = c.x;
        trig.vertices[7] = c.y;
        trig.vertices[8] = c.z;

        model = LoadModelFromMesh(trig);
    }
    void DrawSelf() {
        DrawModel(model, pos, scale, WHITE);
    }

    friend void SetPolyTexture(Triangle tr, Texture tx);

    ~Triangle() {
        UnloadModel(model);
    }
};

// gen triangle 3d mesh
// need to parameterize
static Mesh GenMeshCustom();
void SetPolyTexture(Triangle tr, Texture tx);
Texture SetUpTexture(std::string file_name);
void UnSetUpTexture(Texture tx);



int main() {

    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");

    // image for texturing meshes
    //Image checked = GenImageChecked(2, 2, 1, 1, RED, BLUE);
    Image checked = LoadImage("../../../../resources/grass.png");
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    Model models[NUM_MODELS] = { 0 };
    Model rab = LoadModel("../../../../resources/rabbit.obj");
    rab.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // model is more general than mesh
    // which one should use textures and shaders???
    models[0] = LoadModelFromMesh(GenMeshPoly(6, 2.0f));
    models[1] = LoadModelFromMesh(GenMeshCube(2.0f, 1.0f, 2.0f));
    models[2] = LoadModelFromMesh(GenMeshCustom());
    // meshes can be exported

    // setting textures to models
    for (int i = 0; i < NUM_MODELS; ++i)
        models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // camera angle
    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_PERSPECTIVE };

    // pos where mesh is located
    Vector3 position = { 0.0f, 3.0f, 0.0f };

    int currentModel = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentModel = (currentModel + 1) % NUM_MODELS;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        // drawing 3d shapes
        //DrawModel(models[currentModel], position, 1.0f, WHITE);
        //DrawModel(models[NUM_MODELS - 1], position, 2.0f, WHITE);
        DrawGrid(10, 1.0);
        DrawLine3D({ 0,0,0 }, { 0,5.0f,0.0f }, GOLD);
        DrawLine3D({ 0,0,0 }, { 5.0f,0.0f,0.0f }, LIME);
        DrawLine3D({ 0,0,0 }, { 0,0.0f,5.0f }, RED);
        //DrawPoint3D({ 5.0f,5.0f,5.0f }, PURPLE);

        DrawModel(rab, position, 1.0f, WHITE);

        EndMode3D();

        EndDrawing();
    }

    UnloadTexture(texture);

    for (int i = 0; i < NUM_MODELS; ++i) UnloadModel(models[i]);
    UnloadModel(rab);

    CloseWindow();

    return 0;

}

static Mesh GenMeshCustom() {
    // init mesh characteristics
    Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount * 3;
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
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
    mesh.vertices[4] = 1;
    mesh.vertices[5] = 2;
     mesh.normals[3] = 0;
     mesh.normals[4] = 1;
     mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 1;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] = 0;

    UploadMesh(&mesh, false);

    return mesh;
}

Texture SetUpTexture(std::string file_name) {
    Image checked = LoadImage(file_name.c_str());
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    return texture;
}

void SetPolyTexture(Triangle tr, Texture tx) {
    tr.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tx;
}

void UnSetUpTexture(Texture tx) {
    UnloadTexture(tx);
}