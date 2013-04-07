#ifndef PARAM_H
#define PARAM_H

#include <string>

class Param{
public:
	Param( std::string name, std::string value);
	std::string Name(void);
	std::string Value(void);
private:
	std::string mName;
	std::string mValue;

};

#endif

