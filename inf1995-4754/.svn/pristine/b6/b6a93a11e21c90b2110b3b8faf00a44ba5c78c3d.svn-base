#ifndef MINUTERIE_H
#define MINUTERIE_H

#endif // !MINUTERIE_H



class Minuterie
{
public:
	Minuterie();

	~Minuterie(){};

	uint16_t getDuree() const;
	void setDuree(uint16_t duree);
	void partirMinuterie(uint16_t duree);
	bool estExpiree();
        void setExpiree(uint8_t valeur);

private:
	volatile uint8_t minuterieExpiree_;
	uint16_t duree_;
        volatile uint8_t boutonPoussoir_; 
};
