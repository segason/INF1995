/*
Fichier: tp7_2.cpp
Auteur(s): Olivier St-Onge, Gabriel Hélie, Ibrahima Séga
Date de creation: 20 février 2016
Date de modification: 20 février 2016
Description: Implémentation pb2 du tp7
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"


int main()
{
    DDRB = 0xff;	//Sortie
    PORTB = 0xff;  	//DEL fermee
    can can;		//Objet can
    while(true)		//Boucle infinie
    { 
        uint8_t niveau = can.lecture(1) >> 2;	//Shift pour enlever les 2 bits de trop
    
            if(niveau < 100)
                PORTB = 0x01;	//niveau faible, DEL verte
            
            else if(niveau >= 100 && niveau < 200)	//niveau moyen, DEL ambree
            {
                PORTB = 0x01;
                _delay_ms(10);
                PORTB = 0x02;
                _delay_ms(10);
            }
                
            else if(niveau >= 200)	//niveau fort, DEL rouge
                 PORTB = 0x02;

            else
                PORTB = 0x00;
        
        
    }
}

