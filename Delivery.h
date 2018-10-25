#ifndef DELIVERY_H
#define DELIVERY_H
#include <iostream>
#include <string>
using namespace std;

class Delivery
{
private:
	string name_of_sender;
	string time_stamp;


public:
	virtual string get_time_stamp();

	virtual string get_sender_name();

	virtual void set_name(string name);
	virtual void print_info();
	virtual string get_id();
	virtual double get_weight();

protected:
	Delivery();
	Delivery(string name, string time_stamp);
};
#endif
