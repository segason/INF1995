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
  PORTD = 0x01;  // Precision de l'entree
  enum Etat {INIT, EA, EB, EC, ED, EE, EF, EG, EH, EI, FINAL};  // Definition de la variable etat
  PORTB = 0;     // Initialisation de la sortie
  Etat etatPres = INIT; // Initialisation de l'etat

  
 while(true)            
 {
     bool premiereLecture = PIND & 0x04;        // Variable booleenne et delai utilises afin d'eviter les rebonds.
   _delay_ms(10);
   
   
     switch (etatPres)          // Determination du changement d'etat a effectuer (s'il y a lieu).
     {
         case(INIT):
            PORTB = 0;
            if(PIND & 0x04 && premiereLecture)
                etatPres = EA;
            break;
         case(EA):
            if(!(PIND & 0x04) && premiereLecture == false)
                etatPres = EB;
            break;
         case(EB): 
              if(PIND & 0x04 && premiereLecture)
                etatPres = EC;
              break;
         case(EC):
            if(!(PIND & 0x04) && premiereLecture == false)
                etatPres = ED;
            break;// Ce default est
         case(ED): 
              if(PIND & 0x04 && premiereLecture)
                etatPres = EE;
              break;
         case(EE):
            if(!(PIND & 0x04) && premiereLecture == false)
                etatPres = EF;
            break;
         case(EF): 
            if(PIND & 0x04 && premiereLecture)
                etatPres = EG;
            break;
         case(EG):
            if(!(PIND & 0x04) && premiereLecture == false)
                etatPres = EH;
            break;
         case(EH): 
            if(PIND & 0x04 && premiereLecture)
                etatPres = EI;   
            break;
         case(EI):
            if(!(PIND & 0x04) && premiereLecture == false)
                etatPres = FINAL;
            break;
            
         case(FINAL):           // Etat allumant la DEL et effectuant un retour a l'etat initial.
              PORTB = 0x01;
            _delay_ms(1000);
            etatPres = INIT;
             break;
                            
         default:       //Default au cas-ou
             etatPres = INIT;
             break;
    }
   
 }
}