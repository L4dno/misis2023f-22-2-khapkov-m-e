#include <material_lib/material.hpp>

#include <vector>
#include <string>


// test app
int main() {

    Renderer r;
    
    std::vector<std::string> textures = { "../prj.cw/resources/grass.png", 
        "../prj.cw/resources/sand.png" };
    std::vector<int> map = { 0,1,0,1,0,1,0 };

    r.LoadMeshData("../prj.cw/resources/mesh_out/", 7);
    r.LoadTexturesData(textures);
    r.LoadHexToMaterialMap(map);

    r.DrawSelf();
    

    return 0;
}
