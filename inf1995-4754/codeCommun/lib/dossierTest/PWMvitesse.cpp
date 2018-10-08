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
#include "Moteur.h"



Moteur::Moteur()
{
    DDRC = 0xFF;
}

Moteur::~Moteur()
{}

void Moteur::eteint()
{
    PORTC = 0x00;
    _delay_ms(50/3);
}
void Moteur::premiereVitesse()
{
    PORTC = 0x00;
    _delay_ms(12.5);
    PORTC = 0x03;
    _delay_ms(25/6);
}
void Moteur::deuxiemeVitesse()
{
    PORTC = 0x00;
    _delay_ms(25/3);
    PORTC = 0x03;
    _delay_ms(25/3);
}
void Moteur::troisiemeVitesse()
{
    PORTC = 0x00;
    _delay_ms(25/6);
    PORTC = 0x03;
    _delay_ms(12.5);
}
void Moteur::quatriemeVitesse()
{
    PORTC = 0x03;
    _delay_ms(50/3);
}

void Moteur::eteintQC()
{
    PORTC = 0x00;
    _delay_ms(2.5);
}
void Moteur::premiereVitesseQC()
{
    PORTC = 0x00;
    _delay_ms(1.875);
    PORTC = 0x03;
    _delay_ms(0.625);
}
void Moteur::deuxiemeVitesseQC()
{
    PORTC = 0x00;
    _delay_ms(1.125);
    PORTC = 0x03;
    _delay_ms(1.125);
}
void Moteur::troisiemeVitesseQC()
{
    PORTC = 0x00;
    _delay_ms(0.625);
    PORTC = 0x03;
    _delay_ms(1.875);
}
void Moteur::quatriemeVitesseQC()
{
    PORTC = 0x03;
    _delay_ms(2.5);
}




/*
int main()
{
  DDRB = 0x03; // Ports utilises en sortie
  // Initialisation de la sortie
   PORTB = 0x00;
    while(true)            
    {
        for(int i = 0; i < 120; i++)
        {
            premiereVitesse();
        }
      
        for(int i = 0; i < 120; i++)
        {
            deuxiemeVitesse();
        
        }
        for(int i = 0; i < 120; i++)
        {
            troisiemeVitesse();
     
        }
     
        for(int i = 0; i < 120; i++)
        {
            quatriemeVitesse();
         
        }
        
        for(int i = 0; i < 120; i++)
        {
            cinquiemeVitesse();
        }
        for(int i = 0; i < 800; i++)
        {
            premiereVitesseQC();
        }
      
        for(int i = 0; i < 800; i++)
        {
            deuxiemeVitesseQC();
        
        }
        for(int i = 0; i < 800; i++)
        {
            troisiemeVitesseQC();
        }
     
        for(int i = 0; i < 800; i++)
        {
            quatriemeVitesseQC();
         
        }

        for(int i = 0; i < 800; i++)
        {
            cinquiemeVitesseQC();
        }
        
    }
}
*/
/*
 * Ici, on utilisera le robot pour la première fois. On fera tourner une seule roue pour l'instant. 
 * Par contre, nous imposerons des fréquences de 60 Hz pour la fréquence de la période du signal PWM 
 * dans un premier temps et de 400 Hz dans un deuxième temps. De plus, nous vous demandons de faire 
 * fonctionner le PWM pour un rapport a/b de 0%, 25%, 50% et 75% et 100% pendant 2 secondes chaque. 
 * Votre roue tournera donc 20 secondes au total (les 10 premières à 60 Hz et à 400 Hz pour les 10 autres). 
 * Le chargé de laboratoire vérifiera avec l'oscilloscope que vous générez les signaux correctement.
 * */
/*for(int i = 0; i < 125; i+=25)
        {
           int timer = 0;
            while(timer <= 2000)
            {
                for(int j = 0; j < i; j++)
                {
                    PORTB = 0x01;
                }
                for(int j = 0; j < (100-i); j++)
                {
                    PORTB = 0x00;
                }
                _delay_ms(10);
                timer += 10;
            }
        }
 
 switch(rapport)
                {
                    case (ZERO): 
                        while(timer <= 2000)
                        {
                            PORTB = 0x00;
                            _delay_ms(10);
                            timer += 10;
                        }
                        rapport = VC;
                        timer = 0;
                        break;
                      
                    case (VC):
                        while(timer <= 2000)
                        {
                            PORTB = 0x00;
                            _delay_ms(1/60*0.75);
                            PORTB = 0x01;
                            _delay_ms(1/60*0.25);
                            
                            timer += 1/60;
                        }
                        rapport = CQ;
                        timer = 0;
                        break;
                        
                    case (CQ):
                        while(timer <= 2000)
                        {
                            PORTB = 0x01;
                            _delay_ms(1/60*0.50);
                            PORTB = 0x00;
                            _delay_ms(1/60*0.50);
                            timer += 1/60;
                        }
                        rapport = SQ;
                        timer = 0;
                        break;
                        
                    case (SQ):
                        while(timer <= 2000)
                        {
                            PORTB = 0x01;
                            _delay_ms(1/60*0.75);
                            PORTB = 0x00;
                            _delay_ms(1/60*0.25);
                            timer += 1/60;
                        }
                        rapport = CT;
                        timer = 0;
                        break;
                        
                    case (CT):
                        while(timer <= 2000)
                        {
                            PORTB = 0x01;
                            _delay_ms(1/60);
                            timer += 1/60;
                        }
                        rapport = FIN;
                        timer = 0;
                        break; 
                    
                    case (FIN):
                        rapport = ZERO;
                        if(frequence == SX)
                            frequence == QC;
                        else
                            frequence == SX;
                        break;

                }
 
 */
 
