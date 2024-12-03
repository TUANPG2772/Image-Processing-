#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define IMAGE_WIDTH  256
#define IMAGE_HEIGHT 256


void saveBinaryImage(const char *filename, uint8_t *image) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}

// Function to load a binary image from a file
void Gray_to_Array(const char *filename, uint8_t *image) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        fread(image, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, file);
        fclose(file);
    }
}

//take object
void Take_Object(uint8_t *back, uint8_t *object, uint8_t *output){
    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++){
        if (abs(*(back + i) - *(object + i)) < 10) *(output + i) = 255;
        else *(output + i) = 0;
    } 
}

//count y
int count_y(uint8_t *input ){
    unsigned char output[256];
    
    for (int i = 0; i< IMAGE_HEIGHT; i++){
        int count = 0;
        for (int j = 0; j<IMAGE_WIDTH; j++){
            if (*(input + i*IMAGE_HEIGHT + j) == 0 ) count = count +1;
        }
        output[255-i] = count;
    }

    int max = output[0];
    int chi_so_y = 0;
    for (int k = 1; k<256; k++){
        if (output[k] > max) {
            max = output[k];
            chi_so_y = k;
        }
    }

    return chi_so_y;
}

//count x
int count_x(uint8_t *input ){
    unsigned char output[256];
    
    for (int i = 0; i< IMAGE_HEIGHT; i++){
        int count = 0;
        for (int j = 0; j<IMAGE_WIDTH; j++){
            if (*(input + j*IMAGE_HEIGHT + i) == 0 ) count = count +1;
        }
        output[i] = count;
    }
    int max = output[0];
    int chi_so_x = 0;
    for (int k = 1; k<256; k++){
        if (output[k] > max) {
            max = output[k];
            chi_so_x = k;
        }
    }

    return chi_so_x;
}


int main() {
    uint8_t *back_ground = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    uint8_t *object1 = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    uint8_t *object2 = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);

    uint8_t *object1_foreground = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    uint8_t *object2_foreground = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);

    //uint8_t *output_test = (uint8_t *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);



    // load gray.dat to array
    Gray_to_Array("back_ground_raw_gray.dat", back_ground);
    Gray_to_Array("Object1_raw_gray.dat", object1);
    Gray_to_Array("Object2_raw_gray.dat", object2);

    // take object
    Take_Object(back_ground, object1, object1_foreground);
    Take_Object(back_ground, object2, object2_foreground);

    //xac dinh toa do vat
    int x0 = count_x(object1_foreground);
    int y0 = count_y(object1_foreground);
    int x1 = count_x(object2_foreground);
    int y1 = count_y(object2_foreground);

    printf("\nToa do vat 1 tren anh: (x, y) = (%d, %d)", x0, y0);
    printf("\nToa do vat 2 tren anh: (x, y) = (%d, %d)", x1, y1);
    if (x1 > x0) printf("\nVat di chuyen ve phia ben phai va cach vi tri ban dau %d pixel.",abs(x1 - x0));
    else printf("\nVat di chuyen ve phia ben trai va cach vi tri ban dau %d pixel.",abs(x1 - x0));

    //test
    saveBinaryImage("output1_test_gray.dat", object1_foreground);
    saveBinaryImage("output2_test_gray.dat", object2_foreground);


    free(back_ground);
    free(object1);
    free(object2);
    free(object1_foreground);
    free(object2_foreground);

    printf("\nDone");
    return 0;
}