#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void convertToGrayscale(const char* inputFilePath, const char* outputFilePath) {
    FILE* input = fopen(inputFilePath, "rb");
    if (input == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE* output = fopen(outputFilePath, "wb");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return;
    }

    unsigned char buffer[3];
    while (fread(buffer, sizeof(unsigned char), 3, input) == 3) {
        unsigned char r = buffer[0];
        unsigned char g = buffer[1];
        unsigned char b = buffer[2];
        unsigned char average = (unsigned char)(0.299 * r + 0.589 * g + 0.114 * b);

        // Write the calculated grayscale value to the output file
        fwrite(&average, sizeof(unsigned char), 1, output);
    }

    fclose(output);
    fclose(input);
    printf("Conversion complete: %s -> %s\n", inputFilePath, outputFilePath);
}

int main() {
    convertToGrayscale("back_ground_raw.dat", "back_ground_raw_gray.dat");
    convertToGrayscale("Object1_raw.dat", "Object1_raw_gray.dat");
    convertToGrayscale("Object2_raw.dat", "Object2_raw_gray.dat");
    return 0;
}
