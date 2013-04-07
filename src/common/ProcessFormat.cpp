#include "ProcessFormat.h"


ProcessFormat::ProcessFormat(Process* successor)
{
	mSuccessor = successor;
}

void ProcessFormat::proc(Args* pArgs)
{
	// i wrote the user's manual and used c for the _convert_ command and
	// when I coded it up I used f for the _format_ command so I decided to
	// put them both in there ;-)
	if( (pArgs->Val("command") != "c") && (pArgs->Val("command") != "C") &&
		(pArgs->Val("command") != "f") && (pArgs->Val("command") != "F"))
	{
		mSuccessor->proc( pArgs );
		return;
	}

	std::string src;
	std::string dest;
	std::string log;
	std::string append;

	src = pArgs->Val("src");
	dest = pArgs->Val("dest");
	log = pArgs->Val("log");
	append = pArgs->Val("append");

	// create logging object
	Logger* logr = new Logger("test");

	if( pArgs->Exists("?") == true )
	{
		showUsage();
		delete( logr );
		return;
	}

	if(src == "")
	{
		logr->Log("\nerror : src parameter required to run this process\n");
		delete( logr );
		return;
	}

	if(dest == "")
	{
		logr->Log("\nerror : dest parameter required to run this process\n");
		delete( logr );
		return;
	}

	mFiles = new FileList(src, dest, append );

	FileInfo* nfo;


	// if we didn't find any files then exit
	if( mFiles->Count() == 0 )
	{
		//notify user
		logr->Log("\nerror : no files found to process\n");
		delete( logr );

		//exit
		return;
	}


	// fire up freeimage
	FreeImage_Initialise();

	for( int i = 0; i < mFiles->Count(); i++)
	{
		nfo = mFiles->GetFileInfo( i );
		// will destination file be overwritten?

		// process this file
		ProcFile( nfo, logr );
	}

	// shut down freeimage
	FreeImage_DeInitialise();

	return;
}

void ProcessFormat::ProcFile(FileInfo* fileInfo, Logger* logr)
{
	FIBITMAP* dib;
	int curBPP;

	// if the source and dest are of the same type 
	// AND they have the same name and the same path
	// then we probably don't need to run this one
	if(fileInfo->Type() == fileInfo->NewType())
	{
		if(fileInfo->Fullpath() == fileInfo->NewFullpath())
		{
            return;
		}
	}



	switch( fileInfo->Type() )
	{
		case JPG:
			dib = FreeImage_Load(FIF_JPEG, fileInfo->Fullpath().c_str());
			break;
		case PNG:
			dib = FreeImage_Load(FIF_PNG, fileInfo->Fullpath().c_str() );
			break;
		default:
			logr->Log("image type unknown");
			return;
	}

	std::cout << "Processing File : " << fileInfo->Fullpath() << "\n";

	// opening file fails
	if(!dib)
	{
		logr->Log("failure opening file");
		return;
	}

	bool res;		// holds results for save operation

	switch( fileInfo->NewType() )
	{
		case JPG:
			res = FreeImage_Save(FIF_JPEG, dib, fileInfo->NewFullpath().c_str(), 0);
			break;
		case PNG:
			res = FreeImage_Save(FIF_PNG, dib, fileInfo->NewFullpath().c_str(), 0 );
			break;
		default:
			logr->Log("target image type unknown");
			return;
	}

	// log new filename
	std::cout << "New File Saved At : " << fileInfo->NewFullpath() << "\n";

	// unload dib to reclaim memory
	FreeImage_Unload(dib);

	// return
	return;
}

void ProcessFormat::showUsage()
{
	std::cout << "\n";
	std::cout << "picprep - Change Image Format Usage Details: \n";
	std::cout << "-------------------------------------------------------------------------\n";
	std::cout << "\n";
	std::cout << "NOTE : \n";

	#ifdef osx
	std::cout << " - ALL PARAMETER VALUES MUST BE WRAPPED IN SINGLE OR DOUBLE QUOTES\n\t(ie : append='-xps' )\n";
	#endif

	std::cout << " - ALL COMMANDS ARE CASE SENSITIVE!!\n\n";

	std::cout << "src - [required] - either a specific file name, or a valid wild-card sequence "
				 "for files in a specific directory, the application will attempt to "
				 "open the files based upon their extensions. if a format cannot be "
				 "determined from the extension, or the file cannot be opened, the "
				 "application will report an error, logging it to the log file if one "
				 "has been specified, and continue to process\n\n";

	std::cout << "dest - [required] - either a specific file name, or a specific directory ( if a "
				 "directory that is different from the source directory is specified, "
				 "and no append parameter is specified, the files will be saved with the "
				 "same name as the source filename, if the directories are the same, and "
				 "no append parameter has been specified, the application will display an "
				 "error to the user and exit )\n\n";

	std::cout << "append - characters to append to the newly created file\n\n";

	std::cout << "-------------------------------------------------------------------------\n";

	std::cout << "Example : \n\n";

	
	#ifdef osx
	std::cout << "picprep f src='*.png' dest='*.jpg'\n\n";
	#endif
	
	#ifdef win32
	std::cout << "picprep f src=*.png dest=*.jpg\n\n";
	#endif
	std::cout << "=========================================================================\n";
}
