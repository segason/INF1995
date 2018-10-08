/*
Fichier: TP3-1.cpp
Auteur(s): Alexandre Vu, Louis-Philippe Chouinard
Date de creation: 26 janvier 2016
Date de modification: 26 janvier 2016
Description: Programme permettant l'implementation de la machine a etat demandee dans le probleme 1 du TP3.
*/


/*          TABLE D'ETATS
 * 
État présent	Entree(Bouton)	   État suivant	     Sortie(DELL)
INIT	        0	           INIT	             Eteint(0x00)
INIT	        1	           EA	             Eteint(0x00)
EA	        0	           EB	             Eteint(0x00)
EA	        1	           EA	             Eteint(0x00)
EB	        0	           EB	             Eteint(0x00)
EB	        1	           EC	             Eteint(0x00)
EC	        0	           ED	             Eteint(0x00)
EC	        1	           EC	             Eteint(0x00)
ED	        0	           ED	             Eteint(0x00)
ED	        1	           EE	             Eteint(0x00)
EE	        0	           EF	             Eteint(0x00)
EE	        1	           EE	             Eteint(0x00)
EF	        0	           EF	             Eteint(0x00)
EF	        1	           EG	             Eteint(0x00)
EG	        0	           EH	             Eteint(0x00)
EG	        1	           EG	             Eteint(0x00)
EH	        0	           EH	             Eteint(0x00)
EH	        1	           EI	             Eteint(0x00)
EI	        0	           FINAL	     Eteint(0x00)
EI	        1	           EI	             Eteint(0x00)
FINAL	        X	           INIT	             Rouge(0x01)
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

int main()
{

  DDRB = 0x03; // Ports utilises en sortie
  // Initialisation de la sortie
   PORTB = 0x00;
 while(true)            
 {
    // Variable booleenne et delai utilises afin d'eviter les rebonds.

   int brightness = 500;
  while(brightness > 0)
  {

            for(uint8_t i = 0; i < 10; i++)
            {
                for(int j = 0; j < brightness; j++)
                {
                    PORTB = 0x01;
                    _delay_ms(1/10);
                }
                    PORTB = 0x00;
                    _delay_ms(1);
            }
     
     brightness--;
}
 _delay_ms(1000);

 }
   

}