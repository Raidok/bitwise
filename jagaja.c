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
// L   loendur



/**
 * kontrollib, kas arv on täiendkoodis
 * ette tuleb anda arv ning kasutatavate bittide arv
 */
int onTaiendkood(char Rg, char L) {
	char esimene = 0x01<<L-1; // seatakse viimane bit üheks ja nihutatakse seda vajalik arv kordi vasakule
	return Rg & esimene ? TRUE : FALSE;
}



/**
 * sätib üleliigsed vanemad bitid nullideks
 */
void korista(char *Rg, char L) {
	char bit1 = 0x80;
	char bit = 0x7F;
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
	char bit = 0x01<<L-1;
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
 * selgitab välja vanima kõrge biti
 * ette tuleb anda arv, mida uurima hakatakse
 */
int vanimBit(char Rg, char L) {
	char bit = 0x01<<L-1;
	int i;
	for (i = L-1; i >= 0; i--) {
		if (Rg & bit) {
			break;
		}
		bit >>= 1;
	}
	return i;
}



/**
 * paigutab arvude kõrgeimad bitid kohakuti
 */
void paiguta(char *Rg1, char *Rg2, char L) {
	int pos1 = vanimBit(*Rg1, L);
	int pos2 = vanimBit(*Rg2, L);
	printf("pos1 %d pos2 %d\n", pos1, pos2);
	//korista(Rg1, L);
	//korista(Rg2, L);
	if (pos1 > pos2) {
		*Rg2 <<= pos1-pos2;
	} else {
		*Rg2 >>= pos2-pos1;
	}
}



/**
 * jagamist teostav algoritm
 */
int jaga(char Rg1, char Rg2, char L, int debug) {
	char bit = 0x01<<L-1;
	char Rg3, jaak=0;
	int i;
	
	if (debug) printf("\n********* JAGATAKSE ARVUD %s / %d JA %s / %d *********\n\n", bitid(Rg1, L), Rg1, bitid(Rg2, L), Rg2);
	
	if (onTaiendkood(Rg1, L) || onTaiendkood(Rg2, L)) {
		if (debug) printf("- v2hemalt yks arvudest on t2iendkoodis\n");
	} else {
		if (debug) printf("- m6lemad arvud on otsekoodis\n");
	}
	
	// 1. Sättida Rg1 ja Rg2 vanimad bitid kohakuti.
	if (debug) printf("- vastus peaks tulema: %s / %d jääk: %s / %d\n\n", bitid(Rg1/Rg2, L), Rg1/Rg2, bitid(Rg1-Rg1/Rg2*Rg2, L), Rg1-Rg1/Rg2*Rg2);
	//paiguta(&Rg1, &Rg2, L);
	if (debug) printf("Rg1 : %s (%2d)\n", bitid(Rg1, L), Rg1);
	if (debug) printf("Rg2 : %s (%2d)\n", bitid(Rg2, L), Rg2);
	Rg3 = Rg1;
	if (debug) printf("Rg3 : %s (%2d)  <- Rg1 koopia\n\n", bitid(Rg3, L), Rg3);
	
	for (i = 0; i < L; i++) { // käiakse läbi kõik bitid

		if (debug) printf("\n ------------ %d. ITERATSIOON ------------\n", i+1);

		// vastuse ja jäägi ringnihutamine vasakule
		if (Rg3 & bit) {
			if (debug) printf(" - j22gi ja vastuse paremnihe, ylekanne vastusest j22ki\n");
			Rg3 <<= 1;
			jaak <<= 1;
			jaak += 1;
			Rg3 &= ~(bit<<1);
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		} else {
			if (debug) printf(" - j22gi ja vastuse paremnihe\n");
			Rg3 <<= 1;
			jaak <<= 1;
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		}
		
		// nullib vaatlusest välja jäänud järgud igaks juhuks ära
		korista(&Rg3, L);
		korista(&jaak, L);
		
		if (debug) printf(" - liidan j22gile jagaja\n");
		jaak += Rg2;
		if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		
		if (jaak < 0) {
			if (debug) printf(" - lahutan j22gist jagaja\n");
			jaak -= Rg2;
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		} else {
			if (debug) printf(" - sean noorima j2rgu k6rgeks\n");
			Rg3 |= 0x01;
			if (debug) printf(" > %s (%2d) | %s (%2d)\n", bitid(jaak, L), jaak, bitid(Rg3, L), Rg3);
		}
		
		
		
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

