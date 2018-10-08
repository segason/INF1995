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

int main()
{

    DDRA = 0x03; // Sortie
    PORTD = 0x01;   // Precision de l'entree
    enum Etat {INIT, EA, EB, EC, ED, EE};   // Definition de la variable etat
  
    Etat etatPres = INIT;   // Initialisation de l'etat
    PORTA = 0;  // Initialisation de la sortie
    while(true)
    {
        bool premiereLecture = PIND & 0x04;      // Variable booleenne et delai utilises afin d'eviter les rebonds.
        _delay_ms(10);
    
        switch (etatPres)    // Determination du changement d'etat a effectuer (s'il y a lieu).
        {
            case(INIT):
                PORTA = 0x01;
                if(PIND & 0x04 && premiereLecture)
                    etatPres = EA;
                break;
                
            case(EA):
                while(PIND & 0x04 && premiereLecture)   // Boucle permettant la couleur ambree de la DELL qui n'en sort que quand le bouton est relache (l'etat devrait donc changer apres un temps infime).
                {
                    for(uint8_t i = 0; i < 255; i++)
                        PORTA = 0x02; 
                    for(uint8_t i = 0; i < 20; i++)
                        PORTA = 0x01;
                }
                if(!(PIND & 0x04) && premiereLecture == false)
                    etatPres = EB;
                break;
            
            case(EB):
                PORTA = 0x02; 
                if(PIND & 0x04 && premiereLecture)
                    etatPres = EC;
                break;
            
            case(EC):
                PORTA = 0x01;
                if(!(PIND & 0x04) && premiereLecture == false)
                    etatPres = ED;
                break;
                
            case(ED):
                PORTA = 0;
                if(PIND & 0x04 && premiereLecture)
                    etatPres = EE;
                break;
                
            case(EE):       // Retour a l'etat initial
                PORTA = 0x02; 
                if(!(PIND & 0x04) && premiereLecture == false)
                    etatPres = INIT;
                break; 
         
            default:        // Default ajoute par precaution
                PORTA = 0;
                break;
        }
    }
}
