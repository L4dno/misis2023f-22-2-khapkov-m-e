#ifndef MATERIAL_11012024
#define MATERIAL_11012024

const char* vertex = "#version 330\n"
"in vec3 vertexPosition;"
"in vec2 vertexTexCoord;"
"in vec2 vertexTexCoord2;"
"in vec3 vertexNormal;"
"in vec4 vertexColor;"
"uniform mat4 mvp;"
"uniform mat4 matModel;"
"uniform mat4 matNormal;"
"out vec3 fragPosition;"
"out vec2 fragTexCoord;"
"out vec2 fragTexCoord2;"
"out vec4 fragColor;"
"out vec3 fragNormal;"
"void main()"
"{"
"    // Send vertex attributes to fragment shader"
"    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));"
"    fragTexCoord = vertexTexCoord;"
"    fragTexCoord2 = vertexTexCoord2;"
"    fragColor = vertexColor;"
"    fragNormal = normalize(vec3(matNormal * vec4(vertexNormal, 1.0)));"
"    gl_Position = mvp * vec4(vertexPosition, 1.0);"
"}";
const char* fragment = "#version 330\n"
"in vec3 fragPosition;"
"in vec2 fragTexCoord;"
"in vec2 fragTexCoord2;"
"in vec4 fragColor;"
"in vec3 fragNormal;"
"uniform sampler2D texture0;"
"uniform sampler2D texture1;"
"uniform sampler2D texture2;"
"uniform sampler2D texture3;"
"uniform sampler2D mask0;"
"uniform vec4 colDiffuse;"
"out vec4 finalColor;"
"void main()"
"{"
"    vec4 mask = texture(mask0, fragTexCoord2);"
"    vec4 baseColor = texture(texture0, fragTexCoord);"
"    vec4 layer1Color = texture(texture1, fragTexCoord);"
"    vec4 texelColor = mix(layer1Color, baseColor, mask.r);"
"    vec4 layer2Color = texture(texture2, fragTexCoord);"
"    texelColor = mix(layer2Color, texelColor, mask.g);"
"    vec4 layer3Color = texture(texture3, fragTexCoord);"
"    texelColor = mix(layer3Color, texelColor, mask.b);"
"    finalColor = texelColor;"
"}"
;

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