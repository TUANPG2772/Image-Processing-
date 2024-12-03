// tu file raw.dat xuat ra file YCbCr_422.dat, YCbCr_444.dat

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define hang 256
#define cot 256


int main() {
	FILE* f;
	f = fopen("lena_raw.dat","rb");

    unsigned char Y[hang*cot];
    unsigned char Cb[hang*cot];
    unsigned char Cr[hang*cot];

    unsigned char buffer[3];
    unsigned char buffer1;

    int count = 0;
    //doc file
    while (fread(buffer, sizeof(unsigned char), 3, f) == 3) {
        //lay 3 gia tri R, G, B
        unsigned char r = buffer[0];
        unsigned char g = buffer[1];
        unsigned char b = buffer[2];
        //tinh toan YCbCr
        unsigned char y = 0.299 * r + 0.587 * g + 0.114 * b;
        unsigned char cb = -0.169 * r - 0.331 * g + 0.500 * b + 128;
        unsigned char cr = 0.5 * r - 0.419 * g - 0.081 * b + 128;
        //luu cac gia tri y, cb, cr vao 3 mang 1 chieu Y, Cb, Cr 
        Y[count] = y;
        Cb[count] = cb;
        Cr[count] = cr;
        //tang bien dem
        count = count + 1;
    }
	fclose(f);

    //4:4:4 => 4:2:2
    FILE* output1 = fopen("YCbCr_422.dat", "wb");
    for (int i=0;i<hang*cot;i++){
        if (i%2 == 0){
            buffer[0] =  Y[i];
            buffer[1] = Cb[i];
            buffer[2] = Cr[i];
            fwrite(&buffer, sizeof(unsigned char), 3, output1);
        } else
        if (i%2 == 1){
            buffer1 = Y[i];
            fwrite(&buffer1, sizeof(unsigned char), 1, output1);
        }
    }
    //xuat ra file YCbCr_422.dat
    fclose(output1);
    printf("\nDa xuat ra YCbCr_422.dat!");

	return 0;
}