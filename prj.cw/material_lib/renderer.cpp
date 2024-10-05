#include "include/renderer/renderer.hpp"
#include "include/camera/rlFPCamera.h"

#include <raymath.h>
#include <rlgl.h>

#include <string>
#include <sstream>
#include <exception>
#include <vector>

#define GLSL_VERSION            330

// a simple class to help build up faces of a cube
class GeomtryBuilder
{
public:

    // setup the builder with the mesh it is going to fill out
    GeomtryBuilder(Mesh& mesh) : MeshRef(mesh)
    {
    }

    // we need to know how many triangles are going to be in the mesh before we start
    // this way we can allocate the correct buffer sizes for the mesh
    void Allocate(int triangles)
    {
        // there are 
        MeshRef.vertexCount = triangles * 6;
        MeshRef.triangleCount = triangles * 2;

        MeshRef.vertices = static_cast<float*>(MemAlloc(sizeof(float) * 3 * MeshRef.vertexCount));
        MeshRef.normals = static_cast<float*>(MemAlloc(sizeof(float) * 3 * MeshRef.vertexCount));
        MeshRef.texcoords = static_cast<float*>(MemAlloc(sizeof(float) * 2 * MeshRef.vertexCount));
        MeshRef.texcoords2 = static_cast<float*>(MemAlloc(sizeof(float) * 2 * MeshRef.vertexCount));
        MeshRef.colors = nullptr;	// static_cast<unsigned char*>(MemAlloc(sizeof(unsigned char) * 4 * MeshRef.vertexCount));

        MeshRef.animNormals = nullptr;
        MeshRef.animVertices = nullptr;
        MeshRef.boneIds = nullptr;
        MeshRef.boneWeights = nullptr;
        MeshRef.tangents = nullptr;
        MeshRef.indices = nullptr;
    }

    //inline void SetNormal(Vector3& value) { Normal = value; }
    //inline void SetNormal(float x, float y, float z) { Normal = Vector3{ x,y,z }; }
    inline void SetSetUV(Vector2& value) { UV = value; }
    inline void SetSetUV(float x, float y) { UV = Vector2{ x,y }; }
    inline void SetSetUV2(float x, float y) { UV2 = Vector2{ x,y }; }

    inline void PushVertex(Vector3 vertex, float xOffset = 0, float yOffset = 0, float zOffset = 0)
    {
        size_t index = TriangleIndex * 12 + VertIndex * 3;

        if (MeshRef.colors != nullptr)
        {
            MeshRef.colors[index] = VertColor.r;
            MeshRef.colors[index + 1] = VertColor.g;
            MeshRef.colors[index + 2] = VertColor.b;
            MeshRef.colors[index + 3] = VertColor.a;
        }

        if (MeshRef.texcoords != nullptr)
        {
            index = TriangleIndex * 6 + VertIndex * 2;
            MeshRef.texcoords[index] = UV.x;
            MeshRef.texcoords[index + 1] = UV.y;
        }

        if (MeshRef.texcoords2 != nullptr)
        {
            index = TriangleIndex * 6 + VertIndex * 2;
            MeshRef.texcoords2[index] = UV2.x;
            MeshRef.texcoords2[index + 1] = UV2.y;
        }

        index = TriangleIndex * 9 + VertIndex * 3;
        MeshRef.vertices[index] = vertex.x + xOffset;
        MeshRef.vertices[index + 1] = vertex.y + yOffset;
        MeshRef.vertices[index + 2] = vertex.z + zOffset;

        VertIndex++;
        if (VertIndex > 2)
        {
            TriangleIndex++;
            VertIndex = 0;
        }
    }

protected:
    Mesh& MeshRef;

    size_t TriangleIndex = 0;
    size_t VertIndex = 0;

    Vector3 Normal = { 0,0,0 };
    Color VertColor = WHITE;
    Vector2 UV = { 0,0 };
    Vector2 UV2 = { 0,0 };
};

constexpr uint16_t SectorSize = 256;

class TerrainSector
{
public:
    std::vector<float> heightmap;
    std::vector<Vector3> normals;

    float textureSize = 64;

    uint16_t width = SectorSize;
    uint16_t height = SectorSize;

    void Setup()
    {
        heightmap.reserve(width * height);
        normals.reserve(width * height);

        for (uint16_t v = 0; v < height; v++)
        {
            for (uint16_t h = 0; h < width; h++)
            {
                heightmap.push_back(0);
                normals.emplace_back(Vector3{ 0,1,0 });
            }
        }
    }

    void SetupImage(Image& img)
    {
        ImageResize(&img, width, height);

        for (uint16_t v = 0; v < height; v++)
        {
            for (uint16_t h = 0; h < width; h++)
            {
                float param = GetImageColor(img, h, v).r / 255.0f;

                param *= 35; // scale;

                SetHeightmapValue(h, v, param);
            }
        }
    }

    inline size_t GetIndex(uint16_t h, uint16_t v)
    {
        return (size_t(v) * width) + h;
    }

    bool IsPosValid(uint16_t h, uint16_t v)
    {
        return (h >= 0 && h < width && v >= 0 && v < height);
    }

    float GetHeightmapValue(uint16_t h, uint16_t v)
    {
        if (heightmap.size() == 0)
            Setup();

        if (!IsPosValid(h, v))
            return 0;

        return heightmap[GetIndex(h, v)];
    }

    Vector3 GetNormalVector(uint16_t h, uint16_t v)
    {
        if (heightmap.size() == 0)
            Setup();

        if (!IsPosValid(h, v))
            return Vector3{ 0,0,1 };

        return normals[GetIndex(h, v)];
    }

    void SetHeightmapValue(uint16_t x, uint16_t y, float value)
    {
        if (heightmap.size() == 0)
            Setup();
        heightmap[GetIndex(x, y)] = value;
    }

    std::vector<Vector3> GetSiblingNormals(uint16_t h, uint16_t v)
    {
        std::vector<Vector3> tempNormals;

        Vector3 P = { 0,0,0 };

        float thisH = GetHeightmapValue(h, v);

        /*
                B
            A	P	C
                D
        */


        Vector3 A = { -1, 0, GetHeightmapValue(h - 1,v) - thisH };
        Vector3 B = { 0	, 1, GetHeightmapValue(h,v + 1) - thisH };
        Vector3 C = { 1	, 0, GetHeightmapValue(h + 1,v) - thisH };
        Vector3 D = { 0, -1, GetHeightmapValue(h,v - 1) - thisH };

        Vector3 PA = Vector3Normalize(Vector3Subtract(A, P));
        Vector3 PB = Vector3Normalize(Vector3Subtract(B, P));
        Vector3 PC = Vector3Normalize(Vector3Subtract(C, P));
        Vector3 PD = Vector3Normalize(Vector3Subtract(D, P));

        if (IsPosValid(h - 1, v) && IsPosValid(h, v + 1))
            tempNormals.push_back(Vector3CrossProduct(PB, PA));

        if (IsPosValid(h, v + 1) && IsPosValid(h + 1, v))
            tempNormals.push_back(Vector3CrossProduct(PC, PB));

        if (IsPosValid(h + 1, v) && IsPosValid(h, v - 1))
            tempNormals.push_back(Vector3CrossProduct(PD, PC));

        if (IsPosValid(h, v + 1) && IsPosValid(h - 1, v))
            tempNormals.push_back(Vector3CrossProduct(PA, PD));

        return tempNormals;
    }

    void BuildMesh(Mesh& mesh)
    {
        GeomtryBuilder builder(mesh);
        builder.Allocate(((width - 1) * (height - 1)) * 2);

        int triangleIndex = 0;
        int vertIndex = 0;

        for (uint16_t v = 0; v < height - 1; v++)
        {
            for (uint16_t h = 0; h < width - 1; h++)
            {

                auto setVert = [&builder, this](uint16_t _h, uint16_t _v)
                    {
                        //builder.SetNormal(GetNormalVector(_h, _v));
                        builder.SetSetUV((_h / float(width)) * textureSize, (_v / float(height)) * textureSize);
                        builder.SetSetUV2((_h / float(width)), (_v / float(height)));
                        builder.PushVertex(Vector3{ float(_h),float(_v), GetHeightmapValue(_h,_v) });
                    };

                setVert(h, v);
                setVert(h + 1, v);
                setVert(h + 1, v + 1);

                setVert(h, v);
                setVert(h + 1, v + 1);
                setVert(h, v + 1);

            }
        }
    }
};


Renderer::Renderer() {
    InitWindow(kWindowWidth, kWindowHeight, "Terrain");

    TerrainSector sector;
    sector.Setup();

    Image img = LoadImage("../sample/resources/terrain/terrain.png");
    sector.SetupImage(img);
    UnloadImage(img);
    // cleanup


    sector.BuildMesh(mesh);

    UploadMesh(&mesh, false);
}

Renderer::~Renderer() {
    CloseWindow();
}

void Renderer::DrawSelf() {
    rlFPCamera viewCamera;
    viewCamera.HideCursor = false;
    viewCamera.Setup(50, Vector3{ 0,-10,20 }, true);
    viewCamera.MoveSpeed.x = 20;
    viewCamera.MoveSpeed.y = 20;
    viewCamera.MoveSpeed.z = 20;

    Material mat = LoadMaterialDefault();

    Material wireMat = LoadMaterialDefault();
    wireMat.maps[MATERIAL_MAP_ALBEDO].color = BLACK;

    // load basic lighting
    Shader lightShader = LoadShader("../sample/resources/shaders/base_lighting.vs", "../sample/resources/shaders/lighting.fs");
    lightShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(lightShader, "viewPos");



    int texture1Loc = GetShaderLocation(lightShader, "texture1");
    SetShaderValueTexture(lightShader, texture1Loc, textures[1]);

    int texture2Loc = GetShaderLocation(lightShader, "texture2");
    SetShaderValueTexture(lightShader, texture2Loc, textures[2]);

    int texture3Loc = GetShaderLocation(lightShader, "texture3");
    SetShaderValueTexture(lightShader, texture3Loc, textures[3]);

    int maskLoc = GetShaderLocation(lightShader, "mask0");
    SetShaderValueTexture(lightShader, maskLoc, mask);

    mat.shader = lightShader;
    mat.maps[MATERIAL_MAP_ALBEDO].texture = textures[0];


    // game loop
    while (!WindowShouldClose())
    {
        // to block mouse when button is unpressed
        viewCamera.UseMouseX = viewCamera.UseMouseY = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        viewCamera.Update();

        Vector3 tmp = viewCamera.GetCameraPosition();
        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        SetShaderValue(lightShader, lightShader.locs[SHADER_LOC_VECTOR_VIEW], &tmp, SHADER_UNIFORM_VEC3);

        // drawing
        BeginDrawing();
        // this may be not useful
        //DrawTexture(maskTexture, 0, 0, WHITE);
        ClearBackground(SKYBLUE);

        //BeginMode3D(viewCamera.GetCamera());
        viewCamera.BeginMode3D();

        rlPushMatrix();

        SetShaderValueTexture(lightShader, texture1Loc, textures[1]);
        SetShaderValueTexture(lightShader, texture2Loc, textures[2]);
        SetShaderValueTexture(lightShader, texture3Loc, textures[3]);
        SetShaderValueTexture(lightShader, maskLoc, mask);

        DrawMesh(mesh, mat, MatrixIdentity());


        rlPopMatrix();

        EndMode3D();

        DrawFPS(0, 0);

        DrawText(TextFormat("x%0.2f y%0.2f z%0.2f", viewCamera.GetCamera().position.y, viewCamera.GetCamera().position.x, viewCamera.GetCamera().position.z), 10, 40, 20, WHITE);

        EndDrawing();
    }
}

void Renderer::SetTextureI(int ind, const std::string& path) {
    if (ind < 0 || ind>3)
        throw std::exception("In SetTextureI is wrong texture index");

    Image img = LoadImage(path.c_str());
    if (!IsImageReady(img)) {
        throw std::exception("SetTextureI couldnt find texture file");
    }
    textures[ind] = LoadTextureFromImage(img);
    UnloadImage(img);
    GenTextureMipmaps(&textures[ind]);
    SetTextureFilter(textures[ind], TEXTURE_FILTER_TRILINEAR);
}

void Renderer::SetMask(const std::string& path) {
    Image img = LoadImage(path.c_str());
    if (!IsImageReady(img)) {
        throw std::exception("SetMask couldnt find mask file");
    }
    mask = LoadTextureFromImage(img);
    UnloadImage(img);
    SetTextureFilter(mask, TEXTURE_FILTER_BILINEAR);
}
