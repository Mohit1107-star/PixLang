#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <fstream>
#include <sstream>
#include <string>

void apply_grayscale(unsigned char* data, int width, int height, int channels) {
    if (channels < 3) return;

    for (int i = 0; i < width * height; ++i) {
        int index = i * channels;
        unsigned char r = data[index];
        unsigned char g = data[index + 1];
        unsigned char b = data[index + 2];

        unsigned char gray = static_cast<unsigned char>((r + g + b) / 3);

        data[index]     = gray;
        data[index + 1] = gray;
        data[index + 2] = gray;
    }
}

void apply_blur(unsigned char* data, int width, int height, int channels, int kernelSize) {
    if (channels < 3 || kernelSize < 1) return;

    int half = kernelSize / 2;
    int size = width * height * channels;
    std::vector<unsigned char> copy(data, data + size);

    for (int y = half; y < height - half; ++y) {
        for (int x = half; x < width - half; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int ky = -half; ky <= half; ++ky) {
                for (int kx = -half; kx <= half; ++kx) {
                    int ix = (y + ky) * width + (x + kx);
                    sumR += copy[ix * channels];
                    sumG += copy[ix * channels + 1];
                    sumB += copy[ix * channels + 2];
                }
            }

            int kernelArea = kernelSize * kernelSize;
            int idx = (y * width + x) * channels;
            data[idx]     = sumR / kernelArea;
            data[idx + 1] = sumG / kernelArea;
            data[idx + 2] = sumB / kernelArea;
        }
    }
}

void apply_sharpen(unsigned char* data, int width, int height, int channels, int weight) {
    if (channels < 3) return;

    std::vector<unsigned char> copy(data, data + width * height * channels);

    // Laplacian kernel for sharpening
    int kernel[3][3] = {
        { 0, -1,  0 },
        {-1,  4 + weight, -1},
        { 0, -1,  0 }
    };

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int ix = (y + ky) * width + (x + kx);
                    int k = kernel[ky + 1][kx + 1];
                    sumR += copy[ix * channels]     * k;
                    sumG += copy[ix * channels + 1] * k;
                    sumB += copy[ix * channels + 2] * k;
                }
            }

            int idx = (y * width + x) * channels;
            data[idx]     = std::clamp(sumR, 0, 255);
            data[idx + 1] = std::clamp(sumG, 0, 255);
            data[idx + 2] = std::clamp(sumB, 0, 255);
        }
    }
}


int main() {
    int width, height, channels;
    unsigned char* img = stbi_load("../assets/sample.jpg", &width, &height, &channels, 0);

    if (!img) {
        std::cerr << "Failed to load image.\n";
        return 1;
    }

    std::cout << "Loaded image: " << width << "x" << height << " (" << channels << " channels)\n";

    //apply_grayscale(img, width, height, channels);
    //apply_blur(img, width, height, channels, 5);  // blur kernel size 5
    std::ifstream dslFile("../filters.dsl");
    std::string line;

    while (std::getline(dslFile, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "grayscale") {
            apply_grayscale(img, width, height, channels);
        } else if (cmd == "blur") {
            int strength = 3;  // default
            iss >> strength;
            apply_blur(img, width, height, channels, strength);
        } else if (cmd == "sharpen") {
            int weight = 1;
            iss >> weight;
            apply_sharpen(img, width, height, channels, weight);
        }        
        else {
            std::cerr << "Unknown command in DSL: " << cmd << std::endl;
        }
    }

    stbi_write_jpg("../assets/output.jpg", width, height, channels, img, 90);
    stbi_image_free(img);

    std::cout << "Saved output.jpg\n";
    return 0;
}
