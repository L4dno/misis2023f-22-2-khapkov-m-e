

#include "renderer.hpp"

#include <vector>
#include <string>


// test app

int main() {

    Renderer r;

    std::vector<std::string> textures =
    { "../../prj.test/resources/snow.png", "../../prj.test/resources/sand.png",
        "../../prj.test/resources/dirt.png", "../../prj.test/resources/grass.png" };

    for (int i = 0; i < 4; ++i)
        r.SetTextureI(i, textures[i]);
    r.SetMask("../../prj.test/resources/painting.png");

    r.DrawSelf();

    return 0;
}