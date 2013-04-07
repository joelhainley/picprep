#ifndef PROCESSFORMAT_H
#define PROCESSFORMAT_H

#include "common.h"

#ifdef win32
#include "..\win\FileList.h"
#include "..\win\FileInfo.h"
#endif

#ifdef osx
#include "../osx/FileList.h"
#include "../osx/FileInfo.h"
#endif

#ifdef linux
#include "../linux/FileList.h"
#include "../linux/FileInfo.h"
#endif

// common stuff
#include "args.h"
#include "process.h"
#include "Logger.h"
#include "FreeImage.h"

class ProcessFormat : public Process {
public:
	ProcessFormat(Process* successor);
	void proc(Args* args);

private:
	Process* mSuccessor;
	FileList* mFiles;
	void ProcFile(FileInfo* fileInfo, Logger* logr);
	void showUsage();
};
#endif
