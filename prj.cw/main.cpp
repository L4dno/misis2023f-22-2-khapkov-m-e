

#include "material_lib/include/renderer/renderer.hpp"

#include <vector>
#include <string>


// test app

int main() {

    Renderer r;
    std::vector<std::string> textures =
    { "../resources/lava.png", "../resources/grass.png", 
        "../resources/dirt.png", "../resources/mud.png"};

    for (int i = 0; i < 4; ++i)
        r.SetTextureI(i, textures[i]);
    r.SetMask("../resources/painting.png");

    r.DrawSelf();

    return 0;
}