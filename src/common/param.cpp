#include "param.h"

Param::Param( std::string name, std::string value)
{
	mName = name;
	mValue = value;
}

std::string Param::Name(void)
{
	return( mName );
}

std::string Param::Value(void)
{
	return( mValue );
}
