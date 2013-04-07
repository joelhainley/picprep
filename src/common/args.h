#ifndef ARGS_H
#define ARGS_H

#include "common.h"

#include <string>
#include <iostream>
#include <vector>

#include "param.h"

class Args{
public:
	Args(int argc, char** argv);
	int		Count();
	std::string	Key(int index);
	std::string	Val(int index);
	std::string	Val(std::string key);
	bool	Exists(std::string key);
private:
	std::vector<Param*> mParams;
};


#endif
