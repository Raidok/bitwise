#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0



/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Suvalise märgiga (täis)arvude vahetu jagamine   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * */


// Rg1 jagatav
// Rg2 jagaja
// Rg3 jagatis
// J   jääk
// L   bittide arv



/**
 * sätib üleliigsed vanemad bitid nullideks
 */
void korista(char *Rg, char L) {
	unsigned char bit1 = 0x80;
	unsigned char bit = 0x7F;
	int i;
	for (i = 0; i<sizeof(char)*8-L; i++) {
		*Rg &= bit;
		bit >>= 1;
		bit |= bit1;
		bit1 >>= 1;
	}
}



/**
 * tagastab bittide stringi
 * ette tuleb anda arv ning kasutatavate bittide arv
 */
char *bitid(char Rg, char L) {
	unsigned char bit = 0x01<<L-1;
	int i;
	char *bitid;
	//korista(&Rg, L);
	bitid = (char*) malloc(L+1);
	for (i=0; i < L; i++) {
		*(bitid+i) = Rg & bit ? '1' : '0';
		bit >>= 1;
	}
	*(bitid+i) = '\0';
	return bitid;
}



/**
 * jagamist teostav algoritm
 */
int jaga(char Rg1, char Rg2, char L, int debug) {
	char bit = 0x01<<L-1;
	char Rg3, jaak=0;
	int i;
	
	if (debug) printf("\n********* JAGATAKSE ARVUD %s / %d JA %s / %d *********\n\n", bitid(Rg1, L), Rg1, bitid(Rg2, L), Rg2);
	
	if (debug) printf(" - vastus peaks tulema: %s / %d jääk: %s / %d\n\n", bitid(Rg1/Rg2, L), Rg1/Rg2, bitid(Rg1-Rg1/Rg2*Rg2, L), Rg1-Rg1/Rg2*Rg2);
	if (debug) printf(" - Rg1 : %s (%2d)\n", bitid(Rg1, L), Rg1);
	if (debug) printf(" - Rg2 : %s (%2d)\n", bitid(Rg2, L), Rg2);
	Rg3 = Rg1;
	if (debug) printf(" - Rg3 : %s (%2d)  <- Rg1 koopia\n", bitid(Rg3, L), Rg3);
	if (Rg1 < 0) {
		jaak = 0xff;
	}
	if (debug) printf(" - jaak: %s (%2d)  <- j22k peale m2rgi kontrolli\n\n", bitid(jaak, L), jaak);
	
	for (i = 0; i < L; i++) { // käiakse läbi kõik bitid

		if (debug) printf("\n ------------ %d. ITERATSIOON ------------\n", i+1);

		// vastuse ja jäägi ringnihutamine vasakule
		if (Rg3 & bit) {
			if (debug) printf(" - j22gi ja vastuse paremnihe, ylekanne vastusest j22ki\n");
			Rg3 <<= 1;
			jaak <<= 1;
			jaak += 1;
			//Rg3 &= ~(bit<<1);
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		} else {
			if (debug) printf(" - j22gi ja vastuse paremnihe\n");
			Rg3 <<= 1;
			jaak <<= 1;
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		}
		
		if (debug) printf(" - liidan j22gile jagaja\n");
		jaak += Rg2;
		if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		
		if (jaak < 0) {
			if (debug) printf(" - lahutan j22gist jagaja\n");
			jaak -= Rg2;
			Rg3 |= 0x01;
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		} else {
			if (debug) printf(" - sean noorima j2rgu k6rgeks\n");
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		}
		
		
		
	}

	
	if ((Rg1 < 0 && Rg2 > 0) || (Rg1 > 0 && Rg2 < 0)) {
		Rg3++;
	}
	
	printf("%s (%d) / %s (%d) = %s (%d) r %s (%d)\n", 
		bitid(Rg1, L), Rg1, 
		bitid(Rg2, L), Rg2, 
		bitid(Rg3, L), Rg3,
		bitid(jaak, L), jaak);
}



/**
 * peaprogramm
 */
int main(int argc, char *argv[]) {

	char L=6; // bittide arv
	int debug;
	
	if ( (int)argv[1] ) debug = FALSE;
	else debug = TRUE;
	
	if (debug) printf("--------------------------------------------------------------------------------\n");

	// Esimene algoritm
	// A1 = -29 = 10 0011 <- täiendkood
	// B1 =   4 = 00 0100 <- otsekood
	//jaga(-29, 4, L, debug);
	
	// A2 = 19 = 01 0011 <- otsekood
	// B2 = -8 = 11 1000 <- täiendkood
	jaga(19, -8, L, debug);
	
	//for(;getchar()!='\n';);
	return 0;
}