#ifndef MATERIAL_11012024
#define MATERIAL_11012024

#include <raylib.h>

#include <string>
#include <vector>

#define GLSL_VERSION 330

class Renderer {
private:
    static const int kWindowHeight = 1080;
    static const int kWindowWidth = 1920;
    static const int kNumOfTextureBinds = 3;

    Model model = { 0 };
    Shader shader = { 0 };
    
    // textures can be different in size
    // texture0 is the base texture
    Texture2D textures[kNumOfTextureBinds];
    // invariant that masks sum are 1
    // also masks should have the same width and height
    Texture2D mask;

public:
    // here we init context
    Renderer();
    // and here we close
    ~Renderer();
    void SetMesh(std::string path);
    void SetTexture(int ind, std::string path);
    void SetMask(std::string path);
    void DrawSelf();
};

#endif