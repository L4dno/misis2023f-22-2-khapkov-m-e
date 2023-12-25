//#include "earcut.hpp"
#include <iostream>
#include <vector>
#include <array>

struct Vertex {

};

class Hexagon {
    // returns cords of vertex number i, calculated
    Vertex GetSpecVert(int i);
    std::array<Triangle, 6> split();
    Vertex center;
    float radius;
};

class Triangle {
    // func returns cords of 4 smaller fractial triangles
    std::array<Triangle, 4> split();
    std::array<Vertex, 3> core;
};

int main() {

    // init hex
    
    // create a vector of of consecventive 2d triangles

    // give a height for every hex vertex

    // interpolate a heigth for every new vertexes

    return 0;
}
