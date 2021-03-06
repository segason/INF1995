#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "PWM.h"


Pwm::Pwm()
{
		TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10); 
    
		TCNT1 = 0;

		OCR1A = 0 ;

		OCR1B = 0 ;

		TCCR1B |= (1<<CS11) ;

		TCCR1C = 0;
}

Pwm::~Pwm()
{}

void Pwm::Avance(unsigned int pwm)
{
	PORTD = 0x00;
	OCR1A = OCR1B = pwm;

}

void Pwm::reculer(unsigned int pwm)
{
	PORTD = 0xc0;
	OCR1A = OCR1B = pwm;

}

void Pwm::Tourner_Gauche(unsigned int pwm)
{
		OCR1A = pwm / 2;
		OCR1B = pwm;
}

void Pwm::Tourner_Droite(unsigned int pwm)
{
		OCR1A = pwm;
		OCR1B = pwm / 2;
}

