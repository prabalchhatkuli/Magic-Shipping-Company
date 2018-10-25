#include "Owl.h"

	Owl::Owl()
	{
	}

	Owl::Owl(string name, string time_stamp, double weight, string id)
		:Standard(name, time_stamp, weight)
	{
		this->id = id;
	}
	string Owl::get_id()
	{
		return this->id;
	}

	void Owl::print_info()
	{
                Delivery::print_info();
		cout << " " << get_id() << " " << get_time_stamp() << " " << "Standard - Owl";
		cout << endl;
	}

