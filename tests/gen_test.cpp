#include "../prj.cw/mesh_generator/include/mesh_generator/grid.hpp"
#include "../prj.cw/mesh_generator/include/mesh_generator/point.hpp"
#include "../prj.cw/mesh_generator/include/mesh_generator/triangle.hpp"
#include "../prj.cw/mesh_generator/include/mesh_generator/hexagon.hpp"

//#define DOCTEST
#define RAYTEST

#ifdef RAYTEST

#include <raylib.h>
#include <string>

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

void ExportGrid(const Grid& gr, const std::string path) {
    Mesh out_mesh = GridToMesh(gr);
    UploadMesh(&out_mesh, false);
    std::string name = path + "grid_mesh.obj";
        bool is_good = ExportMesh(out_mesh, name.c_str());
    if (!is_good) {
        throw std::exception("cant export mesh");
    }
    UnloadMesh(out_mesh);
}

int main() {

    Grid to_out(3, 5.0f);
    std::string out_dir = "D:/_Projects/misis2023f-22-2-khapkov-m-e/tests/";

    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "mesh generator");
    ExportGrid(to_out, out_dir);

    Model model = LoadModel("D:/_Projects/misis2023f-22-2-khapkov-m-e/tests/grid_mesh.obj");
    Model test_cube = LoadModelFromMesh(GenMeshCube(5.0f, 5.0f, 5.0f));

    Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,0.0f,1.0f},45.0f,CAMERA_FREE };
    Vector3 position = { 0.0f, -1.0f, -1.0f };

    Image imBlue = GenImageColor(800, 450, Color{ 0, 0, 255, 255 });
    //Texture texBlue = LoadTextureFromImage(imBlue);
    Texture texBlue = LoadTexture("D:/_Projects/misis2023f-22-2-khapkov-m-e/resources/sand.png");
    UnloadImage(imBlue);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texBlue;
    test_cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texBlue;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        /*DrawTexture(texBlue, screenWidth / 2 - texBlue.width / 2, screenHeight / 2 - 
            texBlue.height / 2 - 40, WHITE);*/

        BeginMode3D(camera);
        DrawGrid(20, 5.0f);
        DrawModel(model, position, 1.0f, WHITE);
        DrawModel(test_cube, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#endif

#ifdef DOCTEST

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_SUITE("vector math") {

    TEST_CASE("vector equality") {
        Vector3D lhs{ 1,2,3 };
        Vector3D rhs{ 1,2,3 };
        CHECK(lhs == rhs);
        rhs.z -= 1;
        CHECK(lhs != rhs);
    }

    TEST_CASE("vector difference") {
        Vector3D a{ 1,2,3 };
        Vector3D b{ 1,2,1 };
        Vector3D c{ 0,0,2 };
        CHECK(a - b == c);
    }

    TEST_CASE("cross product test") {
        Vector3D a{ 1,2,3 };
        Vector3D b{ 1,5,7 };
        Vector3D res = a.Cross(b);
        CHECK(res == Vector3D{ -1,-4,3 });
        res = b.Cross(a);
        CHECK(res == Vector3D{ 1,4,-3 });
    }

    TEST_CASE("dot product test") {
        Vector3D a{ 1,2,1 };
        Vector3D b{ 2,1,2 };
        CHECK(a.Dot(b) == 6);
        CHECK(b.Dot(a) == 6);
    }

    TEST_CASE("vector length test") {
        Vector3D a{ 3,0,4 };
        CHECK(a.GetLen() == 5);
    }

    TEST_CASE("vector normalization test") {
        Vector3D a{ 0,3,4 };
        Vector3D norm = a.GetNormalizedCords();
        CHECK(norm == Vector3D{ 0,0.6f, 0.8f });
    }

    TEST_CASE("pseudo scalar test") {
        Vector3D a{ 1,2,1 };
        Vector3D b{ 2,1,2 };
        CHECK(a.Skew(b) == -3);
        CHECK(b.Skew(a) == 3);
    }

}

TEST_SUITE("triangle operations") {

    TEST_CASE("triangle construct") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle abc(a, b, c);
        Triangle acb(a, c, b);
        for (int i = 0; i < 3; ++i) {
            CHECK(abc.GetSpecVert(i) == acb.GetSpecVert(i));
        }
    }

    TEST_CASE("triangle z setting") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle t(a, b, c);
        t.SetVertZ(0, 5);
        CHECK(t.GetSpecVert(0).z == 5);
        CHECK(t.GetSpecVert(1).z != 5);
        CHECK(t.GetSpecVert(2).z != 5);
    }

    TEST_CASE("triangle area calculation") {
        Vector3D a{ 1,2,0 }, b{ 3,4,0 }, c{ 1,4,0 };
        Triangle t(a, b, c);
        CHECK(FloatCompare(t.GetArea(), 2.0f));
    }

    TEST_CASE("triangle splitting") {
        Triangle t({ 1,2 }, { 3,4 }, { 1,4 });
        auto new_triangles = t.Split();
        CHECK(new_triangles[2].GetSpecVert(0) == Vector3D{ 1, 4 });
        CHECK(new_triangles[2].GetSpecVert(1) == Vector3D{ 1, 2 });
        CHECK(new_triangles[2].GetSpecVert(2) == Vector3D{ 5.0f / 3.0f, 10.0f / 3.0f });
    }

}

TEST_SUITE("hexagon operations") {

    TEST_CASE("hexagon construction") {
        Hexagon h(Vector3D{}, 3.0f);
        CHECK(h.GetSpecVert(2) == Vector3D{ 0, 3.0f });
        CHECK(h.GetSpecVert(5) == Vector3D{ 0, -3.0f });
        CHECK(h.GetSpecVert(6) == Vector3D{ 0, 0.0f });
    }

    TEST_CASE("hexagon z setting") {
        Hexagon h(Vector3D{}, 3.0f);
        auto tmp = h.GetSpecVert(0);
        tmp.z = 5;
        h.SetSpecVert(0, tmp);
        CHECK(FloatCompare(h.GetSpecVert(0).z, 5.0f));
        CHECK(FloatCompare(h.GetSpecVert(1).z, 0.0f));
    }

    TEST_CASE("hexagon's vertex change") {
        Hexagon h({}, 3.0f);
        Vector3D new_pos = { 5,5,5 };
        h.SetSpecVert(6, new_pos);
        CHECK(h.GetSpecVert(6) == new_pos);
        new_pos = { 3,4,8 };
        h.SetSpecVert(3, new_pos);
        CHECK(h.GetSpecVert(3) == new_pos);
        CHECK(h.GetSpecVert(6) == Vector3D{5,5,5});
    }

    TEST_CASE("hexagon splitting") {
        Hexagon h(Vector3D{}, 3.0f);
        auto trigs = h.Split();
        CHECK(trigs[0].GetSpecVert(0) == h.GetSpecVert(0));
        CHECK(trigs[0].GetSpecVert(1) == h.GetSpecVert(1));
        CHECK(trigs[0].GetSpecVert(2) == h.GetSpecVert(6));
    }

}

TEST_SUITE("grid testing") {

    TEST_CASE("grid construction in 2d") {
        Grid g(3, 5.0f);
        CHECK(g.Size() == 9);
        std::vector<Vector3D> first_hex = { {12.9904, 2.5},
                                            {12.9904, 7.5},
                                            {8.66025, 10},
                                            {4.33013, 7.5},
                                            {4.33013, 2.5},
                                            {8.66025, 0} };
        for (int i = 0; i < 6; ++i) {
            bool good = FloatCompare(g.GetHex(0).GetSpecVert(i).x, first_hex[i].x) &&
                FloatCompare(g.GetHex(0).GetSpecVert(i).y, first_hex[i].y);
            CHECK(good);
        }

        CHECK(g.GetHex(8).GetSpecVert(6) == Vector3D{ 8.66025 * 3, 2.5 * 8, 5.0f });  
    }
    // works only if 3rd hex is on 3rd level and
    // others are on 1st
    TEST_CASE("grid plain levels setting") {
        // all are at first level
        // except 4 which is on fifth
        Grid g(3, 5.0f);
        for (int i = 0; i < g.Size(); ++i) {
            if (i != 4)
                CHECK(FloatCompare(g.GetHex(i).GetSpecVert(6).z, 5.0f));
            else
                CHECK(FloatCompare(g.GetHex(i).GetSpecVert(6).z, 25.0f));
        }
    }

    TEST_CASE("search for near hexes") {
        Grid g(3, 5.0f);
        Vector3D tmp = g.GetHex(0).GetSpecVert(0);
        Vector3D close = g.GetHexesNearPoint(tmp);
        CHECK(close == Vector3D{ 0,1,4 });
        tmp = g.GetHex(0).GetSpecVert(5);
        close = g.GetHexesNearPoint(tmp);
        CHECK(close == Vector3D{ 0,1,3 });
    }

    TEST_CASE("grid uv setting") {
        Grid g(3, 5.0f);
        
        Hexagon left_down = g.GetTextHex(0);
        Hexagon right_up = g.GetTextHex(8);

        float Xm = (2 * 3 + 1) / 2.0f * 8.66025;
        float Ym = (3 * 3 + 1) / 4.0f * 10;

        CHECK(left_down.GetSpecVert(5) == Vector3D{ 8.66025f / Xm, 0.0f,0. });
        CHECK(left_down.GetSpecVert(3) == Vector3D{ 4.33013f / Xm, 7.5f / Ym,0. });
        CHECK(FloatCompare(right_up.GetSpecVert(0).x, 1.0f));
        CHECK(FloatCompare(right_up.GetSpecVert(2).y, 1.0f));
    }

    TEST_CASE("barycentric calculations test") {
        Grid g(3, 5.0f);
        // simple center of three hexes
        Vector3D p = g.GetHex(0).GetSpecVert(1);
        Vector3D close = g.GetHexesNearPoint(p);
        Vector3D bar_cords = g.GetBarycentricCords(close, p);
        CHECK(bar_cords == Vector3D{
                                1.0f / 3.0f,
                                1.0f / 3.0f,
                                1.0f / 3.0f });
        // the most right and top
        // lies outside any triangle
        p = g.GetHex(8).GetSpecVert(2);
        close = g.GetHexesNearPoint(p);
        auto res = g.GetBarycentricCords(close, p);
        // 0.571429 0.142857 0.285714
        // std::cout << res.x << " " << res.y << " " << res.z;
    }

    TEST_CASE("barycentric interpolation test") {
        Grid g(3, 5.0f);
        // all are at first level
        // except 4 which is on fifth
        for (int i = 0; i < 6; ++i) {
            CHECK(FloatCompare(g.GetHex(4).GetSpecVert(i).z, 35.0f / 3.0f));
        }
    }

    TEST_CASE("getting single hex to mesh data") {
        Grid g(3, 5.0f);
        auto tmp = g.GetHexMesh(0);
        CHECK(tmp.size() == 6 * 3 * 3 * 3);//last 3 is a centers??
    }

    TEST_CASE("converting grid to vector with vertex data") {
        Grid g(3, 5.0f);
        auto tmp = g.GetGridMesh();
        CHECK(tmp.size() == g.Size() * 6 * 3 * 3 * 3);
    }

    TEST_CASE("converting grid to vector with tex data") {
        Grid g(3, 5.0f);
        auto tmp = g.GetGridUV();
        CHECK(tmp.size() == g.Size() * 6 * 3 * 3 * 3);
    }

}

#endif

