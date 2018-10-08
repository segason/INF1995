/*
Fichier: tp7_1.cpp
Auteur(s): Olivier St-Onge, Gabriel Hélie, Ibrahima Séga
Date de creation: 20 février 2016
Date de modification: 20 février 2016
Description: Implémentation pb1 du tp7
*/


#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


enum Status {INIT, EA, EB, EC, ED, EE};
Status etat = INIT; 

uint8_t cmp = 0;
uint8_t cmp2 = 0;

int main()
{
    DDRB = 0xff; // Sortie      
    PORTD = 0x00;   // Port d'entree
    PORTB = 0xff;  // DEL fermee



    while(true)	//Boucle infinie
    { 
        switch (etat)
        {
            case (INIT):
                cmp = 0;	//Compteur
                cmp2 = 0;	//Compteur pour le clignotement rouge
                if(!(PIND & 0x04))	//Le bouton du breadbox est inverse au bouton de la carte
                    etat = EA;
                break;
                
            case (EA):
                
                if(cmp == 120 || (PIND & 0x04))	//Si le compteur atteint 120 ticks
                {								//ou si le bouton est relache
                    for(uint8_t i = 0; i < 5; i++)
                    {
                        PORTB = 0x02;	//clignote vert
                        _delay_ms(50);
                        PORTB = 0x00;
                        _delay_ms(50);
                    }
                    etat = EB;
                }
                cmp++;
                _delay_ms(100);
                break;
           
            case (EB):
                _delay_ms(2000);	//attend 2 sec
                etat = EC;
                break;
            
            case (EC):
                
                PORTB = 0x01;	//flash rouge pour une duree de cmp/2
                _delay_ms(250);
                PORTB = 0x00;
                _delay_ms(250);
                cmp2++;
                if(cmp2 == cmp / 2)	//Si le compteur atteint cmp/2
                    etat = ED;
                break;
                
            case (ED):
                PORTB = 0x02;		
                _delay_ms(2000);
                PORTB = 0x00;
                etat = INIT;
            default:
                PORTB = 0x00;
        }
        
       

    }
}
