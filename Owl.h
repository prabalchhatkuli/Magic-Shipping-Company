#ifndef OWL_H
#define OWL_H
#include "Standard.h"
#include <string>

class Owl : public Standard
{
private:
	string id;
public:
	Owl();

	Owl(string name, string time_stamp, double weight, string id);
	string get_id();
	void print_info();

};
#endif
