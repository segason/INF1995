#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>



using namespace std;


/* Voici le tableau des etats

   00 = ETEINT
   01 = ROUGE
   02 = VERT
   03 = AMBREE
   

   Etat Present   Entree     Prochain Etat     Sortie
       INIT         0            INIT             01
       INIT         1            EA               01
       EA           0            EB               03
       EA           1            EA               03
       EB           0            EB               02
       EB           1            EC               02
       EC           0            ED               01
       EC           1            EC               01
       ED           0            ED               00
       ED           1            EE               00
       EE           0            INIT             02
       EE           1            EE               02                




*/

//Enum pour les etats
enum Etat {
	INIT,
	EA,
	EB,
	EC,
	ED,
	EE
};


int main() {
	DDRB = 0xFF; //DEL en sortie
	bool enfonce = false;
	Etat etat = INIT;

	PORTB = 0x02;	//DEL rouge

	//Boucle infini
	for (;;) {
		
		switch (etat) {
		
		//Etat  initial
		case INIT:
			PORTB = 0x02; //A letat initiale, la del est rouge.

			if (PIND & 0x04) { 	//Si le bouton est appuyer, on passe a leta suivant (etat a). 
				_delay_ms(10);	//Sinon, on reste a letat init (on fait rien).
				if(PIND & 0x04){
					enfonce = true;
					etat = EA;
					_delay_ms(10);
				}
			}

			break;
		
			//Etat A
		case EA: 
                        
                    
			if(PORTB == 0x01){	//DEL ambre
			PORTB = 0x02;
                         _delay_us(400);
                        }
                        
			else if(PORTB == 0x02){
			PORTB = 0x01;
                         _delay_us(600);
                        }
                        
                       
                        
	
			if (PIND & 0x04) { 	//Si le bouton est encore enfonce, on ne fait rien
				_delay_ms(10);	
				if(PIND & 0x04){
					enfonce = true;
				}
			}
			else
				if(enfonce){		//lorsque le bouton est relache, on passe a EB
					etat = EB;
					enfonce = false;
				}
			break;
		
			//Etat B
		case EB:
			PORTB = 0x01; //DEL verte

			if (PIND & 0x04) { 
				_delay_ms(10);	
				if(PIND & 0x04){
					enfonce = true;
					etat = EC;
					_delay_ms(10);
				}
			}

			break;
		
			//Etat c
		case EC:
			PORTB = 0x02; //DEL rouge

			if (PIND & 0x04) { 
				_delay_ms(10);	
				if(PIND & 0x04){
					enfonce = true;
					_delay_ms(10);
				}
			}
			else
				if(enfonce){
					etat = ED;
					enfonce = false;
				}
			break;
		
			//Etat d
		case ED:
			PORTB = 0xFF; //DEL fermee

			if (PIND & 0x04) { 
				_delay_ms(10);	
				if(PIND & 0x04){
					enfonce = true;
					etat = EE;
					_delay_ms(10);
				}
			}

			break;
		
			//Etat e
		case EE:
			PORTB = 0x01; //DEL verte

			if (PIND & 0x04) { 
				_delay_ms(10);	
				if(PIND & 0x04){
					enfonce = true;
					_delay_ms(10);
				}
			}
			else
				if(enfonce){
					etat = INIT;
					enfonce = false;
				}
			break;

		}
	}
	return 0;
}
