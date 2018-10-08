#ifndef PWM_H
#define PWM_H
#include <avr/interrupt.h>
#include <avr/io.h> 


class Pwm
{
public:

	Pwm();
	~Pwm();
	void Avance(unsigned int pwm);
	void reculer(unsigned int pwm);
	void Tourner_Gauche(unsigned int pwm);
	void Tourner_Droite(unsigned int pwm);

};

#endif

