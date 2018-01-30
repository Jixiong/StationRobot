#include <msp430.h>				
#include<ADC.h>

void init_capteurs_IR(void);
void init_trou(void);

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	init_capteurs_IR();
	init_trou();
	ADC_init();

	volatile int gauche, droite, devant, trou;

	while (1) {
		ADC_Demarrer_conversion(1);
		gauche = ADC_Lire_resultat();

		ADC_Demarrer_conversion(7);
		droite = ADC_Lire_resultat();

		ADC_Demarrer_conversion(0);
		devant = ADC_Lire_resultat();

		ADC_Demarrer_conversion(4);
		trou = ADC_Lire_resultat();
	}
}

void init_trou(void) {
	P1SEL &= ~(BIT4);
	P1SEL2 &= ~(BIT4);
	P1DIR &= (BIT4);
}

void init_capteurs_IR(void) {
	P1SEL &= ~(BIT1 | BIT7 | BIT0);
	P1SEL2 &= ~(BIT1 | BIT7 | BIT0);
	P1DIR &= (BIT1 | BIT7 | BIT0);
}
