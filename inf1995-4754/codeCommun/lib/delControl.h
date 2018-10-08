/*
 * Classe permettant l'acces au convertisseur analogique/numerique
 * du microcontroleur ATMega16 de Atmel.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Code qui n'est sous aucune license.
 *
 */

#ifndef DEL_H
#define CDEL_H

#include <avr/io.h> 

/*
 * Classe can:
 *   Le constructeur initialise le convertisseur.
 *   Une lecture enclanche une conversion et le resultat
 *   est retourne sur 16 bits.
 *
 */

class Del
{
public:

   Del();
   ~Del();
    void allumerRouge(uint8_t tempsEteint);
    void allumerVert(uint8_t tempsEteint);
    void faireAmbree(uint8_t tempsEteint);
    void eteindreDel();
    void routineInterruption();
    void initialisation ()

private:
    bool etat_;
};

#endif

