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



volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 
// placer le bon type de signal d'interruption

// a prendre en charge en argument

ISR (TIMER1_COMPA_vect) 
{
    minuterieExpiree = 1;
}


ISR (INT0_vect) 
{
    _delay_ms(10);
    
    if(PIND & 0x04)
        boutonPoussoir = 1;

    // anti-rebond
}

void partirMinuterie (uint16_t duree) 
{

    minuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisee par 1024

    // interruption apres la duree specifiee

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = (1 << WGM12);

    TCCR1B = (1 << CS12 | 1<<CS10 );

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A) ;

}

void initialisation ( void ) 
{

    // cli est une routine qui bloque toutes les interruptions. Il serait bien mauvais d'etre interrompu alors que le microcontroleur n'est pas pret... `
    cli ();


    // configurer et choisir les ports pour les entrees et les sorties. DDRx... Initialisez bien vos variables

    DDRB = 0x03; // Sortie      
    PORTD = 0x01;   // Precision de l'entree
    PORTB = 0x00;  // Initialisation de la sortie
    boutonPoussoir = 0;
    minuterieExpiree = 0;
    // cette procédure ajuste le registre EIMSK de ATmega324PA pour permettre les interruption externes

    EIMSK |= _BV(INT0);


    // il faut sensibiliser les interruptions externes aux changements de niveau du bouton-poussoir en ajustant le registre EICRA

    EICRA |= _BV(ISC00) ;

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}

int main()
{

  
    // Initialisation de l'etat
    initialisation();
   
    _delay_ms(2000);
    PORTB = 0x01;
    _delay_ms(100);
    PORTB = 0x00;
    partirMinuterie(7812);
    
    boutonPoussoir = 0;
    do 
    {
       
    } while (minuterieExpiree == 0 && boutonPoussoir == 0 );

    // Une interruption s'est produite. Arreter toute

    // forme d'interruption. Une seule reponse suffit.

    cli ();

    // Verifier la reponse

    
    if(boutonPoussoir == 1)
         PORTB = 0x02;

    else
         PORTB = 0x01;
}