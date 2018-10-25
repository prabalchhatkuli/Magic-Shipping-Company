#include "Delivery.h"

string Delivery::get_time_stamp()
{
	return this->time_stamp;
}

string Delivery::get_sender_name()
{
	return this->name_of_sender;
}

void Delivery::set_name(string name)
{
	this->name_of_sender = name;
}

void Delivery::print_info()
{
        cout<<this->name_of_sender;
}

string Delivery::get_id()
{

}

double Delivery::get_weight()
{

}


Delivery::Delivery()
{
}

Delivery::Delivery(string name, string time_stamp)
{
         this->name_of_sender = name;
         this->time_stamp = time_stamp;
}
