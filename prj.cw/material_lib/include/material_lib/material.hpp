#ifndef MATERIAL_11012024
#define MATERIAL_11012024

#include <raylib.h>

#include <string>
#include <vector>

class Renderer {
private:
    static const int kWindowHeight = 1080;
    static const int kWindowWidth = 1920;
    static const int kNumOfTextureBinds = 3;

    Model model = { 0 };
    Shader shader = { 0 };
    
    // textures can be different in size
    Image textures[kNumOfTextureBinds];
    // invariant that masks sum are 1
    // also masks should have the same width and height
    Image masks[kNumOfTextureBinds];

    // image should have PIXELFORMAT_UNCOMPRESSED_GRAYSCALE format
    //void ApplyGaussianBlur(Image& image, int radius, float sigma);

    void BlendMasks();
public:
    // here we init context
    Renderer();
    // and here we close
    ~Renderer();
    void SetMesh(std::string path);
    void SetTexture(int ind, std::string path);
    void SetMask(int ind, std::string path);
    void DrawSelf();
};

#endif