//#include <iostream>
//#include <array>
//#include <vector>
//#include <utility>
//#include "earcut.hpp"
//
//int main() {
//
//    using Coord = double;
//
//    // The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
//    // data won't have more than 65536 vertices.
//    using N = uint32_t;
//    using Point = std::pair<Coord, Coord>;
//
//    std::vector<std::vector<Point>> polygon = { {
//        {0.0, 0.0},   // Vertex 1
//        {1.0, 0.0},   // Vertex 2
//        {1.5, 0.866}, // Vertex 3
//        {1.0, 1.732}, // Vertex 4
//        {0.0, 1.732}, // Vertex 5
//        {-0.5, 0.866} // Vertex 6
//    } };
//
//    // Define the vertices of the hexagon
//    //std::vector<std::vector<double>> hexagonVertices = { {
//    //    {0.0, 0.0},   // Vertex 1
//    //    {1.0, 0.0},   // Vertex 2
//    //    {1.5, 0.866}, // Vertex 3
//    //    {1.0, 1.732}, // Vertex 4
//    //    {0.0, 1.732}, // Vertex 5
//    //    {-0.5, 0.866} // Vertex 6
//    //} };
//
//    // Define the number of fractional divisions for each edge
//    int fractionalDivisions = 3;
//
//    // Create a new vector for the vertices with fractional division
//
//    // every side we divide by fractionalDivisions lines???
//    std::vector<std::vector<Point>> fractionalVertices;
//    for (size_t i = 0; i < polygon[0].size(); ++i) {
//        fractionalVertices.push_back(polygon[i]);
//        if (i < hexagonVertices.size() - 1) {
//            double dx = (hexagonVertices[i + 1][0] - hexagonVertices[i][0]) / fractionalDivisions;
//            double dy = (hexagonVertices[i + 1][1] - hexagonVertices[i][1]) / fractionalDivisions;
//            for (int j = 1; j < fractionalDivisions; ++j) {
//                fractionalVertices.push_back({ hexagonVertices[i][0] + j * dx, hexagonVertices[i][1] + j * dy });
//            }
//        }
//    }
//    fractionalVertices.push_back(hexagonVertices.back());
//
//    // Use the earcut library to triangulate the hexagon with fractional vertices into triangles
//    std::vector<int> indices = mapbox::earcut<int>(fractionalVertices);
//
//    // Output the indices of the triangles
//    std::cout << "Triangle indices: ";
//    for (int index : indices) {
//        std::cout << index << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
//
////int main() {
////
////    // The number type to use for tessellation
////    using Coord = float;
////
////    // The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
////    // data won't have more than 65536 vertices.
////    using N = uint32_t;
////
////    // Create array
////    using Point = std::array<Coord, 2>;
////    std::vector<std::vector<Point>> polygon;
////
////    // Fill polygon structure with actual data. Any winding order works.
////    // The first polyline defines the main polygon.
////    //std::vector<Point> pol = { {100, 0}, {100, 100}, {0, 100}, {0, 0} };
////    polygon.push_back({ {100, 0}, {150,50},{00, 100}, {0, 100}, {0, 0} });
////
////    // Following polylines define holes.
////    //polygon.push_back({ {75, 25}, {75, 75}, {25, 75}, {25, 25} });
////
////    // Run tessellation
////    // Returns array of indices that refer to the vertices of the input polygon.
////    // e.g: the index 6 would refer to {25, 75} in this example.
////    // Three subsequent indices form a triangle. Output triangles are clockwise.
////    std::vector<N> indices = mapbox::earcut<N>(polygon);
////
////    int i = 0;
////    std::cout << indices.size() << "\n";
////    for (N tmp : indices) {
////        std::cout << i << ": " << tmp << "\n";
////        ++i;
////    }
////
////    i = 0;
////    std::cout << "\n" << polygon.size() << "\n";
////    for (auto& tmp : polygon) {
////        for (int i = 0; i < tmp.size(); ++i) {
////            std::cout << i << ": " << tmp[i][0] << " - " << tmp[i][1] << "\n";
////        }
////        //++i;
////    }
////
////    return 0;
////}

#include "earcut.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <GL/GLU.h>

int main() {
    // Define the vertex coordinates of the hexagon
    std::vector<std::array<double, 2>> vertices = {
        {0.0, 0.0},  // Vertex 1
        {100.0, 0.0},  // Vertex 2
        {150.0, 50.0},  // Vertex 3
        {100.0, 100.0},  // Vertex 4
        {0.0, 100.0},  // Vertex 5
        {-50.0, 50.0}  // Vertex 6
    };

    // Specify the level of division
    int innerLevel = 1;
    int outerLevel = 1;

    // Triangulate the hexagon using earcut
    std::vector<uint32_t> indices = mapbox::earcut<uint32_t>(vertices, innerLevel, outerLevel);

    // Print the indices of the triangles
    for (size_t i = 0; i < indices.size(); i += 3) {
        std::cout << "Triangle " << i / 3 << ": " << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
    }

    return 0;
}