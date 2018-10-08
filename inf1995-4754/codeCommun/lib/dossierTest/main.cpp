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


int main()
{
    Del notreDel;
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
            
    }
}
