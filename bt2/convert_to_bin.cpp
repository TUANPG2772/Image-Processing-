#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main() {
    FILE* f;
    f = fopen("output.dat", "rb");
    FILE* output = fopen("convolved_bin.dat", "wb");

    unsigned char buffer[8];
    
    while (fread(buffer, sizeof(unsigned char), 8, f) == 8) {
        unsigned int t0 = 0;
        unsigned char t1 = 0;
        for (int i = 0; i < 8; i++) {
            t1 = buffer[i];
            if (t1 > 10) {
                t0 = t0 ^ 1;
            }
            t0 = t0 << 1;
        }
        t0 = t0 >> 1;
        fwrite(&t0, sizeof(unsigned char), 1, output);
    }
    fclose(output);
    fclose(f);
    printf("Done!");
    return 0;
}