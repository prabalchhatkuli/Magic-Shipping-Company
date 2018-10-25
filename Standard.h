#ifndef STANDARD_H
#define STANDARD_H
#include "Delivery.h"
#include <string>

class Standard : public Delivery
{
private:
	double weight;
public:
	virtual double get_weight();

	virtual void set_weight(double weight);

	virtual void print_info();
	virtual string get_id();

protected:
	Standard();
	Standard(string name, string time_stamp, double weight);
};
#endif
