#include "include/material_lib/material.hpp"

#include <raymath.h>

#include <string>
#include <sstream>
#include <vector>

//void Renderer::ApplyGaussianBlur(Image& inputImage, int radius, float sigma)
//{
//    // Creating output image
//    Image outputImage = GenImageColor(inputImage.width, inputImage.height, BLANK);
//
//    /*Color* pixels = (Color*)RL_CALLOC(inputImage.width * inputImage.height, sizeof(Color));
//    for (int i = 0; i < inputImage.width * inputImage.height; ++i) {
//        pixels[i] = inputImage.data[i];
//    }*/
//
//    // Apply Gaussian blur
//    for (int y = 0; y < inputImage.height; y++)
//    {
//        for (int x = 0; x < inputImage.width; x++)
//        {
//            float sum = 0.0;
//            float totalWeight = 0.0;
//
//            // Apply Gaussian blur in the neighborhood of each pixel
//            for (int j = -radius; j <= radius; j++)
//            {
//                for (int i = -radius; i <= radius; i++)
//                {
//                    int neighborX = x + i;
//                    int neighborY = y + j;
//
//                    // Ensure neighbor coordinates are within bounds
//                    if (neighborX >= 0 && neighborX < inputImage.width &&
//                        neighborY >= 0 && neighborY < inputImage.height)
//                    {
//                        // NOTE: Calculate grayscale equivalent color
//                        // Vector3 coln = { (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f };
//                        //unsigned char gray = (unsigned char)((coln.x * 0.299f + coln.y * 0.587f + coln.z * 0.114f) * 255.0f);
//
//                        // ((unsigned char *)dst->data)[y*dst->width + x]
//                        Color pixel = ((Color*)inputImage.data)[neighborX + neighborY * inputImage.width];
//                        float weight = exp(-(i * i + j * j) / (2 * sigma * sigma));
//
//                        sum += (pixel.r + pixel.g + pixel.b) / 3 * weight;
//                        totalWeight += weight;
//                    }
//                }
//            }
//
//            // Normalize and set the blurred pixel value
//            Color blurredPixel = { (unsigned char)(sum / totalWeight), (unsigned char)(sum / totalWeight), (unsigned char)(sum / totalWeight), 255 };
//            ImageDrawPixel(&outputImage, x, y, blurredPixel);
//        }
//    }
//}

//int main() {
//    const int screenWidth = 800;
//    const int screenHeight = 600;
//
//    InitWindow(screenWidth, screenHeight, "Gaussian Blur");
//
//    // Load input image
//    Image inputImage = LoadImage("input_image.png");
//    if (inputImage.data == NULL) {
//        printf("Failed to load input image\n");
//        return -1;
//    }
//
//    // Apply Gaussian blur
//    ApplyGaussianBlur(&inputImage, 5); // Adjust radius as needed
//
//    // Save the blurred image
//    ExportImage(inputImage, "blurred_image.png");
//
//    // Unload resources
//    UnloadImage(inputImage);
//
//    CloseWindow();
//
//    return 0;
//}

void Renderer::BlendMasks() {
    for (int i = 0; i < kNumOfTextureBinds; ++i) {
        ApplyGaussianBlur(masks[i], 5, 0.5);
    }
    for (int im_y = 0; im_y < masks[0].height; ++im_y) {
        for (int im_x = 0; im_x < masks[0].width; ++im_x) {
            
        }
    }
}

void Renderer::DrawSelf() {

    

    // here create shader
    // initialize it
    // and before blur and normalize maps

    /*Camera camera = { {5.0f, 5.0f,5.0f}, {0.0f,0.0f, 0.0f},
        {0.0f,1.0f,0.0f},45.0f,CAMERA_FREE };
    Vector3 position = { 0.0f, -1.0f, -1.0f };*/

    Camera camera = { 0 };
    camera.position = Vector3{ 3.0f, 3.0f, 3.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    
    Vector3 position = { 0.0f, 0.0f, 0.0f };

    shader = LoadShader(0, "texture_blending.fs");

    SetShaderValue(shader, GetShaderLocation(shader, "texture0"), &textures[0], SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "texture1"), &textures[1], SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "texture2"), &textures[2], SHADER_UNIFORM_INT);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        BeginShaderMode(shader);

        DrawModel(model, position, 1.0f, WHITE);

        EndShaderMode();

        EndMode3D();

        EndDrawing();
    }
}

Renderer::Renderer() {
    InitWindow(kWindowWidth, kWindowHeight, "grid landscape");
    for (int i_text = 0; i_text < kNumOfTextureBinds; i_text++) {
        textures[i_text] = GenImageColor(1, 1, BLANK);
        masks[i_text] = GenImageColor(1, 1, BLANK);
    }
}
Renderer::~Renderer() {
    UnloadShader(shader); // Unload shader
    for (int text_ind = 0; text_ind < kNumOfTextureBinds; ++text_ind) {
        UnloadImage(textures[text_ind]);
        UnloadImage(masks[text_ind]);
    }
    UnloadModel(model);
    CloseWindow();
}

// load data from files and upload to vram
void Renderer::SetMesh(std::string path) {

    model = LoadModel(path.c_str());

}

void Renderer::SetTexture(int ind, std::string path) {

    if (ind < 0 || ind > 2)
        throw std::exception("wrong texture index");

    textures[ind] = LoadImage(path.c_str());

    if (!IsImageReady(textures[ind])) {
        throw std::exception("cant load a texture");
    }

   /* model.materialCount = kNumOfTextureBinds;
    model.materials = (Material*)MemAlloc(sizeof(Material) * model.materialCount);

    for (int i = 0; i < model.materialCount; ++i) {
        model.materials[i] = LoadMaterialDefault();
        Image img = LoadImage(file_names[i].c_str());
        if (!IsImageReady(img)) {
            throw std::exception("cant load image");
        }
        Texture2D text = LoadTextureFromImage(img);
        UnloadImage(img);
        model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = text;
    }*/
}

void Renderer::SetMask(int ind, std::string path) {
    if (ind < 0 || ind > 2)
        throw std::exception("wrong texture index");

    masks[ind] = LoadImage(path.c_str());

    if (!IsImageReady(masks[ind])) {
        throw std::exception("cant load a mask texture");
    }
}






