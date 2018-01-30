#include <msp430.h>


float distance_parcouru(int valeur){
	// 1 tour = 13.2 cm = 12 interruptions
	return  ((float)valeur / 12.0) * 13.2;
}

void init_codeurs(void) {
	P2SEL &= ~(BIT0 | BIT5);
	P2SEL2 &= ~(BIT0| BIT5);

	P2DIR &= ~(BIT0| BIT5);

	P2IFG &= ~(BIT0| BIT5);
	P2IES &= ~(BIT0| BIT5);
	P2IE |= (BIT0| BIT5);
}

