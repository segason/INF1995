#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

using namespace std;

volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0;

ISR  (TIMER1_COMPA_vect ) {

minuterieExpiree = 1;

}


ISR ( INT0_vect ) {

boutonPoussoir = 1;

// anti-rebond
_delay_ms(30);


//EIFR |= (1 << INTF0) ;

}

void partirMinuterie ( uint16_t duree ) {

minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisee par 1024

// interruption apres la duree specifiee

TCNT1 = 0;

OCR1A = duree;

TCCR1A = 0 ;

TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10) ;

TCCR1C = 0;

//p.134 Bit 1
TIMSK1 = (1 << OCIE1A);

}

void initialisation(){
    cli();
    DDRB = 0xFF;
    PORTB = 0x01;
    PORTD = 0x01;
    
    EIMSK |= _BV(INT0);
    
    EICRA |= (1 << ISC00);
    
}

int main(){
    initialisation();
    for (int i = 0 ; i < 2000; i++){
        _delay_ms(1);
    }
    PORTB = 0xFF;
    sei();
    partirMinuterie(7812);
    
    
    do {


} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );



cli ();

// Verifier la reponse

if (boutonPoussoir == 1){
    PORTB = 0x02;
}
else{
    PORTB = 0x01;
}
    
    return 0;
    
}