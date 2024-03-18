#include "include/mesh_generator/grid.hpp"

#include <raylib.h>

#include <string>
#include <sstream>
#include <iostream>

void ExportGrid(const Grid& gr, const std::string path);
Mesh HexToMesh(const std::vector<Vector3D> mesh_data, const std::vector<Vector3D> tex_data);
std::string GetObjName(const std::string path, int mesh_ind);

// convert one grid to one mesh
Mesh GridToMesh(const Grid& gr);

int main() {

    Grid to_out(5.0f);
    std::string out_dir = "../prj.cw/resources/mesh_out/";

    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");
    ExportGrid(to_out, out_dir);
    CloseWindow();

    return 0;

}

Mesh GridToMesh(const Grid& gr) {
    auto mesh_data = gr.GetGridMesh();
    auto tex_data = gr.GetGridUV();

    
        Mesh mesh = { 0 };
        mesh.triangleCount = mesh_data.size() / 3;
        mesh.vertexCount = mesh_data.size();
        mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
        mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
        mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

        // Mesh out_mesh = HexToMesh(gr.GetHexMesh(i), gr.GetHexUV(i));

        for (int i = 0; i < mesh_data.size(); ++i) {
            mesh.vertices[i * 3] = mesh_data[i].x;
            mesh.vertices[i * 3 + 1] = mesh_data[i].y;
            mesh.vertices[i * 3 + 2] = mesh_data[i].z;
            mesh.texcoords[i * 2] = tex_data[i].x;
            mesh.texcoords[i * 2 + 1] = tex_data[i].y;
            mesh.normals[i * 3] = 0;
            mesh.normals[i * 3 + 1] = 0;
            mesh.normals[i * 3 + 2] = 0;
        }

        return mesh;

}

// should be rewritten as exporting one mesh
void ExportGrid(const Grid& gr, const std::string path) {
    Mesh out_mesh = GridToMesh(gr);    
        UploadMesh(&out_mesh, false);
        std::string name = path + "grid_mesh.obj"
        bool is_good = ExportMesh(out_mesh, name.c_str());
        if (!is_good) {
            throw std::exception("cant export mesh");
        }
        UnloadMesh(out_mesh);
}

// should unite all data at one mesh
Mesh HexToMesh(const std::vector<Vector3D> mesh_data, 
    const std::vector<Vector3D> tex_data) {
    Mesh mesh = { 0 };
    mesh.triangleCount = mesh_data.size() / 3;
    mesh.vertexCount = mesh_data.size();
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)MemAlloc(mesh.vertexCount * 2 * sizeof(float));
    mesh.normals = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));

    for (int i = 0; i < mesh_data.size(); ++i) {
        mesh.vertices[i * 3] = mesh_data[i].x;
        mesh.vertices[i * 3 + 1] = mesh_data[i].y;
        mesh.vertices[i * 3 + 2] = mesh_data[i].z;
        mesh.texcoords[i * 2] = tex_data[i].x;
        mesh.texcoords[i * 2 + 1] = tex_data[i].y;
        mesh.normals[i * 3] = 0;
        mesh.normals[i * 3 + 1] = 0;
        mesh.normals[i * 3 + 2] = 0;
    }
    return mesh;
}

std::string GetObjName(const std::string path, int mesh_ind) {
    std::ostringstream buffer;
    buffer << path << "/mesh" << mesh_ind << ".obj";
    return buffer.str();
}