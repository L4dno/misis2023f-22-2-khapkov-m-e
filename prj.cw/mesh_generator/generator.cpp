#include "include/mesh_generator/grid.hpp"

#include <raylib.h>

#include <string>
#include <sstream>
#include <iostream>

void ExportGrid(const Grid& gr, const std::string path);
Mesh HexToMesh(const std::vector<Vector3D> mesh_data, const std::vector<Vector3D> tex_data);
std::string GetObjName(const std::string path, int mesh_ind);

int main() {

    Grid to_out(5.0f);
    std::string out_dir = "D:/_Projects/misis2023f-22-2-khapkov-m-e/prj.cw/resources/mesh_out";

    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");
    ExportGrid(to_out, out_dir);
    CloseWindow();

    return 0;
}

void ExportGrid(const Grid& gr, const std::string path) {
    for (int i = 0; i < gr.Size(); ++i) {
        Mesh out_mesh = HexToMesh(gr.GetHexMesh(i), gr.GetHexUV(i));
        UploadMesh(&out_mesh, false);
        bool is_good = ExportMesh(out_mesh, GetObjName(path, i).c_str());
        if (!is_good) {
            throw std::exception("cant export mesh");
        }
        UnloadMesh(out_mesh);
    }
}

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