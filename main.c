//voici la preuve 1 pour la projet de MicroP


#include <msp430.h> 
#include <ADC.h>
#include <moteur.h>

//1023 = 5

/*
 * main.c
 */


//on arr�tre qhhhhhh




void init_suivi_ligne(void);
int suivi1(void);
int suivi2(void);

/*
 * main.c
 */
-�int main(void) {
	volatile int i,j;
	volatile int suivi_gauche, suivi_droit;

	volatile int resultat;
	volatile double tension;

	volatile int vitess;
	volatile int butoir = 0;//quand butoir = 0 acc�l�ration


    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;

    vitess = 0; //Ici, c'est pour initialiser la valeur de vitess � 60
    ADC_init();

    init_moteurs();
    puissance_moteurs(vitess,vitess);
    moteurs_avancer();
    puissance_moteurs(vitess,vitess);

    while(1){
    	ADC_Demarrer_conversion(0);
    	resultat = ADC_Lire_resultat();


    	//la p�riode de acc�l�ration
    	if((vitess<95)&&(butoir==0)){
    			vitess += 5;
    			puissance_moteurs(vitess,vitess);
    	}

    	//la p�riode de ralentir
    	if ((vitess >= 20)&&(butoir == 1)){
    			vitess -= 1;
    		    puissance_moteurs(vitess,vitess);
    	}




    	//Pour changer la
        if (resultat > 150){
        	butoir = 1;
    	}

        //Pour arr�tre le robot
    	if (resultat > 250){
    		vitess = 0;
    		puissance_moteurs(0, 0);
    	}


        for (i=0;i<5000;i++);
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


