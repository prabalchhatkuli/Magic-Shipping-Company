#include "VanishingCabinet.h"

	VanishingCabinet::VanishingCabinet()
	{
	}

	VanishingCabinet::VanishingCabinet(string name, string time_stamp, double weight, string id)
		:Delivery(name, time_stamp)
	{
		set_weight(weight);
		this->id = id;
	}

	double VanishingCabinet::get_weight()
	{
		return weight;
	}

	void VanishingCabinet::set_weight(double weight)
	{
		this->weight = weight;
	}

	string VanishingCabinet::get_id()
	{
		return this->id;
	}

	void VanishingCabinet::print_info()
	{
                Delivery::print_info();
		cout << " " << get_id() << " " << get_time_stamp() << " " << "Vanishing Cabinet";
		cout << endl;
	}
