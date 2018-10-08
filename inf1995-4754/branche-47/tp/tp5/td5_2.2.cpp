#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

using namespace std;

volatile uint8_t etat = 0; //Variable globale
volatile bool presse = false; //Variable globale

ISR ( INT0_vect ) {

    _delay_ms ( 30 );
 
if(etat == 5){
    etat = 0;for (;;) {
		
		switch (etat) {
		
		//Etat  initial
		case 0:
}
else{
    etat++;
}

EIFR |= (1 << INTF0) ;

}

 
void initialisation(){
    cli();
    DDRB = 0xFF;
    PORTB = 0x02;
    PORTD = 0x01;
    
    EIMSK |= _BV(INT0);
    
    EICRA |= (1 << ISC00);
    
    sei();
}

int main(){
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