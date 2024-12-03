#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void convert_to_bin(FILE* inputImage,FILE* outputImage){
    
    unsigned char buffer[8];
    
    while (fread(buffer, sizeof(unsigned char), 8, inputImage) == 8) {
        unsigned int t0 = 0;
        unsigned char t1 = 0;
        for (int i = 0; i < 8; i++) {
            t1 = buffer[i];
            if (t1 == 0) {
                t0 = t0 ^ 1;
            }
            t0 = t0 << 1;
        }
        t0 = t0 >> 1;
        fwrite(&t0, sizeof(unsigned char), 1, outputImage);
    }
    fclose(outputImage);
    fclose(inputImage);
}


int main() {
    FILE* fin1,*fin2,*fin3,*fin4;
    FILE* fout1,*fout2,*fout3,*fout4;
    
    fin1 = fopen("doc.dat","rb");
    fout1 = fopen("doc_bin.dat","wb");

    fin2 = fopen("ngang.dat","rb");
    fout2 = fopen("ngang_bin.dat","wb");

    fin3 = fopen("cheo1.dat","rb");
    fout3 = fopen("cheo1_bin.dat","wb");

    fin4 = fopen("cheo2.dat","rb");
    fout4 = fopen("cheo2_bin.dat","wb");

    convert_to_bin(fin1,fout1);
    convert_to_bin(fin2,fout2);
    convert_to_bin(fin3,fout3);
    convert_to_bin(fin4,fout4);

    printf("Done!");
    return 0;
}