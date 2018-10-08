#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>



using namespace std;

volatile uint8_t etat = 0;
volatile bool presse = false;


// placer le bon type de signal d'interruption
// a prendre en charge en argument

ISR ( INT0_vect) {

// laisser un delai avant de confirmer la reponse du
// bouton-poussoir: environ 30 ms (anti-rebond)
_delay_ms ( 30 );

// Se souvenir ici si le bouton est presse ou relache

if(PIND & 0x04)
	presse = true;
else
	presse = false;

// changements d'etats tels que ceux de la
// semaine precedente

if(etat==5)
	etat=0;
else
	etat++;

// Voir la note plus bas pour comprendre cette instruction et son role

EIFR |= (1 << INTF0) ;

}



void initialisation ( void ) {

	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'etre interrompu alors que
	// le microcontroleur n'est pas pret...
	cli ();

	// configurer et choisir les ports pour les entrees
	// et les sorties. DDRx... Initialisez bien vos variables


	DDRB = 0xFF; //DEL en sortie
	PORTB = 0x02;
	PORTD = 0x01;

	// cette procédure ajuste le registre EIMSK
	// de ATmega324PA pour permettre les interruptions externes
	EIMSK |= _BV(INT0);

	// il faut sensibiliser les interruptions externes aux
	// changements de niveau du bouton-poussoir
	// en ajustant le registre EICRA

	EICRA |= _BV(ISC00) ;

	// sei permet de recevoir a nouveau des interruptions.
	sei ();

}


int main() {
	
	//bool enfonce = false;
	//etat = 0;

	//PORTB = 0x02;	//DEL rouge

	//Boucle infini
	initialisation();
	for (;;) {
		
		switch (etat) {
		
		//Etat  initial
		case 0:
			PORTB = 0x02; //A letat initiale, la del est rouge
			break;
		
			//Etat A
		case 1:            
			if(PORTB == 0x01){	//DEL ambre
				PORTB = 0x02;
                _delay_us(100);
                        }
                        
			else if(PORTB == 0x02){
				PORTB = 0x01;
                _delay_us(100);
                        }           
			break;
		
			//Etat B
		case 2:
			PORTB = 0x01; //DEL verte
			break;
		
			//Etat c
		case 3:
			PORTB = 0x02; //DEL rouge
			break;
		
			//Etat d
		case 4:
			PORTB = 0xFF; //DEL fermee
			break;
		
			//Etat e
		case 5:
			PORTB = 0x01; //DEL verte
			break;

		}
	}
	return 0;
}
