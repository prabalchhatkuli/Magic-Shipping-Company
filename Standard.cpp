#include "Standard.h"

    double Standard::get_weight()
	{
		return this->weight;
	}

	void Standard::set_weight(double weight)
	{
		this->weight = weight;
	}

	void Standard::print_info()
	{
                Delivery::print_info();
	}

	string Standard::get_id()
	{

	}

	Standard::Standard()
	{

	}

	Standard::Standard(string name, string time_stamp, double weight)
		:Delivery(name, time_stamp)
	{
		set_weight(weight);
	}

