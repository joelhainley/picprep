#ifndef PROCESS_H
#define PROCESS_H

#include "args.h"

class Process
{
public:
	virtual void proc(Args* args) = 0;
private:
};

#endif

