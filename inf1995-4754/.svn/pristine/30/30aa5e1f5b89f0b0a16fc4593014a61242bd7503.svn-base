#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>


int main()
{
	DDRB = 0xFF; // PORT B est en mode sortie
	
	for (;;){

  
	for (int i1 = 0 ; i1 < 120 ; i1++){
		PORTB = 0x01;
		_delay_ms(1000.0/60.0);
	}
	for (int i2 = 0 ; i2 < 120; i2++){
		PORTB = 0xFF;
		_delay_ms(1000.0/240.0);
		PORTB = 0x01;
		_delay_ms(1000.0/80.0);
	}
	for (int i3 = 0 ; i3 < 120; i3++){
		PORTB = 0xFF;
		_delay_ms(1000.0/120.0);
		PORTB = 0x01;
		_delay_ms(1000.0/120.0);
	}
	for (int i4 = 0 ; i4 < 120; i4++){
		PORTB = 0xFF;
		_delay_ms(1000.0/80.0);
		PORTB = 0x01;
		_delay_ms(1000.0/240.0);
	}
	for (int i3 = 0 ; i3 < 120; i3++){
		PORTB = 0xFF;
		_delay_ms(1000.0/60.0);
	}
	
	
	
	for (int j1 = 0 ; j1 < 800 ; j1++){
		PORTB = 0x01;
		_delay_ms(1000.0/400.0);
	}
	for (int i2 = 0 ; i2 < 800; i2++){
		PORTB = 0xFF;
		_delay_ms(1000.0/1600.0);
		PORTB = 0x01;
		_delay_ms(1000.0/(1600.0/3.0));
	}
	for (int i3 = 0 ; i3 < 800; i3++){
		PORTB = 0xFF;
		_delay_ms(1000.0/800.0);
		PORTB = 0x01;
		_delay_ms(1000.0/800.0);
	}
	for (int i4 = 0 ; i4 < 800; i4++){
		PORTB = 0xFF;
		_delay_ms(1000.0/(1600.0/3.0));
		PORTB = 0x01;
		_delay_ms(1000.0/1600.0);
	}
	for (int i3 = 0 ; i3 < 800; i3++){
		PORTB = 0xFF;
		_delay_ms(1000.0/400.0);
	}
}


  for (;;){
	  PORTB = 0x01;
  }
  return 0; 
}

