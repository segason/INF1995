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
#include <avr/interrupt.h>

enum Etat {INIT, EA, EB, EC, ED, EE};
volatile Etat etatPres = INIT;  // Definition de la variable etat
volatile bool changementEtat = 0;

// placer le bon type de signal d'interruption

// a prendre en charge en argument

ISR (INT0_vect) 
{
    // laisser un delai avant de confirmer la reponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)
    bool boutonEtatUn = PIND & 0x04;
    _delay_ms(30);

    // Se souvenir ici si le bouton est presse ou relache

    bool boutonEtatDeux = PIND & 0x04;

    // changements d'etats tels que ceux de la
    if(boutonEtatUn == boutonEtatDeux)
        changementEtat = 1;
    // semaine precedente


//     // Voir la note plus bas pour comprendre cette instruction et son role
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) 
{

    // cli est une routine qui bloque toutes les interruptions. Il serait bien mauvais d'etre interrompu alors que le microcontroleur n'est pas pret... `
    cli ();


    // configurer et choisir les ports pour les entrees

    // et les sorties. DDRx... Initiali     `sez bien vos variables

    DDRB = 0x03; // Sortie      
    PORTD = 0x01;   // Precision de l'entree
    PORTB = 0;  // Initialisation de la sortie


    // cette procédure ajuste le registre EIMSK

    // de ATmega324PA pour permettre les interruptions externes

    EIMSK |= _BV(INT0);


    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= _BV(ISC00) ;


    // sei permet de recevoir a nouveau des interruptions.

    sei ();

}

int main()
{

  
// Initialisation de l'etat
    initialisation();
   

    while(true)
    { 
        switch (etatPres)    // Determination du changement d'etat a effectuer (s'il y a lieu).
        {
            case(INIT):
                PORTB = 0x01;
                if(changementEtat)
                {
                    etatPres = EA;
                    changementEtat = 0;
                }
                break;
                
            case(EA):
                if(PORTB == 0x02)
                {
                        PORTB = 0x01;
                        _delay_ms(0.25);
                }
                else if(PORTB == 0x01)
                {
                    PORTB = 0x02;
                    _delay_ms(4);
                    
                }
                    
                if(changementEtat)
                {
                    etatPres = EB;
                    changementEtat = 0;
                }
                break;
            
            case(EB):
                PORTB = 0x02; 
                if(changementEtat)
                {
                    etatPres = EC;
                    changementEtat = 0;
                }
                break;
            
            case(EC):
                PORTB = 0x01;
                if(changementEtat)
                {
                    etatPres = ED;
                    changementEtat = 0;
                }
                break;
                
            case(ED):
                PORTB = 0;
                if(changementEtat)
                {
                    etatPres = EE;
                    changementEtat = 0;
                }
                break;
                
            case(EE):       // Retour a l'etat initial
                PORTB = 0x02;
                if(changementEtat)
                {
                    etatPres = INIT;
                    changementEtat = 0;
                }
                break; 
         
            default:        // Default ajoute par precaution
                PORTB = 0;
                break;
        }
    }
}