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


int main()
{
    DDRB = 0x03; // Sortie      
    PORTD = 0x00;   // Precision de l'entree
    PORTB = 0;  // Initialisation de la sortie
    can intensite;  // Déclaration de l'objet à partir duquel la fonction qui lit l'intensité est appelée.
    while(true)
    { 
        uint8_t rapport = intensite.lecture(1) >> 2; //Lecture de l'intensité lumineuse et décalage vers la droite pour ne garder que les 8 bits les plus significatids lors de la conversion implicite en uint8_t.
    
            if(rapport < 80)    // Couleur verte de la DEL si l'intensité est inférieure à 80 (faible intensité lumineuse).
                PORTB = 0x02;
            
            else if(rapport >= 80 && rapport < 160) // Couleur ambrée de la DEL si l'intensité est supérieure ou égale à 80 et inférieure à 160 (intensité lumineuse moyenne).
            {
                PORTB = 0x02;
                _delay_ms(10);
                PORTB = 0x01;
                _delay_ms(10);
            }
                
            else if(rapport >= 160) // Couleur rouge de la DEL si l'intensité est supérieure ou égale à 160 (forte intensité lumineuse).
                 PORTB = 0x01;

            else
                PORTB = 0x00;   // Else implémenté par précaution.
        
        
    }
}
