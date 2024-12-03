#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define hang 256
#define cot 256

int main(){
    unsigned char buffer[4];
    unsigned char temp[6];
    unsigned char temp1[6];

    int count = 0;
    FILE* f, *out;    
    f = fopen("YCbCr_422.dat","rb");
    out = fopen("YCbCr_to_RGB.dat","wb");
    while (fread(buffer, sizeof(unsigned char), 4, f) == 4) {
        //doi sang 444
        temp[0] = buffer[0];
        temp[1] = buffer[1];
        temp[2] = buffer[2];
        temp[3] = buffer[3];
        temp[4] = buffer[1];
        temp[5] = buffer[2];
        //doi sang RGB
        temp1[0] = temp[0] +  1.402 * (temp[2] - 128);
        temp1[1] = temp[0] - 0.344 * (temp[1] - 128) - 0.714 * (temp[2] - 128);
        temp1[2] = temp[0] + 1.772 * (temp[1] - 128);
        temp1[3] = temp[3] +  1.402 * (temp[2] - 128);
        temp1[4] = temp[3] - 0.344 * (temp[1] - 128) - 0.714 * (temp[2] - 128);
        temp1[5] = temp[3] + 1.772 * (temp[1] - 128);
   
        fwrite(&temp1, sizeof(unsigned char), 6, out);
    }
    fclose(f);
    fclose(out);
    printf("\nDa xuat ra file YCbCr_to_RGB.dat");
    return 0;
}