#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <stdlib.h>
#define PADDING 2 // Padding size

#define IMAGE_WIDTH  256
#define IMAGE_HEIGHT 256

#define BLOCK_SIZE 64
#define NUM_BLOCKS (IMAGE_HEIGHT / BLOCK_SIZE)
#define RESULT_SIZE (NUM_BLOCKS * NUM_BLOCKS)



void read_image(const char* filename, uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE* file;
    if (fopen_s(&file, filename, "rb") == 0) {
        fread(image, 1, IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}

void save_image(const char* filename, uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    FILE* file;
    if (fopen_s(&file, filename, "wb") == 0) {
        fwrite(image, 1, IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}


void swap(uint8_t &a, uint8_t &b) {
    uint8_t temp = a;
    a = b;
    b = temp;
}


void calculateSumArray(uint8_t matrix[IMAGE_HEIGHT][IMAGE_WIDTH], int sums[RESULT_SIZE]) {
    for (int i = 0; i < IMAGE_HEIGHT; i += BLOCK_SIZE) {
        for (int j = 0; j < IMAGE_WIDTH; j += BLOCK_SIZE) {
            int sum = 0;
            for (int x = 0; x < BLOCK_SIZE; ++x) {
                for (int y = 0; y < BLOCK_SIZE; ++y) {
                    sum += matrix[i + x][j + y];
                }
            }
            sums[(i / BLOCK_SIZE) * NUM_BLOCKS + (j / BLOCK_SIZE)] = sum;
        }
    }
}

void convolution(uint8_t inputImage[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage1[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage2[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage3[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage4[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    int x, y;
    int verticalGradientMask[5][5] = {
      { 0, 1, 0, -1, 0 },
      { 0, 1, 0, -1, 0 },
      { 0, 1, 0, -1, 0 },
      { 0, 1, 0, -1, 0 },
      { 0, 1, 0, -1, 0 }
    };


    int horizontalGradientMask[5][5] = {
        {   0,   0,   0,   0,   0 },
        {   1,   1,   1,   1,   1 },
        {   0,   0,   0,   0,   0 },
        {  -1,  -1,  -1,  -1,  -1 },
        {   0,   0,   0,   0,   0 }
    };
    int plus45GradientMask[5][5] = {
       { 0,  0,  0,  1,  0 },
       { 0,  1,  1,  0, -1 },
       { 0,  1,  0, -1,  0 },
       { 1,  0, -1, -1,  0 },
       { 0, -1,  0,  0,  0 }
    };
    int minus45GradientMask[5][5] = {
       { 0, -1,  0,  0,  0 },
       { 1,  0, -1, -1,  0 },
       { 0,  1,  0, -1,  0 },
       { 0,  1,  1,  0, -1 },
       { 0,  0,  0,  1,  0 }
    };

    uint8_t paddedImage[IMAGE_HEIGHT + 2 * PADDING][IMAGE_WIDTH + 2 * PADDING] = { {0} };

    // Copy the original image to the center of the padded matrix
    for (y = PADDING; y < IMAGE_HEIGHT + PADDING; y++) {
        for (x = PADDING; x < IMAGE_WIDTH + PADDING; x++) {
            paddedImage[y][x] = inputImage[y - PADDING][x - PADDING];
        }
    }

    // Perform convolution with zero-padded image
    for (y = PADDING; y < IMAGE_HEIGHT + PADDING; y++) {
        for (x = PADDING; x < IMAGE_WIDTH + PADDING; x++) {
            int sobel1 = 0;
            int sobel2 = 0;
            int sobel3 = 0;
            int sobel4 = 0;
            for (int i = -2; i <= 2; i++) {
                for (int j = -2; j <= 2; j++) {
                    sobel1 += verticalGradientMask[i + 2][j + 2] * paddedImage[y + i][x + j];
                    sobel2 += horizontalGradientMask[i + 2][j + 2] * paddedImage[y + i][x + j];
                    sobel3 += plus45GradientMask[i + 2][j + 2] * paddedImage[y + i][x + j];
                    sobel4 += minus45GradientMask[i + 2][j + 2] * paddedImage[y + i][x + j];
                }
            }
            if (sobel1 < 0) {
                sobel1 = 0;
            }
            else if (sobel1 > 255) {
                sobel1 = 255;
            };
            if (sobel2 < 0) {sobel2 = 0;
            }
            else if (sobel2 > 255) {
                sobel2 = 255;
            };
            if (sobel3 < 0) {
                sobel3 = 0;
            }
            else if (sobel3 > 255) {
                sobel3 = 255;
            };
            if (sobel4 < 0) {
                sobel4 = 0;
            }
            else if (sobel4 > 255) {
                sobel4 = 255;
            };
            outputImage1[y - PADDING][x - PADDING] = (uint8_t)(sobel1);
            outputImage2[y - PADDING][x - PADDING] = (uint8_t)(sobel2);
            outputImage3[y - PADDING][x - PADDING] = (uint8_t)(sobel3);
            outputImage4[y - PADDING][x - PADDING] = (uint8_t)(sobel4);
        }
    }
}

void winnertakeall(uint8_t outputImage1[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage2[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage3[IMAGE_HEIGHT][IMAGE_WIDTH], uint8_t outputImage4[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    uint8_t temp[4];
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        temp[0] = 0;
        temp[1] = 0;
        temp[2] = 0;
        temp[3] = 0;

        for (int j = 0; j < IMAGE_WIDTH; j++) {
             temp[0] = outputImage1[i][j];
             temp[1] = outputImage2[i][j];
             temp[2] = outputImage3[i][j];
             temp[3] = outputImage4[i][j];
             
             uint8_t max = temp[0];
             int chiso = 0;
             
             for (int k =1;k<4;k++){
                if (temp[k]>max) {
                    max = temp[k];
                    chiso = k;
                }
             }

             if (max > 30) {
                for (int k = 0;k<4;k++){
                    if (k == chiso) {
                        temp[k] = 1;
                    } 
                    else temp[k] = 0;
                }
             } else if (max <= 30 ){
                temp[0] = 0;
                temp[1] = 0;
                temp[2] = 0;
                temp[3] = 0;
             }

             swap(temp[0],outputImage1[i][j]);
             swap(temp[1],outputImage2[i][j]);
             swap(temp[2],outputImage3[i][j]);
             swap(temp[3],outputImage4[i][j]);

        }       
    }   
}

double euclideanDistance(int vector1[], int vector2[]) {
    double sum_squared_diff = 0.0;

    for (int i = 0; i < 64; i++) {
        int diff = vector1[i] - vector2[i];
        sum_squared_diff += diff * diff;
    }

    return sqrt(sum_squared_diff);
}

int main() {

    uint8_t inputImage[IMAGE_HEIGHT][IMAGE_WIDTH];
    uint8_t outputImage1[IMAGE_HEIGHT][IMAGE_WIDTH];
    uint8_t outputImage2[IMAGE_HEIGHT][IMAGE_WIDTH];
    uint8_t outputImage3[IMAGE_HEIGHT][IMAGE_WIDTH];
    uint8_t outputImage4[IMAGE_HEIGHT][IMAGE_WIDTH];
    int sums1[RESULT_SIZE];
    int sums2[RESULT_SIZE];
    int sums3[RESULT_SIZE];
    int sums4[RESULT_SIZE];
    int finalArray[4 * RESULT_SIZE];
    int SV1[64] = {197, 39, 31, 72, 262, 90, 94, 112, 128, 33, 3, 101, 0, 105, 10, 77, 14, 343, 482, 104, 55, 394, 363, 46, 7, 231, 209, 0, 64, 64, 74, 63, 76, 171, 6, 36, 25, 54, 41, 35, 2, 37, 3, 31, 62, 68, 108, 104, 146, 552, 874, 240, 11, 321, 186, 37, 31, 106, 63, 38, 0, 21, 14, 26};
    int SV2[64] = {210, 48, 2, 251, 605, 35, 365, 280, 236, 51, 72, 276, 6, 231, 15, 243, 46, 291, 455, 194, 44, 284, 315, 19, 69, 231, 177, 20, 142, 166, 113, 89, 177, 161, 7, 54, 30, 59, 56, 71, 13, 21, 7, 68, 65, 79, 159, 135, 128, 107, 103, 273, 42, 568, 800, 132, 114, 50, 51, 107, 47, 137, 39, 65};
    
    //read_image("SV_gray_test.dat", inputImage);
    //read_image("SV1_gray.dat", inputImage);
    read_image("test_SV1_gray.dat", inputImage);


    //nhan chap voi 4 cua so
    convolution(inputImage, outputImage1, outputImage2, outputImage3, outputImage4);
    
    //winner take all: lay anh nhi phan
    winnertakeall(outputImage1,outputImage2,outputImage3,outputImage4);

    //tinh tong
    calculateSumArray(outputImage1, sums1);
    calculateSumArray(outputImage2, sums2);
    calculateSumArray(outputImage3, sums3);
    calculateSumArray(outputImage4, sums4);

    // Ghép kết quả thành một mảng 64 phần tử
    for (int i = 0; i < RESULT_SIZE; ++i) {
        finalArray[i] = sums1[i];
        finalArray[RESULT_SIZE + i] = sums2[i];
        finalArray[2 * RESULT_SIZE + i] = sums3[i];
        finalArray[3 * RESULT_SIZE + i] = sums4[i];
    }


    FILE *f;
    //f = fopen("SV_test.txt","w");
    //f = fopen("SV1.txt","w");
    f = fopen("SV.txt","w");
    for (int i = 0; i < 4 * RESULT_SIZE; ++i) {
        fprintf(f,"%d, ", finalArray[i]);
    }
    fclose(f);


    double distance1 = euclideanDistance(finalArray, SV1);
    double distance2 = euclideanDistance(finalArray, SV2);

    printf("Khoang cach so voi SV1: %f\n",distance1);
    printf("Khoang cach so voi SV2: %f\n",distance2);
    
    if (distance1<distance2) printf("Nhan dien: SV1");
    else if (distance1>distance2) printf("Nhan dien: SV2");

    save_image("doc.dat", outputImage1);
    save_image("ngang.dat", outputImage2);
    save_image("cheo1.dat", outputImage3);
    save_image("cheo2.dat", outputImage4);


    printf("\nDone!");
    return 0;
}