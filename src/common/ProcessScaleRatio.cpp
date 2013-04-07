#include "ProcessScaleRatio.h"

using namespace std;
ProcessScaleRatio::ProcessScaleRatio(Process* successor)
{
	mSuccessor = successor;
}

void ProcessScaleRatio::proc(Args* pArgs)
{
	if( (pArgs->Val("command") != "p") && (pArgs->Val("command") != "P") )
	{
		mSuccessor->proc( pArgs );
		return;
	}

	std::string src;
	std::string dest;
	std::string percentage;
	std::string log;
	std::string append;

	percentage = pArgs->Val("r");
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

	if(percentage == "")
	{
		logr->Log("\nerror : 'r' parameter required to run this process\n");
		return;
	}

	if(src == "")
	{
		logr->Log("\nerror : src parameter required to run this process\n");
		return;
	}

	if(dest == "")
	{
		logr->Log("\nerror : dest parameter required to run this process\n");
		return;
	}

	mFiles = new FileList(src, dest, append );

	FileInfo* nfo;

	// if we didn't find any files then exit
	if( mFiles->Count() == 0 )
	{
		//notify user
		//close log file
		//exit
		logr->Log( "No Files Found" );
		return;
	}

	// fire up freeimage
	FreeImage_Initialise();

	for( int i = 0; i < mFiles->Count(); i++)
	{
		nfo = mFiles->GetFileInfo( i );
		// will destination file be overwritten?

		// process this file
		ProcFile( atof( percentage.c_str() ), nfo, logr );
	}

	// shutdown freeimage
	FreeImage_DeInitialise();

	exit;
}

void ProcessScaleRatio::ProcFile(float percentage, FileInfo* fileInfo, Logger* logr)
{
	FIBITMAP* dib;
	FIBITMAP* newDib;
	FIBITMAP* finalDib;
	FIBITMAP* dib32bpp;
	int origBPP;

	// open file
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

	// determine bitdepth of current file
	origBPP = FreeImage_GetBPP(dib);

	if( origBPP != 32 )
		dib32bpp = FreeImage_ConvertTo32Bits( dib );
	else
		dib32bpp = dib;

	int width;
	int height;

	width = FreeImage_GetWidth( dib32bpp );
	height = FreeImage_GetHeight( dib32bpp );

	std::cout << "Original Width : " << width << "\n";
	std::cout << "Original Height : " << height << "\n";

	int newWidth;
	int newHeight;

	newWidth = width * percentage;
	newHeight = height * percentage;

	std::cout << "New Width : " << newWidth << "\n";
	std::cout << "New Height : " << newHeight << "\n";

	newDib = FreeImage_Rescale(dib32bpp, newWidth, newHeight, FILTER_BILINEAR);

	if( origBPP != 32 )
	{
		switch( origBPP )
		{
			case 8:
				finalDib = FreeImage_ConvertTo8Bits( newDib );
				break;
			case 16:
				finalDib = FreeImage_ConvertTo16Bits555( newDib );
				break;
			case 24:
				finalDib = FreeImage_ConvertTo24Bits( newDib );
				break;
		}
	}
	else
	{
		finalDib = newDib;
	}


	bool res;		// holds results for save operation

	// save new file
	switch( fileInfo->NewType() )
	{
		case JPG:
			res = FreeImage_Save(FIF_JPEG, finalDib, fileInfo->NewFullpath().c_str(), 0);
			break;
		case PNG:
			res = FreeImage_Save(FIF_PNG, finalDib, fileInfo->NewFullpath().c_str(), 0 );
			break;
		default:
			logr->Log("target image type unknown");
			return;
	}

	// log new filename
	std::cout << "New File Saved At : " << fileInfo->NewFullpath() << "\n";

	// unload dibs / reclaim memory
	FreeImage_Unload(dib);
	FreeImage_Unload(newDib);
	FreeImage_Unload(finalDib);
	FreeImage_Unload(dib32bpp);
	return;
}

void ProcessScaleRatio::showUsage()
{
	std::cout << "\n";
	std::cout << "picprep - Scale Image Ratio Usage Details: \n";
	std::cout << "-------------------------------------------------------------------------\n";
	std::cout << "\n";
	std::cout << "NOTE : \n";
	
	#ifdef osx
		std::cout << " - ALL PARAMETER VALUES MUST BE WRAPPED IN SINGLE OR DOUBLE QUOTES\n\t(ie : append='-xps' )\n";
	#endif

	std::cout << " - ALL COMMANDS ARE CASE SENSITIVE!!\n\n";

	std::cout << "r - [required] - ratio to scale the picture by\n\n";

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
	std::cout << "picprep p r='0.5' src='*.png' dest='*.png' append='50'\n\n";
	#endif
	
	#ifdef win32
	std::cout << "picprep p r=0.5 src=*.png dest=*.png append=50\n\n";
	#endif
	std::cout << "=========================================================================\n";
}
