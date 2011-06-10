#include <stdio.h>
#include <stdlib.h>

char *bits(char Rg) {

    unsigned char bit = 0x80;
    int i;
    char *bits;
    bits = (char*) malloc(9);
    for (i=0; i < 8; i++) {
        *(bits+i) = Rg & bit ? '1' : '0';
        bit >>= 1;
    }
    *(bits+i) = '\0';
    return bits;
}

int divide(char Rg1, char Rg2) {

    char Rg3, r=0;
    int i;

    printf("Rg1 : %s (%2d)\n", bits(Rg1), Rg1);
    printf("Rg2 : %s (%2d)\n", bits(Rg2), Rg2);
    Rg3 = Rg1;
    printf("Rg3 : %s (%2d)  <- copy of Rg1\n", bits(Rg3), Rg3);
    if (Rg1 < 0) {
        r = 0xff;
    }
    printf("rem : %s (%2d)  <- remainder after sign check\n", bits(r), r);

    for (i = 0; i < 8; i++) {

        printf("\n ------------ %d. ITERATION ------------\n", i+1);


        if (Rg3 & 0x80) {
            printf(" - left shift r and Rg3, carry\n");
            Rg3 <<= 1;
            r <<= 1;
            r += 1;
            printf(" > %s (%2d) | %s (%2d)\n", bits(r), r, bits(Rg3), Rg3);
        } else {
            printf(" - left shift r and Rg3\n");
            Rg3 <<= 1;
            r <<= 1;
            printf(" > %s (%2d) | %s (%2d)\n", bits(r), r, bits(Rg3), Rg3);
        }

        printf(" - add in the divisor\n");
        r += Rg2;
        printf(" > %s (%2d) | %s (%2d)\n", bits(r), r, bits(Rg3), Rg3);

        if (r >= 0) {
            printf(" - subtract the divisor and set the lowest bit of Rg3 to 1\n");
            r -= Rg2;
            Rg3 |= 0x01;
            printf(" > %s (%2d) | %s (%2d)\n", bits(r), r, bits(Rg3), Rg3);
        } else {
            printf(" - lowest bit of Rg3 stays 0\n");
            printf(" > %s (%2d) | %s (%2d)\n", bits(r), r, bits(Rg3), Rg3);
        }

    }

    // post division sign check
    if (Rg1 < 0 && Rg2 > 0) {
        Rg3++;
    }

    printf("\n%s (%d) / %s (%d) = %s (%d) r %s (%d)\n\n", bits(Rg1), Rg1, bits(Rg2), Rg2, bits(Rg3), Rg3, bits(r), r);
}


int main(int argc, char *argv[]) {

    divide(-29, 4);
    divide(19, -8);

    return 0;
}