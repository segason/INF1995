#ifndef PWMSON_H
#define PWMSON_H
#include <avr/interrupt.h>
#include <avr/io.h> 


class PwmSon
{
public:

	PwmSon();
	~PwmSon();
        
	void faireSon(unsigned int pwm);
	void silence(unsigned int pwm);
        void ajustementPwmSon();



private:

};

#endif
