#include <stdio.h>
#include<stdlib.h>
#include <math.h>

int main() {

    FILE *fp;

    fp = fopen("part1sequence", "rb");

    if(fp == NULL){
        printf("error\n");
        exit(1);
    }

    unsigned long x;
    int bits[4096][64];

    printf("output:\n");

    int table[7] = {2, 4, 1, 7, 3, 5, 6};
    int p = 0;
    int i = 0;
    int d = 0;
    size_t v;
    while((v = fread(&x, sizeof(x), 1, fp)) > 0){

        for(int k = 63; k >= 0; k--){
            bits[i][k] = x&1;
            x>>=1;
        }
        printf("Logical Address %d: ", i);

        for(int l = 0; l < 64; l++){
            printf("%d", bits[i][l]);
        }

        printf("\n");
        int m = 0;
        for(int o = 56; o >=52; o--){
            if(bits[i][o] == 1){
                //printf("i = %d m = %d\n", i, m);
                p += (int) pow(2, m);
            }
            m++;
        }
        int q = 0;
        for(int o = 63; o >=57; o--){
            if(bits[i][o] == 1){
                //printf("i = %d q = %d\n", i, q);
                d += (int) pow(2, q);
            }
            q++;
        }

        int shiftBit = table[p];
        for(int r = 56; r >= 53; r--){
            bits[i][r] = shiftBit&1;
            shiftBit>>=1;
        }

        printf("page table index: %d\n", p);
        printf("frame #: %d\n", table[p]);
        printf("frame offset: %d", d);


        printf("\nPhysical Address: ");
        for(int l = 0; l < 64; l++){
            printf("%d", bits[i][l]);
        }

        i += (int) v;
        p = 0;
        d = 0;
        printf("\n\n");
    }


    return 0;
}