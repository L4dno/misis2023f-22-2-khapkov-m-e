#include "grid.hpp"

#include <raylib.h>
#include <raymath.h>
#include <iterator>

Mesh TranslateMesh(std::vector<Vector3D>& mesh_data, std::vector<Vector3D>& tex_data) {
    Mesh mesh = { 0 };
    mesh.triangleCount = mesh_data.size() / 3;
    mesh.vertexCount = mesh_data.size();
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));

    for (int i = 0; i < mesh_data.size(); ++i) {
        mesh.vertices[i * 3] = mesh_data[i].x;
        mesh.vertices[i * 3 + 1] = mesh_data[i].y;
        mesh.vertices[i * 3 + 2] = mesh_data[i].z;
        mesh.texcoords[i * 2] = tex_data[i].x;
        mesh.texcoords[i * 2 + 1] = tex_data[i].y;
    }
    UploadMesh(&mesh, false);
    return mesh;
}

void ShowModel(Model ter) {

    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_PERSPECTIVE };
    Vector3 position = { 0.0f, 0.0f, -1.0f };

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        // drawing 3d shapes
        DrawModel(ter, position, 1.0f, WHITE);

        DrawGrid(10, 1.0);
        DrawLine3D({ 0,0,0 }, { 0,5.0f,0.0f }, GOLD);
        DrawLine3D({ 0,0,0 }, { 5.0f,0.0f,0.0f }, LIME);
        DrawLine3D({ 0,0,0 }, { 0,0.0f,5.0f }, RED);
        //DrawPoint3D({ 5.0f,5.0f,5.0f }, PURPLE);

        EndMode3D();

        EndDrawing();
    }
    
    
}

Model MergeMeshes(std::vector<Mesh>& mesh_arr, std::vector<Material>& mat_arr,
                    std::vector<int>& mesh_to_mat) {
    Model out_model = { 0 };
    
    out_model.meshCount = mesh_arr.size();
    out_model.materialCount = mat_arr.size();

    out_model.transform = MatrixIdentity();

    out_model.meshes = (Mesh*)MemAlloc(sizeof(Mesh) * out_model.meshCount);
    out_model.materials = (Material*)MemAlloc(sizeof(Material) * out_model.materialCount);
    out_model.meshMaterial = (int*)MemAlloc(sizeof(int) * out_model.meshCount);

    out_model.boneCount = 0;
    out_model.bones = NULL;
    out_model.bindPose = NULL;

    for (int i = 0; i < out_model.meshCount; ++i) {
        out_model.meshes[i] = mesh_arr[i];
        out_model.meshMaterial[i] = mesh_to_mat[i];
    }
    for (int i = 0; i < out_model.materialCount; ++i) {
        out_model.materials[i] = mat_arr[i];
    }

    return out_model;

}

int main() {
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");

    Grid g(5.0f);
    std::vector<Mesh> mesh_arr;
    for (int i = 0; i < 7; ++i) {
        std::vector<Vector3D> mesh = g.GetHexMesh(i);
        std::vector<Vector3D> tex = g.GetHexUV(i);
        mesh_arr.push_back(TranslateMesh(mesh, tex));
    }

    std::vector<Material> mats;
    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    mats.push_back(LoadMaterialDefault());
    mats[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    std::vector<int> map = { 0, 0, 0,0,0,0,0};

    
    Model outcome = MergeMeshes(mesh_arr, mats, map);
    ShowModel(outcome);
    UnloadModel(outcome);
    CloseWindow();


   /* std::vector<Mesh> meshes;
    meshes.push_back(GenMeshCube(3, 3, 8));
    meshes.push_back(GenMeshCube(4, 9, 4));

    UploadMesh(&meshes[0], 0);
    UploadMesh(&meshes[1], 0);

    std::vector<Material> mats;
    Image checked = GenImageChecked(2, 2, 1, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    mats.push_back(LoadMaterialDefault());
    mats[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    std::vector<int> map = { 0, 0 };*/

    //Model m = MergeMeshes(meshes, mats, map);
   /* m.materialCount = 1;
    m.materials = (Material*)MemAlloc(m.materialCount *  sizeof(Material));
    m.materials[0] = LoadMaterialDefault();*/

    //Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
    //    {0.0f,1.0f,0.0f},45.0f,CAMERA_PERSPECTIVE };

    //while (!WindowShouldClose()) {
    //    UpdateCamera(&camera, CAMERA_FREE);

    //    BeginDrawing();

    //    ClearBackground(RAYWHITE);
    //    BeginMode3D(camera);
    //    // drawing 3d shapes
    //    DrawModel(m, {0,0,0}, 1.0f, WHITE);

    //    DrawGrid(10, 1.0);
    //    DrawLine3D({ 0,0,0 }, { 0,5.0f,0.0f }, GOLD);
    //    DrawLine3D({ 0,0,0 }, { 5.0f,0.0f,0.0f }, LIME);
    //    DrawLine3D({ 0,0,0 }, { 0,0.0f,5.0f }, RED);
    //    //DrawPoint3D({ 5.0f,5.0f,5.0f }, PURPLE);

    //    EndMode3D();

    //    EndDrawing();
    //}
    //UnloadModel(m);
    //CloseWindow();

    return 0;
}