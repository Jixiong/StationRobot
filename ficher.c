#include <msp430.h> 
#include <ADC.h>
#include <Afficheur.h>


//1023 = 5

/*
 * main.c
 */


//on arrêtre qhhhhhh




void init_moteurs(void);
void puissance_moteurs(int pourcentageA, int pourcentageB);
void moteurs_avancer(void);

void init_suivi_ligne(void);
int suivi1(void);
int suivi2(void);

/*
 * main.c
 */
int main(void) {
	volatile int i;
	volatile int suivi_gauche, suivi_droit;

	volatile int resultat;
	volatile double tension;


    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;

    ADC_init();

    init_moteurs();
    moteurs_avancer();
    puissance_moteurs(60,60);

    while(1){
    	ADC_Demarrer_conversion(0);
    	resultat = ADC_Lire_resultat();

        for (i=0;i<10000;i++);


    	if (resultat > 255){
    		puissance_moteurs(0, 0);
    	}


    }

	return 0;
}

int suivi1(void) {
	//surface blanche : Vout petit
	ADC_Demarrer_conversion(7);
	volatile int sol = ADC_Lire_resultat();

	return sol;
}

int suivi2(void) {
	//surface blanche : Vout petit
	ADC_Demarrer_conversion(5);
	volatile int sol = ADC_Lire_resultat();

	return sol;
}

void init_suivi_ligne(void) {
	P1SEL &= ~(BIT7 | BIT5);
	P1SEL2 &= ~(BIT7 | BIT5);

	P1DIR &= ~(BIT7 | BIT5);
}

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

