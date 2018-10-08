/*
Fichier: TP3-2.cpp
Auteur(s): Alexandre Vu, Louis-Philippe Chouinard
Date de creation: 26 janvier 2016
Date de modification: 26 janvier 2016
Description: Programme permettant l'implementation de la machine a etat demandee dans le probleme 2 du TP3.
*/
/* 
 *                  TABLE D'ETATS
 *
 *Etat present    Entree(bouton)  Etat suivant    Sortie(DELL)
 *  INIT            0               INIT            Rouge(0x01)
 *  INIT            1               EA              Rouge(0x01)
 *  EA              0               EB              Ambre(alternance entre 0x01 et 0x02)
 *  EA              1               EA              Ambre(alternance entre 0x01 et 0x02)
 *  EB              0               EB              Vert(0x02)
 *  EB              1               EC              Vert(0x02)     
 *  EC              0               ED              Rouge(0x01)
 *  EC              1               EC              Rouge(0x01)
 *  ED              0               ED              Eteint(0x00)
 *  ED              1               EE              Eteint(0x00)
 *  EE              0               INIT            Vert(0x02)
 *  EE              1               EE              Vert(0x02)
 */
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "delControl.h"
#include "Moteur.h"
#include "minuterie.h"

enum Etat{VERT, ROUGE};
Minuterie notreMinuterie;


ISR (TIMER1_COMPA_vect) 
{
    notreMinuterie.setExpiree(uint8_t(1));
}

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

// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

	while (!( UCSR0A & (1<<UDRE0))) //Attendre que le tampon soient libre. 
	{
	}
               
    	UDR0 = donnee; 

}


int main()
{
    /*Del notreDel;
    Moteur notreMoteur;

    notreMinuterie.partirMinuterie(8000);
    Etat notreEtat = VERT;
   
    while(true)
    {
        
        notreMoteur.deuxiemeVitesse();
        if(notreMinuterie.estExpiree())
            switch (notreEtat)
            {
                case VERT:
                    notreDel.allumerRouge(uint8_t(0));
                    notreEtat = ROUGE;
                    notreMinuterie.setExpiree(uint8_t(0));
                    break;
                case ROUGE:
                    notreDel.allumerVert(uint8_t(0));
                    notreEtat = VERT;
                    notreMinuterie.setExpiree(uint8_t(0));
                    break;
            }
            
    }*/
        DDRA = 0xFF;
	Memoire24CXXX memoire;
	memoire.init();
	uint8_t chaine[19] = {'E', 'C', 'O', 'L', 'E', 'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', 0};	
	memoire.ecriture(0x00, chaine, 19);
	_delay_ms(5);
	
	initialisationUART();
	for ( uint8_t i=0; i < 19; i++ ) {

		transmissionUART ( chaine[i] );

	}
	return 0;
}
