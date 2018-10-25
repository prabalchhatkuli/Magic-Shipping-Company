#include "Griffin.h"

	Griffin::Griffin()
	{
	}

	Griffin::Griffin(string name, string time_stamp, double weight, string id)
		:Standard(name, time_stamp, weight)
	{
		this->id = id;
	}

	string Griffin::get_id()
	{
		return this->id;
	}

	void Griffin::print_info()
	{
		cout << get_sender_name() << " " << get_id() << " " << get_time_stamp() << " " << "Standard - Griffin";
		cout << endl;
	}
