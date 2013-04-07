#ifndef PROCESSSCALEABSOLUTE_H
#define PROCESSSCALEABSOLUTE_H

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

//common stuff
#include "args.h"
#include "process.h"
#include "Logger.h"
#include "FreeImage.h"

class ProcessScaleAbsolute : public Process {
public:
	ProcessScaleAbsolute(Process* successor);
	void proc(Args* args);

private:
	void ProcFile(int specWidth, int specHeight, FileInfo* fileInfo, Logger* logr, bool keepPerspective);
	void showUsage();

	Process* mSuccessor;
	FileList* mFiles;
};
#endif
