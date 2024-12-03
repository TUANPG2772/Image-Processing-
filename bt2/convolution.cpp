#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define IMAGE_WIDTH  256
#define IMAGE_HEIGHT 256

// Function to load a binary image from a file
void loadBinaryImage(const char *filename, uint8_t *image) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        fread(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}

// Function to save a binary image to a file
void saveBinaryImage(const char *filename, uint8_t *image) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}

// Function to perform Sobel edge detection
void sobelEdgeDetection(uint8_t *inputImage, uint8_t *outputImage) {
    int x, y, i, j;
    int gx, gy;
    int sobel_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int sobel_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    for (y = 1; y < IMAGE_HEIGHT - 1; y++) {
        for (x = 1; x < IMAGE_WIDTH - 1; x++) {
            gx = 0;
            gy = 0;
            for (j = -1; j <= 1; j++) {
                for (i = -1; i <= 1; i++) {
                    gx += sobel_x[j + 1][i + 1] * inputImage[(y + j) * IMAGE_WIDTH + (x + i)];
                    gy += sobel_y[j + 1][i + 1] * inputImage[(y + j) * IMAGE_WIDTH + (x + i)];
                }
            }
            outputImage[y * IMAGE_WIDTH + x] = (uint8_t)(sqrt(gx * gx + gy * gy)/8); // Scaling for visualization
        }
    }
}

int main() {
    uint8_t *inputImage = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    uint8_t *outputImage = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);

    loadBinaryImage("gray.dat", inputImage);

    sobelEdgeDetection(inputImage, outputImage);

    saveBinaryImage("output.dat", outputImage);

    free(inputImage);
    free(outputImage);
    printf("Done");
    return 0;
}
