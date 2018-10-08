#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>


int main()
{
	DDRB = 0xff; // PORT B est en mode sortie

  for(;;)  // boucle sans fin
  {
	PORTB = 0xFF;
	int brightness = 255;


	while(brightness >= 0){
	
	for (int i = 0 ; i < 5; i++){
		for (int j = 0 ; j < brightness ; j++){
			PORTB = 0x01;
			_delay_ms(1/10);
		}
		PORTB = 0xFF;
                _delay_ms(1);
	
	}

	brightness--;
      }
      
      brightness = 255;
      
      while(brightness >= 0){
	
	for (int i = 0 ; i < 5; i++){
		for (int j = 0 ; j < brightness ; j++){
			PORTB = 0x02;
			_delay_ms(1/10);
		}
		PORTB = 0xFF;
                _delay_ms(1);
	
	}

	brightness--;
      }
	
	
  }
  return 0; 
}
