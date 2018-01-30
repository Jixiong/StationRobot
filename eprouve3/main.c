//voici la preuve 1 pour la projet de MicroP

#include <msp430.h> 
#include <ADC.h>
#include <moteur.h>
#include <codeurs.h>

//1023 = 5

/*
 * main.c
 */

// Ce sont des fonction qu'il soit réaliser
/*
void Robot_Avancer();
void Robot_Arrete();
void Robot_Tourner_Gauche();
void Robot_Toutner_Droit();
void Robot_init();
*/

//Ces trois fonction, si la sortie égale à 1, il y a un obstacle, sinon, la sortie égale à 0
/*
int Obstacle_Devant();
int Obstacle_A_Gauche();
int Obstacle_A_Droite();
*/
void init_capteurs_IR(void);


/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

	init_capteurs_IR();


	int gauche;
	int droite;

	while (1) {
		ADC_Demarrer_conversion(1);
		gauche = ADC_Lire_resultat();

		ADC_Demarrer_conversion(7);
		droite = ADC_Lire_resultat();

		/*if ((Obstacle_Devant() == 1)) {
			Robot_Arrete();
			if (Obstacle_A_Gauche() == 0) {
				Robot_Tourner_Gauche();
				for (i = 0; i < 15000; i++)
					;
				Robot_Avancer();
			} else {
				if (Obstacle_A_Droite() == 0) {
					Robot_Tourner_Droite();
					for (i = 0; i < 15000; i++)
						;
					Robot_Avancer();
				} else {
					Robot_Tourner_Droite();
					for (i = 0; i < 15000; i++)
						;
					Robot_Tourner_Droite();
					for (i = 0; i < 15000; i++)
						;
					Robot_Avancer();
				}
			}

		}
		if ((Obstacle_A_Gauche() == 0) && (Obstacle_Devant() == 0)) {
			for (i = 0; i < 10000; i++)
				;
			Robot_Arrete();
			Robot_Tourner_Gauche();
			for (i = 0; i < 15000; i++)
				;
			Robot_Avancer();
		}

	}*/

}
/*
void init_capteurs_IR(void) {
	P1SEL &= ~(BIT | BIT);
	P1SEL2 &= ~(BIT | BIT);
	P1DIR &= (BIT | BIT);
}

int Obstacle_Devant(void) {
	ADC_Demarrer_conversion();
	if (ADC_Lire_resultat() >)
		return 1;
	return 0;
}

int Obstacle_A_Gauche(void) {
	ADC_Demarrer_conversion();
	if (ADC_Lire_resultat() >)
		return 1;
	return 0;
}

int Obstacle_A_Droite(void) {
	ADC_Demarrer_conversion();
	if (ADC_Lire_resultat() >)
		return 1;
	return 0;
}*/

