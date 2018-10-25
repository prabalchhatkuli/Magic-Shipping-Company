#ifndef VANISHINGCABINET_H
#define VANISHINGCABINET_H
#include "Delivery.h"
#include <string>

class VanishingCabinet : public Delivery
{
private:
	size_t weight;
	string id;
public:
	VanishingCabinet();

	VanishingCabinet(string name, string time_stamp, double weight, string id);

	double get_weight();

	void set_weight(double weight);

	string get_id();

	void print_info();
};
#endif
