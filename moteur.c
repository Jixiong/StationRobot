/*
 * moteur.c
 *
 *  Created on: 19 janv. 2018
 *      Author: j.mosnino.15
 */
void init_moteurs(void);
void puissance_moteurs(int pourcentageA, int pourcentageB);
void moteurs_avancer(void);
void moteurs_tourne_gauch(void);


void init_moteurs(void) {
	P2SEL &= ~(BIT1 | BIT5);
	P2SEL |= (BIT2 | BIT4);
	P2SEL2 &= ~(BIT1 | BIT2 | BIT4 | BIT5);

	P2DIR |= (BIT1 | BIT2 | BIT4 | BIT5);

	TA1CTL |= (TASSEL_2 | MC_1 | ID_0);


	TA1CCTL1 |= OUTMOD_7; //moteur A
	TA1CCTL2 |= OUTMOD_7; //moteur B
}

void puissance_moteurs(int pourcentageA, int pourcentageB) {
	//pour le robot lent, le poucentage doit etre > 60
	TA1CCR0 = 240; //4.16kHz
	TA1CCR1 = (int) (239*pourcentageA)/100;
	TA1CCR2 = (int) (237*pourcentageB)/100;
}

void moteurs_avancer(void) {
	P2OUT |= (BIT5);
	P2OUT &= ~(BIT1);
}

void moteurs_tourne_gauch(void){
	int i;
	P2OUT &= ~(BIT5);
	P2OUT &= ~(BIT1);
	
	puissance_moteur (60,60);
	
	for(i=0; i<10000;i++);
	
	puissancemoteur (0,0);
}

