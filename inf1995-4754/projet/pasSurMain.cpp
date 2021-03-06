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

uint8_t compteur = 0, petitSkip = 0, rapport = 0, nbCarre =0;
char directions[3] = {};
Del del;
Pwm moteur;
can intensite;


char transmissionPcVersUart ( ) {

	while (!( UCSR0A & (1<<RXC0)) && !(PIND & 0x04)) //
	{
	}
               
    	return UDR0;//Retourne le data recu par lwe buffer

}


void faireSon(unsigned int pwm)
{
       if(pwm >= 45)
       {
        TCCR0A = (1 << WGM01) | (1 << COM0A0);
	
	TCCR0B = 0x04 ;
		
	OCR0A = 15625.0/(110.0 * pow(2, (pwm-45)/12.0));
       }
       else
        {
            TCCR0A = (1 << WGM01) | (1 << COM0A0);
	
            TCCR0B = 0x04 ;
		
            OCR0A = 0;
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


void faireIntersection()
{
    if (directions[compteur] == 'd')
    {
		moteur.pivotDroit(150);
		_delay_ms(500);
		moteur.Avance(150);
		while(!(bit1 || bit2 || bit3))
				lireDirection();	
    
		while(!bit5)
		{
			lireDirection();
			if(!bit1 && bit2 && !bit3)	// 0 1 0 X X
				moteur.Avance(150);

			else if (bit1 && !bit2 && !bit3) // 1 0 0 X X
				moteur.pivotGauche(150);

			else if (!bit1 && !bit2 && bit3) // 0 0 1 X X
				moteur.Tourner_Droite(150);

			else if (!bit1 && !bit2 && !bit3 && bit4)
				moteur.Tourner_Droite(150);	// 0 0 0 1 X
		
			else
				moteur.Avance(150);
		}          
    }
    
    else if (directions[compteur] == 'g')
    {
		moteur.pivotGauche(150);
		_delay_ms(600);	
		moteur.Avance(150);
		while(!(bit3 || bit4 || bit5))
		{
				lireDirection();			
		}	
	
		while(!bit1)
		{
			lireDirection();
			if(!bit3 && bit4 && !bit5)	// X X 0 1 0
			moteur.Avance(150);
		
                    else if (bit3 && !bit4 && !bit5) // X X 1 0 0
			moteur.Avance(150);
		
                    else if (!bit3 && !bit4 && bit5) // X X 0 0 1
			moteur.pivotDroit(150);

                    else if (bit2 && !bit3 && !bit4 && !bit5)	// X 1 0 0 0
			moteur.Tourner_Gauche(160);
		
                    else
			moteur.Avance(150);
		
		
		}
	
               // if(!bit1 && !bit2 && bit3 && bit4 && bit5) //Pour la cloche ronde
               //     moteur.Tourner_Gauche(150);
					
    }
    compteur++;
    
}

void faireIntersectionTriangle()
{
    /*
    if (directions[compteur] == 'd')
    {
       moteur.pivotDroit(150);
       _delay_ms(500);
        lireDirection();
        
        while(!bit3)
        {
           lireDirection();
           moteur.pivotGauche(150);
        }
        while(bit1 || bit2 || bit3 || bit4 || bit5)
        {
		lireDirection();
		if(!bit3 && bit4 && !bit5)	// X X 0 1 0
                    moteur.Avance(150);
		
                else if (bit3 && !bit4 && !bit5) // X X 1 0 0
                    moteur.Avance(150);
		
                else if (!bit3 && !bit4 && bit5) // X X 0 0 1
                    moteur.pivotDroit(150);

                else if (bit2 && !bit3 && !bit4 && !bit5)	// X 1 0 0 0
                    moteur.Tourner_Gauche(160);
		
                else
                    moteur.Avance(150);
        }
        while(!bit1)
        {
            lireDirection();
            moteur.Tourner_Gauche(150);
        }
        
        
                                            
    }
    else if (directions[compteur] == 'g')
    {
        moteur.pivotGAUCHE(150);
       _delay_ms(500);
        lireDirection();
        
                   
        while(!bit3)
        {
           lireDirection();
            moteur.Tourner_Droite(170);
        }
        while(bit1 || bit2 || bit3 || bit4 || bit5)
	{
		lireDirection();
		if(!bit1 && bit2 && !bit3)	// 0 1 0 X X
			moteur.Avance(150);

		else if (bit1 && !bit2 && !bit3) // 1 0 0 X X
			moteur.pivotGauche(150);

		else if (!bit1 && !bit2 && bit3) // 0 0 1 X X
			moteur.Tourner_Droite(150);

		else if (!bit1 && !bit2 && !bit3 && bit4)
			moteur.Tourner_Droite(150);	// 0 0 0 1 X
		
		else
			moteur.Avance(150);
	}
	while(!bit5)
        {
            lireDirection();
            moteur.Tourner_Droite(150);
        }
   
    }               
    compteur++;
    */
}

void suivreLigne()
{
    if(bit1 && bit2 && bit3 && bit4 && bit5) // 1 1 1 1 1
    {
		while(bit1 && bit5)
		{
			lireDirection();
			moteur.Avance(150);
		}
		
		if(!bit1 && !bit2 && !bit3 && !bit4 && !bit5)
		{
			while(!bit3)
			{
				lireDirection();
				moteur.pivotDroit(150);
			}
		}
			
		if(compteur >= 3)
                {
			moteur.Avance(0);
                        while(true)
			{}
                }
                else
                    moteur.Avance(150);
    }
    else if(bit1 && bit2 && !bit3 && !bit4 && !bit5) // 1 1 0 0 0
        {
            moteur.Tourner_Gauche(150);
        }
        else if(bit1 && !bit2 && !bit3 && !bit4 && !bit5) //1 0 0 0 0
        {
            moteur.pivotGauche(150);
        }
        else if(!bit1 && bit2 && !bit3 && !bit4 && !bit5) // 0 1 0 0 0
        {
            moteur.Tourner_Gauche(150);
        }
        else if((!(bit1) && !(bit2) && bit3 && bit4 && bit5) || ( !bit1 && bit2 && bit3 && bit4 && bit5)) // 0 0 1 1 1
        {
           moteur.Avance(150);
           _delay_ms(700);
           lireDirection();
           
           if (bit1 || bit2 || bit3 || bit4 || bit5)	//Si tu vois la ligne, continue
           {
		nbCarre++;
		if(nbCarre == 3)
		{
			moteur.pivotDroit(150);
			_delay_ms(1000);
			while(!bit3)
                        {
                            moteur.pivotDroit(150);
                            lireDirection();
                        }
		}
				
            }
            else 		//Si tu vois rien, tourne le coin
            {
               
                while(!bit3)
                {
                    moteur.pivotDroit(150);
                    lireDirection();
                }
            }
        }
        else if(bit1 && bit2 && bit3 && !(bit4) && !(bit5)) // 1 1 1 0 0
        {
            moteur.pivotGauche(150);
           _delay_ms(100);
        }
        else if (!bit1 && !bit2 && !bit3 && !bit4 && bit5) //0 0 0 0 1
        {
            moteur.pivotDroit(150);
        }
        else if (!bit1 && !bit2 && !bit3 && bit4 && bit5) //0 0 0 1 1
        {
            moteur.Tourner_Droite(150);
        }
        else if (!bit1 && !bit2 && !bit3 && bit4 && !(bit5)) // 0 0 0 1 0
        {
            moteur.Tourner_Droite(150);
        }
        
	else if (!(bit1) && !(bit2) && bit3 && !bit4 && !bit5) // 0 0 1 0 0
	{
		moteur.Avance(150);
	}
	else if (!bit1 && bit2 && bit3 && !bit4 && !bit5) //0 1 1 0 0
	{
		moteur.Tourner_Gauche(150);
	}
	else if (!bit1 && !bit2 && bit3 && bit4 && !bit5) // 0 0 1 1 0
	{
		moteur.Tourner_Droite(150);
	}   
        else if (!bit1 && !bit2 && !bit3 && !bit4 && !bit5)	// 0 0 0 0 0
	{
			moteur.Avance(150);
			_delay_ms(1000); // Peut-être à augmenter
			lireDirection();
                        
			if (!bit1 && !bit2 && !bit3 && !bit4 && !bit5) // INTERSECTION
			{
                            faireIntersection();
			}
			/*else // POINTILLÉS
                        {
                         
				if(petitSkip >= 2 && petitSkip < 7)
                                {
					faireSon(100); 
                                }
                                petitSkip++;  
                            
                        }*/
			
        }
        else if(!bit1 && bit2 && bit3 && bit4 && !bit5) // Essai pour gerer l'intersection en triangle 0 1 1 1 0
        {
                faireIntersectionTriangle();
        }
        
        //////////TRY DEEZ SHIETS//////////////
       /* else if(bit1 && bit2 && bit3 && bit4 && !bit5) // 1 1 1 1 0
        {
            moteur.pivotGauche(150);
            _delay_ms(100);
        }
        else if(!bit1 && bit2 && bit3 && bit4 && bit5) // 0 1 1 1 1
        {
            moteur.pivotDroit(150);
            _delay_ms(100);
        }*/
        else
        {
            del.allumerRouge(0);
        }
}

void verifierLuminosite()
{
    rapport = intensite.lecture(6) >> 2; 
    if(rapport < 80 )/*&& !estSortiDuTunel*/
    {
        PORTA = 0b1100;
    }
    else/*&& passeDansLeTunel*/
    {
      PORTA = 0x00;
    }
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
    while (true)
    {
        verifierLuminosite();
        lireDirection();
        suivreLigne();
    }
 
}






