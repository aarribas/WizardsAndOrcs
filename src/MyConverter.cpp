#include "MyConverter.h"

std::string Converter::intToString(int i)
{
	std::stringstream out;
	out << i;
	return out.str();
}