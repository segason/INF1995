
#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>



/* Voici le tableau des etats

  00 = ETEINT
  01 = ROUGE

  Etat Present     Entree     Prochain Etat    Sortie 
     INIT            0            INIT           00
     INIT            1            EA             00
     EA              0            EA             00
     EA              1            EB             00
     EB              0            EB             00
     EB              1            EC             00
     EC              0            EC             00
     EC              1            ED             00
     ED              0            ED             00
     ED              1            ACTIVER        00
     ACTIVER         x            INIT           01            

*/

 enum Etat {
	INIT = 0,
	EA,
	EB,
	EC,
	ED,
	ACTIVER,

};



int main() {

	DDRA = 0xFF; //DEL en sortie

	Etat etat = INIT;

	bool enfonce = false;


	//Boucle infini
	for (;;) {
	
	switch (etat) {
	case INIT:
		PORTA = 0xff; //La del est fermer au depart
		
		if (PIND & 0x04) { 		// bouton appuyer
			_delay_ms(10);
			if(PIND & 0x04){
				enfonce = true;
				_delay_ms(10);
			}
		}
		else
			if(enfonce){
				enfonce = false;
				etat = EA;
			}
				
		break;

	
	case EA:
		if (PIND & 0x04) { 		// bouton appuyer
			_delay_ms(10);
			if(PIND & 0x04){
				enfonce = true;
				_delay_ms(10);
			}
		}
		else
			if(enfonce){
				enfonce = false;
				etat = EB;
			}
		break;

	
	case EB:
		if (PIND & 0x04) { 		// bouton appuyer
			_delay_ms(10);
			if(PIND & 0x04){
				enfonce = true;
				_delay_ms(10);
			}
		}
		else
			if(enfonce){
				enfonce = false;
				etat = EC;
			}
		break;


	case EC:
		if (PIND & 0x04) { 		// bouton appuyer
			_delay_ms(10);
			if(PIND & 0x04){
				enfonce = true;
				_delay_ms(10);
			}
		}
		else
			if(enfonce){
				enfonce = false;
				etat = ED;
			}
		break;


	case ED:
		if (PIND & 0x04) { 		// bouton appuyer
			_delay_ms(10);
			if(PIND & 0x04){
				enfonce = true;
				_delay_ms(10);
			}
		}
		else
			if(enfonce){
				enfonce = false;
				etat = ACTIVER;
			}
		break;

	

	case ACTIVER:
		PORTA = 0x02; // del devient rouge
		_delay_ms(1000);
		etat = INIT; //On remet letat initial apres le delay de 1s
		break;
	}



	
}

	return 0;
}
