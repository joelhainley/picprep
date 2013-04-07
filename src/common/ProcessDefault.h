#include "args.h"
#include "process.h"

#ifndef PROCESSDEFAULT_H
#define PROCESSDEFAULT_H

class ProcessDefault : public Process {
public:
	ProcessDefault(Process* successor);
	void proc(Args* args);

private:
	Process* mSuccessor;
	void showUsage();

};
#endif

