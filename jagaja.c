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
	korista(&Rg, L);
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
	korista(Rg1, L);
	korista(Rg2, L);
	if (pos1 > pos2) {
		*Rg2 <<= pos1-pos2;
	} else {
		*Rg2 >>= pos2-pos1;
	}
}



/**
 * jagamist teostav algoritm
 */
int jaga(char Rg1, char Rg2, char *Rg3, char *jaak, char L) {
	char t;
	int i;
	
	// algväärtustamine
	*Rg3 = 0;
	*jaak = 0;
	
	printf("\n********* JAGATAKSE ARVUD %s / %d JA %s / %d *********\n\n", bitid(Rg1, L), Rg1, bitid(Rg2, L), Rg2);
	
	if (onTaiendkood(Rg1, L) || onTaiendkood(Rg2, L)) {
		printf("- Kuna v2hemalt yks arvudest on t2iendkoodis, j2tan meelde?.\n");
		//*Rg3 = ~0;
	} else {
		printf("- M6lemad arvud on otsekoodis.\n");
	}
	
	// 1. Sättida Rg1 ja Rg2 vanimad bitid kohakuti.
	paiguta(&Rg1, &Rg2, L);
	printf("Rg1 : %s / %d\n", bitid(Rg1, L), Rg1);
	printf("Rg2 : %s / %d\n", bitid(Rg2, L), Rg2);
	printf("- vastus peaks tulema: %s / %d jääk: %s / %d\n\n", bitid(Rg1/Rg2, L), Rg1/Rg2, bitid(Rg1-Rg1/Rg2*Rg2, L), Rg1-Rg1/Rg2*Rg2);
	
	
	
	for (i=0; /**jaak < Rg2 &&*/ i<L; i++) {
		
		// 2. Arvutada jääk = (Rg1 - Rg2)
		if (Rg2 > Rg1) {
			Rg2 >>= 1;
		}
		*jaak = Rg1 - Rg2;
		korista(jaak, L);
		printf("--------------------  %d. ITERATSIOON :\n", i+1);
		printf("> Rg1 : %s / %d\n", bitid(Rg1, L), Rg1);
		printf("> Rg2 : %s / %d\n", bitid(Rg2, L), Rg2);
		printf(">j22k : %s / %d\n", bitid(*jaak, L), *jaak);
		// 3. Kui jaak >= 0, siis Rg3-e viimane bit 1-ks ja Rg1 = t.
		if ( *jaak >= 0 ) {
			*Rg3 |= 0x01;
			Rg1 = *jaak;
			printf("- viimane bit k6rgeks:\n");
			printf("  Rg3: %s / %d\n", bitid(*Rg3, L), *Rg3);
		} else {/*
			*Rg3 &= 0xFE;
			printf("- viimane bit madalaks:\n");
			printf("  Rg3: %s / %d\n", bitid(*Rg3, L), *Rg3);*/
		}
		
		if (Rg2 > Rg1) {
			printf(">>>L6PP\n\n");
			break;
		}
		
		// 4. Nihutada Rg1 ühe võrra vasakule
		//Rg1 <<= 1;
		// 5. Nihutada Rg3 ühe võrra vasakule
		*Rg3 <<= 1;
		
		korista(&Rg1, L);
		korista(Rg3, L);
		printf("- nihked tehtud:\n");
		printf("  Rg1: %s / %d\n", bitid(Rg1, L), Rg1);
		printf("  Rg3: %s / %d\n\n", bitid(*Rg3, L), *Rg3);
		
	}
}



/**
 * peaprogramm
 */
int main(char* args[]) {
	char jagatis, jaak, L=6;
	
	printf("--------------------------------------------------------------------------------\n");
	
	// Esimene algoritm
	// A1 = -29 = 10 0011 <- täiendkood
	// B1 =   4 = 00 0100 <- otsekood
	//jaga(0x23, 0x04, &jagatis, &jaak, 0x06);
	//printf("\nJagatis: %d\nJ22k: %d\n\n", jagatis, jaak);
	
	// A2 = 19 = 01 0011 <- otsekood
	// B2 = -8 = 11 1000 <- täiendkood
	jaga(-29, 4, &jagatis, &jaak, L);
	printf("\nJAGATIS: %s / %d\n", bitid(jagatis, L), jagatis);
	printf("   J22K: %s / %d\n\n", bitid(jaak, L), jaak);
	
	jaga(19, -8, &jagatis, &jaak, L);
	printf("\nJAGATIS: %s / %d\n", bitid(jagatis, L), jagatis);
	printf("   J22K: %s / %d\n\n", bitid(jaak, L), jaak);
	
	//for(;getchar()!='\n';);
	return 0;
}

