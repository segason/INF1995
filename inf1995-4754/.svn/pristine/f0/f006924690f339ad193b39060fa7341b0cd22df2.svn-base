#include "Memoire24CXXX.h"
#include "delControl.h" 
#include "Moteur.h" 
#include "can.h"
#include "minuterie.h" 
#include "Memoire24CXXX.h" 
#include "PwmSon.h"
#include "PWM.h"
#include <avr/io.h>
#include <avr/interrupt.h> 
#define F_CPU 8000000
#include <util/delay.h>
using namespace std;
    
bool bit1 = false, bit2 = false, bit3 = false, bit4 = false, bit5 = false, enfonceGauche = false, enfonceDroit = false;
bool aFaitTriangle = false, devraitFinir = false;
uint8_t compteur = 0, petitSkip = 0, rapport = 0, nbCarre =0;
char directions[3] = {};
Del del;
Pwm moteur;
can intensite;

void verifierLuminosite()
{
    rapport = intensite.lecture(6) >> 2; 
    if(rapport < 80 )
    {
        PORTA = 0b1100;
    }
    else
    {
      PORTA = 0x00;
    }
}
char transmissionPcVersUart ( ) {

	while (!( UCSR0A & (1<<RXC0)) && !(PIND & 0x04)) //
	{
	}
               
    	return UDR0;//Retourne le data recu par lwe buffer

}


void faireSon(unsigned int pwm)
{
       if(pwm > 45)
       {
        TCCR0A = (1 << WGM01) | (1 << COM0A0);
	
		TCCR0B = 0x04 ;
		
		OCR0A = 15625.0/(110.0 * pow(2, (pwm-45)/12.0));
       }
       else
        {
			TCCR0B &= 0x00;
       }
}

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premier registres pour vous éviter des complications

UBRR0H = 0;

UBRR0L = 0xCF;

// permettre la reception et la transmission par le UART0

UCSR0A = (1 << TXC0) | (1 << RXC0) ;

UCSR0B =  (1 << RXEN0) | (1 << TXEN0) ; // L'émetteur USART est activé en réglant TXEN dans UCSRB.

// Format des trames: 8 bits, 1 stop bits, none parity

UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

}

void transmissionUARTVersPc ( uint8_t donnee ) {

	while (!( UCSR0A & (1<<UDRE0))) //Attendre que le tampon soient libre. 
	{
	}
               
    	UDR0 = donnee; 
}

void lireDirection()
{
        bit1 = PINC & 0b00000001; // capteur_gauche
        bit2 = PINC & 0b00000010; // centre centre gauche
        bit3 = PINC & 0b00000100; // centre 
        bit4 = PINC & 0b00001000; // centre centre droit 
        bit5 = PINC & 0b00010000; // capteur_droit
}


void fairePointilles()
{
	del.allumerRouge(0);
	while(true)
	{
		while(bit1 || bit2 || bit3 || bit4 || bit5)	
		{
			lireDirection();
			
			if(bit1 && bit2 && !bit3 && !bit4 && !bit5) // 1 1 0 0 0
				moteur.Tourner_Gauche(95);
        
			else if(bit1 && !bit2 && !bit3 && !bit4 && !bit5) //1 0 0 0 0
				moteur.pivotGauche(95);
      
			else if(!bit1 && bit2 && !bit3 && !bit4 && !bit5) // 0 1 0 0 0
				moteur.Tourner_Gauche(95);
			
            else if((!bit1 && !bit2 && bit3 && bit4 && bit5) || ( !bit1 && bit2 && bit3 && bit4 && bit5)) //0 0 1 1 1 ... 0 1 1 1 1
            {
				faireSon(0);	
				aFaitTriangle = false;
				del.eteindreDel();
                return;
			}
			
			else if (!bit1 && !bit2 && !bit3 && !bit4 && bit5) //0 0 0 0 1
				moteur.pivotDroit(95);
       
			else if (!bit1 && !bit2 && !bit3 && bit4 && bit5) //0 0 0 1 1
				moteur.Tourner_Droite(95);
  
			else if (!bit1 && !bit2 && !bit3 && bit4 && !(bit5)) // 0 0 0 1 0
				moteur.Tourner_Droite(95);
        
			else if (!(bit1) && !(bit2) && bit3 && !bit4 && !bit5) // 0 0 1 0 0
				moteur.Avance(95);

			else if (!bit1 && bit2 && bit3 && !bit4 && !bit5) //0 1 1 0 0
				moteur.Tourner_Gauche(95);
	
			else if (!bit1 && !bit2 && bit3 && bit4 && !bit5) // 0 0 1 1 0
				moteur.Tourner_Droite(95);

		}
						
		faireSon(70);	//Son puisque'on passe sur le 3e blanc
			
		if(petitSkip == 7)
		{
			faireSon(0);
			aFaitTriangle = false;
			del.eteindreDel();
            return;
		}
							
		while (!bit1 && !bit2 && !bit3 && !bit4 && !bit5)	
		{	
            lireDirection();
			moteur.Avance(95);
		}
		
		petitSkip++;			
	}
}

void faireIntersection()
{
    if (directions[compteur] == 'd')
    {
		moteur.pivotDroit(95);
		_delay_ms(500);
		moteur.Avance(90);
		while(!bit2)
			lireDirection();	
    
		while(!bit5)
		{
			lireDirection();
			if(!bit1 && bit2 && !bit3)	// 0 1 0 X X
				moteur.Avance(95);

			else if (bit1 && !bit2 && !bit3) // 1 0 0 X X
				moteur.pivotGauche(95);

			else if (!bit1 && !bit2 && bit3) // 0 0 1 X X
				moteur.Tourner_Droite(95);
				
			else if (bit1 && bit2 && !bit3) // 1 1 0 X X
				moteur.Tourner_Gauche(95);

			else if (!bit1 && !bit2 && !bit3 && bit4)
				moteur.Tourner_Droite(95);	// 0 0 0 1 X
		
			else
				moteur.Avance(95);
		}
		moteur.pivotDroit(95);
		_delay_ms(100); 
        moteur.Avance(95);
        _delay_ms(100);
    }
    
    else if (directions[compteur] == 'g')
    {
		moteur.pivotGauche(95);
		_delay_ms(600);	
		moteur.Avance(90);
		while(bit4)
			lireDirection();			
	
		while(!bit1)
		{
			lireDirection();
			if(!bit3 && bit4 && !bit5)	// X X 0 1 0
			moteur.Avance(95);
		
            else if (bit3 && !bit4 && !bit5) // X X 1 0 0
				moteur.Avance(95);
		
            else if (!bit3 && !bit4 && bit5) // X X 0 0 1
				moteur.pivotDroit(95);
				
			else if (bit3 && bit4 && !bit5) // X X 1 1 0
				moteur.Tourner_DroiteInt(95);

			else if (bit2 && !bit3 && !bit4 && !bit5)	// X 1 0 0 0
				moteur.Tourner_GaucheInt(95);
		
            else
				moteur.Avance(95);
		}
		moteur.pivotGauche(95);
		_delay_ms(100);
        moteur.Avance(95);
        _delay_ms(100);
					
    }
    compteur++;
    
}

void faireIntersectionTriangle()
{
    del.allumerVert(0);
    
    if (directions[compteur] == 'd')
    {
       while(bit1 || bit2 || bit3 || bit4 || bit5)
       {
           moteur.pivotDroit(95);
           lireDirection();
        }
        moteur.Avance(95);
        _delay_ms(800);
        while(!bit2)
        {
            lireDirection();
            moteur.Tourner_Gauche(95);
        }
       
         while(bit1 || bit2 || bit3 || bit4 || bit5)
		{
			del.allumerRouge(0);
			lireDirection();
			if(!bit1 && bit2 && !bit3)	// 0 1 0 X X
				moteur.Avance(95);

			else if (bit1 && !bit2 && !bit3) // 1 0 0 X X
				moteur.Tourner_GaucheInt(95);

			else if ((bit4) || (bit4 && bit1))	// X X X 1 X ou 1 X X 1 X
				moteur.pivotDroit(95);

			else if (!bit1 && !bit2 && bit3) // 0 0 1 X X
				moteur.Tourner_DroiteInt(95);


		}
		del.allumerVert(0);
		moteur.Avance(95);
		_delay_ms(500);
		
        while(!bit3)
        {
            lireDirection();
            moteur.Tourner_Gauche(95);
        }
        
        
                                            
    }
    else if (directions[compteur] == 'g')
    {
       while(bit1 || bit2 || bit3 || bit4 || bit5)
       {
           moteur.pivotGauche(95);
           lireDirection();
        }
        moteur.Avance(95);
        _delay_ms(800);
        while(!bit4)
        {
            lireDirection();
            moteur.Tourner_Droite(95);
        }
       
         while(bit1 || bit2 || bit3 || bit4 || bit5)
		{
			del.allumerRouge(0);
			lireDirection();
			if(!bit3 && bit4 && !bit5)	// X X 0 1 0
				moteur.Avance(95);

			else if (bit3 && !bit4 && !bit5) // X X 1 0 0 
				moteur.Tourner_Gauche(95);

			else if ((bit2) || (bit2 && bit5))	// X 1 X X X ou X 1 X X 1
				moteur.pivotGauche(95);

			else if (!bit3 && !bit4 && bit5) // X X 0 0 1
				moteur.Tourner_Droite(95);


		}
		del.allumerVert(0);
		moteur.Avance(95);
		_delay_ms(500);
		
        while(!bit3)
        {
            lireDirection();
            moteur.Tourner_Droite(95);
        }
   
    }               
    compteur++;
    aFaitTriangle = true;
    del.eteindreDel();
    
    
}

void suivreLigne()
{
	
    if(bit1 && bit2 && bit3 && bit4 && bit5) // 1 1 1 1 1
    {
		while(bit1 && bit5)
		{
			lireDirection();
			moteur.Avance(95);
		}
		if(compteur >= 2)
        {
			moteur.Avance(0);
			devraitFinir = true;
         }
                
		else if(!bit1 && !bit2 && !bit3 && !bit4 && !bit5)
		{
			while(!bit3)
			{
				lireDirection();
				moteur.pivotDroit(95);
			}
		}

        else
			moteur.Avance(95);
    }
	/*else if(bit1 && bit2 && !bit3 && !bit4 && !bit5) // 1 1 0 0 0
	{
		moteur.Tourner_Gauche(120);
	}*/
	else if(bit1 && !bit2 && !bit3 && !bit4 && !bit5) //1 0 0 0 0
		moteur.pivotGauche(95);
	
	else if(!bit1 && bit2 && !bit3 && !bit4 && !bit5) // 0 1 0 0 0
		moteur.Tourner_Gauche(95);
	
	else if((!bit1 && !bit2 && bit3 && bit4 && bit5) || (!bit1 && bit2 && bit3 && bit4 && bit5)) // 0 0 1 1 1
	{
	   moteur.Avance(95);
	   _delay_ms(950);
	   lireDirection();
	   
	   if (bit1 || bit2 || bit3 || bit4 || bit5)	//Si tu vois la ligne, continue
	   {
			nbCarre++;
			if(nbCarre == 3)
			{
				moteur.pivotDroit(95);
				_delay_ms(1000);
				while(!bit3)
				{
					moteur.pivotDroit(95);
					lireDirection();
				}
			}	
		}
		
		else 		//Si tu vois rien, tourne le coin
		{
		   nbCarre = 0;
			while(!bit3)
			{
				moteur.pivotDroit(85);
				lireDirection();
			}
			moteur.Avance(200);
			_delay_ms(50);
			petitSkip = 0;
		}
	}
	/*else if(bit1 && bit2 && bit3 && !(bit4) && !(bit5)) // 1 1 1 0 0
	{
		moteur.pivotGauche(95);
	   _delay_ms(100);
	}*/
	else if (!bit1 && !bit2 && !bit3 && !bit4 && bit5) //0 0 0 0 1
		moteur.pivotDroit(95);
	
	/*else if (!bit1 && !bit2 && !bit3 && bit4 && bit5) //0 0 0 1 1
	{
		moteur.Tourner_Droite(120);
	}*/
	else if (!bit1 && !bit2 && !bit3 && bit4 && !(bit5)) // 0 0 0 1 0
		moteur.Tourner_Droite(95);
	
        
	else if (!(bit1) && !(bit2) && bit3 && !bit4 && !bit5) // 0 0 1 0 0
		moteur.Avance(95);
	
	else if (!bit1 && bit2 && bit3 && !bit4 && !bit5) //0 1 1 0 0
		moteur.Tourner_Gauche(95);
	
	else if (!bit1 && !bit2 && bit3 && bit4 && !bit5) // 0 0 1 1 0
		moteur.Tourner_Droite(95);
	 
    else if (!bit1 && !bit2 && !bit3 && !bit4 && !bit5)	// 0 0 0 0 0
	{
		_delay_ms(200);		//afin de s'assurer d'etre sur du blanc
		lireDirection();
		
		if(!bit1 && !bit2 && !bit3 && !bit4 && !bit5)	//si toujours sur du blanc
		{
			moteur.Avance(95);
			_delay_ms(600); 
			lireDirection();
            verifierLuminosite();
            
			if ((!bit1 && !bit2 && !bit3 && !bit4 && !bit5) && rapport > 80) // INTERSECTION
				faireIntersection();

			else if(rapport > 80 && aFaitTriangle)// POINTILLÉS
            {       
				//del.allumerRouge(0);
                petitSkip++; 
                if(petitSkip == 2)	//si petitSkip est a 2, on passe aux pointilles courts
					fairePointilles();     
            }
                            
        }
			
    }
    
    else if(!bit1 && bit2 && bit3 && bit4 && !bit5) // Essai pour gerer l'intersection en triangle 0 1 1 1 0
        faireIntersectionTriangle();
    
        /*else
        {
            del.allumerRouge(0);
        }*/
}



int main()
{
    DDRB = 0b11111100;
    DDRD = 0b11110000;
    DDRC = 0x00;
    DDRA = 0x0F;

    
///////////// BOUTONS DE DIRECTION ///////////////
  
    
    
	while (compteur<3) 
        {
			if (!(PINB & 0x01)) { 	//bouton droit
				_delay_ms(10);
				if(!(PINB & 0x01)){
					enfonceDroit = true;
                                        PORTA = 0b1000;
					_delay_ms(10);
				}
			}
			else if (!(PINB & 0x02)) 
                        { 		//bouton gauche
				_delay_ms(10);
				if(!(PINB & 0x02))
                                {
					enfonceGauche = true;
                                         PORTA = 0b0100;
					_delay_ms(10);
				}
			}
			else if(enfonceDroit)
                        {
                            enfonceDroit = false;
                            PORTA = 0x00;
                            directions[compteur] = 'g';
                            compteur++;
                        }
			else if(enfonceGauche)
                        {
                            enfonceGauche = false;
                            PORTA = 0x00;
                            directions[compteur] = 'd';
                            compteur++;
                        }
				
        }

	
		
	
////////////// FIN DE DETECTION DE BOUTONS /////////////////////
 
 
 
    compteur = 0;
    moteur.Avance(205);
    _delay_ms(200);
    
    while (!devraitFinir)
    {
        verifierLuminosite();
        lireDirection();
        suivreLigne();
    }
    moteur.Avance(0);
    del.allumerVert(0);
    faireSon(0);
 
}






