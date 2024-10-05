#ifndef MATERIAL_11012024
#define MATERIAL_11012024


#include <raylib.h>

#include <string>

#define GLSL_VERSION            330


    class Renderer {
    private:
        Mesh mesh = { 0 };
        const int kWindowHeight = 1080;
        const int kWindowWidth = 1920;
        static const int kNumOfTextBinds = 4; // 0 is a base texture

        // textures can be different in size
        // texture0 is the base texture
        Texture2D textures[kNumOfTextBinds];
        // invariant that masks sum are 1
        // also masks should have the same width and height
        Texture2D mask;

    public:
        // here we init context
        Renderer();
        // and here we close
        ~Renderer();
        
        void SetTextureI(int, const std::string&);
        void SetMask(const std::string&);
        void DrawSelf();
    };

    
#endif