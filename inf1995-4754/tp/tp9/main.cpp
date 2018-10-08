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


struct Tableau
{
    uint8_t tableau[2];
};



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

// De l'USART vers le PC


void lecture(Memoire24CXXX& memoire, uint8_t& adresse, 
uint8_t& inst, uint8_t& operande)
{
	_delay_ms(5);
	uint8_t instruction[2] = {};
	//memoire.lecture(adresse, instruction, 2);
	//memoire.lecture(adresse, inst, 1);
	//memoire.lecture(adresse + 1, operande, 1);
	
    Tableau monTableau;
    monTableau.tableau[0] = instruction[0];
    monTableau.tableau[1] = instruction[1];
	return monTableau;
}
/*
uint8_t lecture(Memoire24CXXX& memoire, uint8_t& adresse)
{
	_delay_ms(5);
	uint8_t instruction[2] = {};
	memoire.lecture(adresse, instruction, 2);
	adresse += 2;
	
	return instruction[2];
}
*//*
void transmissionUARTVersPc ( uint8_t donnee ) {

	while (!( UCSR0A & (1<<UDRE0))) //Attendre que le tampon soient libre. 
	{
	}
               
    	UDR0 = donnee; 

}*/
char transmissionPcVersUart ( ) {

	while (!( UCSR0A & (1<<RXC0)) && !(PIND & 0x04)) //
	{
	}
               
    	return UDR0;//Retourne le data recu par lwe buffer

}


void faireSon(unsigned int midi)
{
	TCCR0A = (1 << WGM01) | (1 << COM0A0);
	TCCR0B = 0x04 ;
	
	if(midi >= 45 && midi <= 81)
		OCR0A = 15625.0/(110.0 * pow(2, (midi-45)/12.0));
		
	if(midi == 0)
		OCR0A = 0;
		
}





int main()
{
	DDRB = 0xFF;
	DDRD = 0B11110000;
        Del del;
        Memoire24CXXX memoire;
	memoire.init();
        
	
        
        
        initialisationUART();
        
        uint8_t tableau[255];
        tableau[0] = transmissionPcVersUart();
        tableau[1] = transmissionPcVersUart();
        
        uint16_t taille = (tableau[0] << 8) | tableau[1];
        
        for (int i = 2; i < taille; i++){
            tableau[i] = transmissionPcVersUart();
        }
        
        for (int i = 2; i < taille; i++){
            memoire.ecriture(i , tableau[i]);
            _delay_ms(5);
            del.allumerRouge(0);
            _delay_ms(25);
            del.eteindreDel();
            _delay_ms(25);
        }
         
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       
        uint8_t adresse = 0x02;
	uint8_t adresseBoucle;
	uint8_t repBoucle;
	uint8_t compteur;
	uint8_t operande;
	uint8_t instruction;
	enum Etat{ON, OFF, END};
	Etat monEtat = OFF;
	
	Pwm moteur;

        
	//Sequence de demarrage
	for(uint8_t i = 0; i < 3; i++)
	{
            del.allumerRouge(0);
            _delay_ms(500);
            del.allumerVert(0);
            _delay_ms(500);
	}
	
	del.eteindreDel();
        
	while(monEtat != END)
        {
            Tableau tab = lecture(memoire, adresse, instruction, operande);
           
            instruction = tab.tableau[0];
               inst[1] = tab.tableau[1];
            switch (instruction)
            { 
                    case (0x01):
                            monEtat = ON;
                            break;
                            
                    case (0x02):
                            if(monEtat == ON)
                                for(uint8_t i = 0; i < operande; i++)
                                    _delay_ms(25);
                    break;
                    
                    case (0x44):
                            if(monEtat == ON)
                                    del.allumerVert(0);
                    break;
                    
                    case (0x45):
                            if(monEtat == ON)
                                del.eteindreDel();
                    break;
                    
                    case (0x48):
                            if(monEtat == ON)
                                faireSon(operande);
                    
                    break;
                    
                    case (0x09):
                            if(monEtat == ON)
                                faireSon(0);
   
                    break;
                    
                    case (0x60):
                            if(monEtat == ON)
                                moteur.Avance(0);
                    break;
                    
                     case (0x61):
                            if(monEtat == ON)
                                moteur.Avance(0);
                                
                    break;
                    
                    case (0x62):
                            if(monEtat == ON)
                                moteur.Avance(operande);
                    break;
                    
                    case (0x63):
                            if(monEtat == ON)
                                moteur.reculer(operande);
                    break;
                    
                    case (0x64):
                            if(monEtat == ON)
                                moteur.Tourner_Droite(128);
                    break;
                    
                    case (0x65):
                            if(monEtat == ON)
                                moteur.Tourner_Gauche(128);
                    break;
                    
                    case (0xC0):
                            if(monEtat == ON)
                            {
                                  adresseBoucle = adresse;
                                  repBoucle = operande;
                                  compteur = 0;  
                            }
                    break;
                    
                    case (0xC1):
                            if(monEtat == ON)
                            {
                                if(compteur < repBoucle)
                                {
									adresse = adresseBoucle;
									compteur++;
                                }
                            }
                    break;
                    
                    case (0xFF):
                            monEtat = END;
                    break;
            }
            adresse += 2;

        }	
	
	
	return 0;
}
