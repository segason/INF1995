#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>



using namespace std;

volatile uint8_t etat = 0;
volatile bool presse = false;
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 


void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisee par 1024
// interruption apres la duree specifiee

TCNT1 = 0 ;
OCR1A = duree;
TCCR1A = (1 << WGM12) ;
TCCR1B = (1 << CS12 | 1 << CS10) ;
TCCR1C = 0;
TIMSK1 = (1 << OCIE1A) ;
}


ISR ( TIMER1_COMPA_vect ) {

minuterieExpiree = 1;

}


ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond

_delay_ms(10);
if(PIND & 0x04)
	boutonPoussoir = 1;
else
	boutonPoussoir = 0;

}



void initialisation ( void ) {

	// cli est une routine qui bloque toutes les interruptions.
	// Il serait bien mauvais d'etre interrompu alors que
	// le microcontroleur n'est pas pret...
	cli ();

	// configurer et choisir les ports pour les entrees
	// et les sorties. DDRx... Initialisez bien vos variables


	DDRB = 0xFF; //DEL en sortie
	PORTB = 0xff;
	PORTD = 0x01;
	etat = 0;
	boutonPoussoir = 0;

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
	initialisation();
	
	for(int i=0;i<3;i++)
		_delay_ms(1000);
	PORTB = 0x02;
	_delay_ms(100);
	PORTB = 0xff;
	partirMinuterie(7812);
	
	do {

// attendre qu'une des deux variables soit modifiee
// par une ou l'autre des interruptions.

} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


// Une interruption s'est produite. Arreter toute
// forme d'interruption. Une seule reponse suffit.

cli ();

// Verifier la reponse


if(boutonPoussoir == 1)
	PORTB = 0x01;
//if (minuterieExpiree == 1)
else
	PORTB = 0x02;
	
	return 0;

}

