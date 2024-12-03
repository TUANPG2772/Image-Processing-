#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main() {
	FILE* f;
	f = fopen("test_SV1.dat","rb");
	FILE* output = fopen("test_SV1_gray.dat", "wb");

    unsigned char buffer[3];
    while (fread(buffer, sizeof(unsigned char), 3, f) == 3) {
        unsigned char r = buffer[0];
        unsigned char g = buffer[1];
        unsigned char b = buffer[2];
        unsigned char average = r*0.299 + g*0.589 + b*0.114;

        // Ghi giá trị trung bình vào tệp averaged_values.dat
        fwrite(&average, sizeof(unsigned char), 1, output);
    }

	fclose(output);
	fclose(f);
    printf("Done!");
	return 0;
}