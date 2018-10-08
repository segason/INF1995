#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


void ajustementPWM () 
{

    TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10); 
    
    TCNT1 = 0;

    OCR1A = 0 ;

    OCR1B = 0 ;

    TCCR1B |= (1<<CS11) ;

    TCCR1C = 0;

}

void Avance(unsigned int pwm)
{
	OCR1A = OCR1B = pwm;
}

void Tourner_Gauche(unsigned int pwm)
{
	OCR1A = pwm / 2;
	OCR1B = pwm;
}

void Tourner_Droite(unsigned int pwm)
{
	OCR1A = pwm;
	OCR1B = pwm / 2;
}


int main()
{
	DDRD = 0xFF;
	
	while (1)
        {
		ajustementPWM();
		Avance(0);
		_delay_ms(2000);	
		Avance(64);
		_delay_ms(2000);	
		Avance(128);
		_delay_ms(2000);	
		Avance(192);
		_delay_ms(2000);	
		Avance(255);
		_delay_ms(2000);	
		Tourner_Gauche(128);
		_delay_ms(2000);
		Tourner_Droite(128);
		_delay_ms(2000);	

	}
	return 0;
}



