#include <ADC.h>
#include <infrarouge.h>

/*
 * infrarouge.c
 *
 *  Created on: 19 janv. 2018
 *      Author: j.liu.13
 *      cette fichier est pour des operations du capture de l'infrarouge
 */

int lire_le_capteur_infra(int port){
	int resultat;

	ADC_init();

	ADC_Demarrer_conversion(port);
	resultat = ADC_Lire_resultat();

    if (resultat < 255) return 0;
    else return 1;
}



