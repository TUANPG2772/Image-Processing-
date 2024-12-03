#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define hang 256
#define cot 256

// tinh PSNR 2 ma tran
double calculate_psnr(unsigned char a[hang*cot], unsigned char b[hang*cot]) {
    double mse = 0.0;

    for (int i = 0; i < hang*cot; ++i) {
        mse = mse + (a[i] - b[i])*(a[i] - b[i]);
    }

    mse = mse / (hang*cot);

    double psnr = 10.0 * log10((255 * 255) / mse);
    return psnr;
}

int main() 	{
    FILE* f;
	f = fopen("lena_raw.dat","rb");

    unsigned char R1[hang*cot];
    unsigned char G1[hang*cot];
    unsigned char B1[hang*cot];

    unsigned char buffer[3];
    int count = 0;
    //doc file
    while (fread(buffer, sizeof(unsigned char), 3, f) == 3) {
        //lay 3 gia tri R, G, B
        unsigned char r = buffer[0];
        unsigned char g = buffer[1];
        unsigned char b = buffer[2];

        //luu cac gia tri R, G, B vao 3 mang 1 chieu R1, G1, B1
        R1[count] = r;
        G1[count] = g;
        B1[count] = b;
        //tang bien dem
        count = count + 1;
    }
	fclose(f);

    FILE* f1;
	f1 = fopen("YCbCr_to_RGB.dat","rb");

    unsigned char R2[hang*cot];
    unsigned char G2[hang*cot];
    unsigned char B2[hang*cot];

    count = 0;
    //doc file
    while (fread(buffer, sizeof(unsigned char), 3, f1) == 3) {
        //lay 3 gia tri R, G, B
        unsigned char r = buffer[0];
        unsigned char g = buffer[1];
        unsigned char b = buffer[2];

        //luu cac gia tri R, G, B vao 3 mang 1 chieu R2, G2, B2
        R2[count] = r;
        G2[count] = g;
        B2[count] = b;
        //tang bien dem
        count = count + 1;
    }
	fclose(f1);

    for (int i=0;i<3;i++){
        if (i==0) printf("\nPSNR kenh R: %.1f",calculate_psnr(R1,R2));
        else
        if (i==1) printf("\nPSNR kenh G: %.1f",calculate_psnr(G1,G2));
        else
        if (i==2) printf("\nPSNR kenh B: %.1f",calculate_psnr(B1,B2));
    }
}