#ifndef GRIFFIN_H
#define GRIFFIN_H
#include "Standard.h"
#include <string>

class Griffin : public Standard
{
private:
	string id;
public:
	Griffin();

	Griffin(string name, string time_stamp, double weight, string id);

	string get_id();
	void print_info();

};
#endif
