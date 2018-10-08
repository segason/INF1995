/*
Fichier: TP7-2.cpp
Auteur(s): Alexandre Vu, Louis-Philippe Chouinard
Date de creation: 23 février 2016
Description: Programme permettant l'implementation du vérificateur d'intensité demandé au problème 2 du TP7.
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"        //Ajout du fichier d'en-tête des fonctions du convertisseur analogique-numérique.
#include "Memoire24CXXX.h" 
void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

UCSR0A = (1 << TXC0) | (1 << RXC0) ;

UCSR0B =  (1 << RXEN0) | (1 << TXEN0) ; // L'émetteur USART est activé en réglant TXEN dans UCSRB.

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

}

void transmissionUARTVersPc ( uint8_t donnee ) {

	while (!( UCSR0A & (1<<UDRE0))) //Attendre que le tampon soient libre. 
	{
	}
               
    	UDR0 = donnee; 
}
int main()
{
    DDRA = 0x00;
    DDRB = 0x03; // Sortie      
    PORTD = 0x00;   // Precision de l'entree
    PORTB = 0;  // Initialisation de la sortie

initialisationUART();
    
    can intensite;  // Déclaration de l'objet à partir duquel la fonction qui lit l'intensité est appelée.
    while(true)
    { 
        uint8_t rapport = intensite.lecture(6) >> 2; //Lecture de l'intensité lumineuse et décalage vers la droite pour ne garder que les 8 bits les plus significatids lors de la conversion implicite en uint8_t.
            
            transmissionUARTVersPc(rapport);
            if(rapport < 80)    // Couleur verte de la DEL si l'intensité est inférieure à 80 (faible intensité lumineuse).
                PORTB = 0x01;
            
            else if(rapport >= 80 && rapport < 160) // Couleur ambrée de la DEL si l'intensité est supérieure ou égale à 80 et inférieure à 160 (intensité lumineuse moyenne).
            {
                PORTB = 0x02;
                _delay_ms(10);
                PORTB = 0x01;
                _delay_ms(10);
            }
                
            else if(rapport >= 220) // Couleur rouge de la DEL si l'intensité est supérieure ou égale à 160 (forte intensité lumineuse).
                 PORTB = 0x02;

            else
                PORTB = 0x00;   // Else implémenté par précaution.
        
        
    }
}
