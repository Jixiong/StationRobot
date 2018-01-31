//voici la preuve 1 pour la projet de MicroP

#include <msp430.h> 
#include <ADC.h>
#include <moteur.h>

//1023 = 5

/*
 * main.c
 */

//on arrêtre qhhhhhh
void init_IR(void);
/*
 * main.c
 */
int main(void) {
	volatile int i, j;

	volatile int resultat = 0;
	volatile double tension;

	volatile int vitess;
	volatile int vitess_droite;

	volatile int butoir = 0; //quand butoir = 0 accélération

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	vitess = 0; //Ici, c'est pour initialiser la valeur de vitess à 0
	ADC_init();
	init_IR();

	init_moteurs();
	//puissance_moteurs(vitess,vitess);
	moteurs_avancer();
	//puissance_moteurs(vitess,vitess);

	while (1) {
		ADC_Demarrer_conversion(0);
		resultat = ADC_Lire_resultat();

		//la période de accélération
		if ((vitess < 70) && (butoir == 0)) {
			vitess += 5;
			if (vitess > 30) {
				vitess_droite = vitess + 4.5;
			} else {

				vitess_droite = vitess;
			}
			puissance_moteurs(vitess, vitess_droite);

		}

		//la période de ralentir
		if ((vitess >= 20) && (butoir == 1)) {
			vitess -= 10;
			puissance_moteurs(vitess + 0.25, vitess);
		}

		//Pour changer la mode d'acce
		if (resultat > 160) {
			butoir = 1;
		}

		if (resultat < 160) {
			butoir = 0;
		}

		//Pour arrêtre le robot
		if (resultat > 430) {
			puissance_moteurs(0, 0);

		}


//for (i=0;i<3000;i++);
	}

	return 0;
}

void init_IR(void) {

	P1SEL &= ~BIT0;
	P1SEL2 &= ~BIT0;
	P1DIR &= ~ BIT0;

}

