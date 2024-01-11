#ifndef MATERIAL_11012024
#define MATERIAL_11012024

#include <raylib.h>

#include <string>
#include <vector>

class Renderer {
private:
    Model model = { 0 };
    const int kWindowHeight = 1080;
    const int kWindowWidth = 1920;

    std::string GetObjName(const std::string path, int mesh_ind);

public:
    // here we init context
    Renderer();
    // and here we close
    ~Renderer();
    void LoadMeshData(std::string path, int count);
    void LoadTexturesData(std::vector<std::string> file_names);
    void LoadHexToMaterialMap(std::vector<int> hex_mat);
    void DrawSelf();
};

#endif