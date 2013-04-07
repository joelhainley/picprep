#include <iostream>
#include <fstream>


#include "common.h"

#ifdef win32
#include <io.h>
#include "..\win\FileList.h"
#endif

#ifdef osx
#include "../osx/FileList.h"
#endif

#ifdef linux
#include "../linux/FileList.h"
#endif

// common stuff
#include "args.h"
#include "ProcessDefault.h"
#include "ProcessBPP.h"
#include "ProcessFormat.h"
#include "ProcessScaleAbsolute.h"
#include "ProcessScaleRatio.h"


int main(int argc, char** argv)
{

	// capture the arguments from the command line
	Args* args = new Args(argc, argv);

	/*
	FileList* filelist = new FileList("w:\\mp3s\\*.*", "c:\\work\\", "-togo");
	FileInfo* nfo;

	for( int i = 0; i < filelist->Count(); i++)
	{
		nfo = filelist->GetFileInfo( i );
		std::cout << nfo->NewPath() <<"\\" << nfo->NewName() << "\n";

	}
	*/

	// create the chain of responsibility for this application
	ProcessDefault* procDef = new ProcessDefault(0);
	ProcessBPP* procBPP = new ProcessBPP( procDef );
	ProcessFormat* procFmt = new ProcessFormat( procBPP );
	ProcessScaleRatio* procRatio = new ProcessScaleRatio( procFmt );
	ProcessScaleAbsolute* procAbs = new ProcessScaleAbsolute( procRatio );

	// proc the command line with the chain
	procAbs->proc( args );

	// exit the routine
	return( 0 );
}
