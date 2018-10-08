/*
//PB2
	void initialisationUART(void) {

		// 2400 bauds. Nous vous donnons la valeur des deux
		// premier registres pour vous éviter des complications
		UBRR0H = 0;
		UBRR0L = 0xCF;
		// permettre la reception et la transmission par le UART0 (p.173 Atmel)
		UCSR0A = 0;
		UCSR0B |= (1 << RXEN0) | (1 << TXEN0) ;
		// Format des trames: 8 bits, 1 stop bits, none parity (p.188 Atmel) 
		UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	}

	// De l'USART vers le PC
	// (p.174)
	void transmissionUART(uint8_t donnee) {
		/* Wait for empty transmit buffer */
//		while (!(UCSR0A & (1 << UDRE0)))
//			;
//		/* Put data into buffer, sends the data */
//		UDR0 = donnee;
//	}




	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////



/*
int main()
{

	//PB1

	DDRB = 0xFF;
	Memoire24CXXX memoireAVR;

	//Ecriture de la chaine d caractère
	char const* chaine= "*E*C*O*L*E*P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
        uint8_t* donnees;
         donnees[0] = (uint8_t)atoi(chaine);
  
	memoireAVR.ecriture(0x00, donnees, 39);

	_delay_ms(5);
	//Lecture de la chaine ecrite
	uint8_t* result = 0;
	memoireAVR.lecture(0x00, result, 39);
	


	if (*donnees == *result)
		PORTB = 0x02; //vert = réussi
	else
		PORTB = 0x01; //rouge = échec


    
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////



	//PB3
	transmissionUART((uint8_t)result);
	uint8_t* donnees = nullptr;
	while (uint8_t(donnees) != 0xFF)
		memoireAVR.lecture(0x00, donnees);


}*/


#include "Memoire24CXXX.h"
#include <avr/io.h>
#include <avr/interrupt.h> 
#define F_CPU 8000000
#include <util/delay.h>
using namespace std;

int main()
{
	DDRB = 0xFF;
	Memoire24CXXX memoireAVR;
	uint8_t chaine[19] = {'E', 'C', 'O', 'L', 'E', 'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', 0};	
	memoireAVR.ecriture(0x00, chaine, 19);
	_delay_ms(5);
	uint8_t chaine2[19] = {};
	memoireAVR.lecture(0x00, chaine2, 19);
	_delay_ms(5);
	int compteur = 0;
	for(int i = 0; i< 19; i++)
	{
		if(chaine[i] == chaine2[i])
			compteur++;
	}	
	if (compteur == 19){
		PORTB = 0x02;
		_delay_ms(2000);
	}
	else {
		PORTB = 0x01;
		_delay_ms(2000);
	}
	return 0;
}