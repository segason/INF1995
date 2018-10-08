/*
Fichier: TP7-1.cpp
Auteur(s): Alexandre Vu, Louis-Philippe Chouinard
Date de creation: 23 février 2016
Description: Programme permettant l'implémentation de la séquence d'instruction demandée au problème 1 du TP7.
*/

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


enum Etat {INIT, EA, EB, EC, ED};
volatile Etat etatPres = INIT;  // Definition de la variable etat

uint8_t compteurUn = 0; //Creation des variables "compteurs"
uint8_t compteurDeux = 0; //Creation des variables "compteurs"

int main()
{
    DDRB = 0x03; // Sortie      
    PORTD = 0x00;   // Precision de l'entree
    PORTB = 0;  // Initialisation de la sortie
  
    while(true)         //Boucle infinie permettant la scrutation.
    { 
        switch (etatPres)       //Vérification de l'état présent.
        {
            case (INIT):            //Initialisation des compteurs. Passage au prochain état si le bouton est appuyé.
                compteurUn = 0;
                compteurDeux = 0;
                if(!(PIND & 0x04))
                    etatPres = EA;
                break;
            
            case (EA):          //Incrémente le compteur à chaque cycle et vérifie à chaque fois si le compteur atteint 120 ou si le bouton est relâché. Si c'est le cas, la DEL clignote et on passe au prochain état.
                if(compteurUn == 120 || (PIND & 0x04))
                {
                    for(uint8_t i = 0; i < 5; i++)
                    {
                        PORTB = 0x02;
                        _delay_ms(50);
                        PORTB = 0x00;
                        _delay_ms(50);
                    }
                    etatPres = EB;
                }
                compteurUn++;
                _delay_ms(100);
                break;
           
            case (EB):
                _delay_ms(2000);  //Attente de 2 secondes avant le passage au prochain état, gardant ainsi la dernie valeur pour la DEL (ainsi fermée).
                etatPres = EC;
                break;
            
            case (EC):              //Pour cet état la DEL clignote en rouge dépendamment du nombre atteint par le premier compteur. À chaque cycle le deuxième compteur  
                PORTB = 0x01;       //incrémente et on passe au prochain état lorsque la moitié de la valeur du premier compteur est atteinte.
                _delay_ms(250);
                PORTB = 0x00;
                _delay_ms(250);
                compteurDeux++;
                if(compteurDeux == compteurUn / 2)
                    etatPres = ED;
                break;
                
            case (ED):             //La DEL reste 2 secondes au vert, puis est fermée et revient à l'état initial.
                PORTB = 0x02;
                _delay_ms(2000);
                PORTB = 0x00;
                etatPres = INIT;
                
            default:        //État par défaut mis au cas-où.
                PORTB = 0x00;
        }
        
       

    }
}