#include "ProcessScaleAbsolute.h"

ProcessScaleAbsolute::ProcessScaleAbsolute(Process* successor)
{
	mSuccessor = successor;
}

void ProcessScaleAbsolute::proc(Args* pArgs)
{
	if( (pArgs->Val("command") != "a") && (pArgs->Val("command") != "A") )
	{
		mSuccessor->proc( pArgs );
		return;
	}

	std::string src;
	std::string dest;
	std::string width;
	std::string height;
	std::string log;
	std::string append;
	std::string aspectRatio;
	bool keepAspectRatio;

	width = pArgs->Val("w");
	height = pArgs->Val("h");
	src = pArgs->Val("src");
	dest = pArgs->Val("dest");
	log = pArgs->Val("log");
	append = pArgs->Val("append");
	aspectRatio = pArgs->Val("aspectratio");

	if( width == "" )
		width = "0";

	if( height == "" )
		height = "0";

	if( (aspectRatio == "0") || (aspectRatio == "off") )
		keepAspectRatio = false;
	else 
		keepAspectRatio = true;


	// create logging object
	Logger* logr = new Logger("test");

	if( pArgs->Exists("?") == true )
	{
		showUsage();
		delete( logr );
		return;
	}

	// we can have either width, height or both, but not neither
	// unspecified values will be set to 0 the process routine will
	// determine what that means when it goes to size the image
	if( (height == "0") && (width == "0") )
	{
		logr->Log("\nerror : height, or width, or height/width parameters required to run this process\n");
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
		ProcFile( atoi(width.c_str()), atoi(height.c_str()), nfo, logr, keepAspectRatio );
	}

	// shutdown freeimage
	FreeImage_DeInitialise();
	delete( logr );
	delete( mFiles );
	return;
}

void ProcessScaleAbsolute::ProcFile(int specWidth, int specHeight, FileInfo* fileInfo, Logger* logr, bool keepAspectRatio)
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
	float ratioW;
	float ratioH;
	float newWidth;
	float newHeight;

	width = FreeImage_GetWidth( dib32bpp );
	height = FreeImage_GetHeight( dib32bpp );

	std::cout << "Original Width : " << width << "\n";
	std::cout << "Original Height : " << height << "\n";

	if( specWidth == 0 )
	{

		ratioH = (float)specHeight / (float)height;

		newWidth = (float)width * ratioH;
		newHeight = (float)height * ratioH;
	}
	else if( specHeight == 0)
	{
		ratioW = (float)specWidth / (float)width;

		newWidth = (float)width * ratioW;
		newHeight = (float)height * ratioW;
	}
	else
	{
		ratioH = (float)specHeight / (float)height;
		ratioW = (float)specWidth / (float)width;

		if( keepAspectRatio == false )
		{
			newWidth = (float)width * ratioW;
			newHeight = (float)height * ratioH;
		}
		else if( ratioH >= ratioW )
		{
			newWidth = (float)width * ratioW;
			newHeight = (float)height * ratioW;
		}
		else
		{
			newWidth = (float)width * ratioH;
			newHeight = (float)height * ratioH;
		}

	}

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

	std::cout << "New File Saved At : " << fileInfo->NewFullpath() << "\n";

	// unload the image
	FreeImage_Unload(newDib);
	FreeImage_Unload(finalDib);
	FreeImage_Unload(dib32bpp);
	FreeImage_Unload(dib);

	// return
	return;
}

void ProcessScaleAbsolute::showUsage()
{
	std::cout << "\n";
	std::cout << "picprep - Scale Image By Absolute Values Usage Details: \n";
	std::cout << "-------------------------------------------------------------------------\n";
	std::cout << "\n";
	std::cout << "NOTE : \n";
	
	#ifdef osx
		std::cout << " - ALL PARAMETER VALUES MUST BE WRAPPED IN SINGLE OR DOUBLE QUOTES\n\t(ie : append='-xps' )\n";
	#endif

	std::cout << " - ALL COMMANDS ARE CASE SENSITIVE!!\n\n";

	std::cout << "w - maximum desired width of image [either this or the h param must be present, both parameters are also allowed "
				 " in which case the application will determine the more restricted of the two dimensions and scale both sides by "
				 " the same value to keep perspective the same]\n\n";
	
	std::cout << "h - maximum desired height of image [either this or the w param must be present, both parameters are also allowed "
				 " in which case the application will determine the more restricted of the two dimensions and scale both sides by "
				 " the same value to keep perspective the same]\n\n";

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

	std::cout << "aspectratio - setting aspectratio to 0 (zero) or off tells picprep to ignore the current"
				 "aspect ratio for the image when doing its calculations. Turning off the aspect ratio and "
				 " specifying width and height for an image will cause it to be scaled to that absolute size. "
				 " Picprep defaults to preserving the aspect ratio of an image during calcuations, this is merely "
				 " to turn off the aspect ratio preservation.\n";

	std::cout << "-------------------------------------------------------------------------\n";

	std::cout << "Examples : \n\n";
	#ifdef osx
	std::cout << "picprep a w='100' h='75' src='*.png' dest='*.png'	append='50'\n\n";
	std::cout << "picprep a w='100' h='75' src='*.png' dest='*.png'	append='50' aspectRatio='off'\n\n";
	#endif
	
	#ifdef win32
	std::cout << "picprep a w=100 h=75 src=*.png dest=*.png append=50\n\n";
	std::cout << "picprep a w=100 h=75 src=*.png dest=*.png append=50 aspectRatio=off\n\n";
	#endif
	std::cout << "=========================================================================\n";
}
