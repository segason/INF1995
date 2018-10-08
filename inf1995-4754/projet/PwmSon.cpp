#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "PwmSon.h"


PwmSon::PwmSon()
{
	
}



PwmSon::~PwmSon()
{}


void PwmSon::ajustementPwmSon()
{
    /*TCCR0A |= (1<<WGM01) | (1<<COM0A0);

    TCCR0B |= (1<<CS02) ;*/
    
    	TCCR0A = (1 << WGM01) | (1 << COM0A0);
	
	TCCR0B = 0x04 ;
		
	OCR0A = 100;
	
	//= 15625.0/(110.0 * pow(2, (note-45)/12.0));

}


void PwmSon::faireSon(unsigned int pwm)
{
	OCR0A = floor((pwm-45)*255/36);
}

void PwmSon::silence(unsigned int pwm)
{
	TCCR0B &= 0x00;
}
