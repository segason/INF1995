#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


void ajustementPWM () 
{

    TCCR0A |= (1<<WGM01) | (1<<COM0A0);
    
    //TCNT0 = 0;

    //OCR0A = 0 ;

    //OCR0B = 0 ;

    TCCR0B |= (1<<CS02) ;

    //TCCR0C = 0;

}

void Avance(unsigned int pwm)
{
	OCR0A = floor((pwm-45)*255/36);
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
	DDRB = 0xFF;
	
	while (1)
        {
		ajustementPWM();
		//Avance(0);
		//_delay_ms(2000);	
		//Avance(64);
		//_delay_ms(2000);	
		
		
		Avance(64);
		_delay_ms(2000);	
		/*Avance(192);
		_delay_ms(2000);	
		Avance(255);
		_delay_ms(2000);	
		Tourner_Gauche(128);
		_delay_ms(2000);
		Tourner_Droite(128);
		_delay_ms(2000);*/

	}
	return 0;
}



