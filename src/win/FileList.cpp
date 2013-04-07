#include "FileList.h"

/*
todo: 
- destination coding 
	if blank then it should use the extension of the source file
	if *.* then it should use the extension from the source file
	if *.png then it should store it as a png file
	if *.jpg then it should store it as a jpg file
	etc..
*/
FileList::FileList(std::string src, std::string dest, std::string append)
{
	FileInfo* info;
	std::string newName;
	std::string srcExt;
	std::string destExt;
	FileType destType;

	// get first file in the list
	if((mFileHandle = _findfirst( src.c_str(), &mFile)) == -1L)
	{
			// there are no files
	}
	else
	{
		if( FileIsDir( &mFile ) == false )
		{
			info = GetInfo(&mFile, src, dest, append);

			mFiles.push_back( info );
		}
		
		while( _findnext( mFileHandle, &mFile ) == 0 )
		{
			if( FileIsDir( &mFile ) == false )
			{
				info = GetInfo(&mFile, src, dest, append);
				mFiles.push_back( info );
			}
		}
	}
}
//=====================================================================================

int FileList::Count()
{
	return( mFiles.size() );
}
//=====================================================================================

FileInfo* FileList::GetFileInfo(int index)
{
	if( index > this->Count())
	{
		return 0;
	}

	return( mFiles[index] );
}
//=====================================================================================

bool FileList::FileIsDir(_finddata_t* pFile)
{
	if ( pFile->attrib & _A_SUBDIR )
	{
		return( true );
	}
	else
	{
		return( false );
	}
}
//=====================================================================================

std::string FileList::GetPath( std::string pattern )
{
	int i;
	int lastPos;
	std::string tmp;

	lastPos = 0;

	for( i = 0; i < pattern.length(); i++ )
	{
		if( pattern[i] == '\\' )
		{
			lastPos = i;
		}
	}

	tmp = pattern.substr( 0, lastPos );

	if( pattern.substr( 0, lastPos ).length() == 0 )
	{
		GetCWD( tmp );
		return( tmp );
	}
	else
	{
		return( pattern.substr( 0, lastPos ) );
	}
}
//=====================================================================================

std::string FileList::GetExtension( std::string filename )
{
	int i;
	int lastPos;

	lastPos = 0;

	for( i = 0; i < filename.length(); i++ )
	{
		if( filename[i] == '.' )
		{
			lastPos = i;
		}
	}

	return( filename.substr( lastPos + 1 ) );	
}
//=====================================================================================

std::string FileList::GetNameLessExt( std::string filename )
{
	int i;
	int lastPos;

	lastPos = 0;

	for( i = 0; i < filename.length(); i++ )
	{
		if( filename[i] == '.' )
		{
			lastPos = i;
		}
	}

	return( filename.substr( 0, lastPos ) );
}
//=====================================================================================


bool FileList::GetCWD(std::string& buffer)
{
	char tmpBuffer[512];
	if( _getcwd( tmpBuffer, 512 ) == 0 )
	{
		return false;
	}
	else
	{
		buffer.assign(tmpBuffer);
		return true;
	}
}
//=====================================================================================

FileInfo* FileList::GetInfo( _finddata_t* pFile, std::string pSrc, std::string pDest, std::string pAppend)
{
	//FileInfo* info;
	std::string newName;
	std::string srcExt;
	std::string destExt;
	FileType destType;

	//convert destExt to lowercase
	destExt = GetExtension( pDest );
	
	transform( destExt.begin(), destExt.end(), destExt.begin(), tolower);

	if((destExt == "jpg") || (destExt == "jpeg"))
	{
		destType = JPG;
	}
				
	if((destExt == "png"))
	{
		destType = PNG;
	}

	if((destExt == "*"))
	{
		destType = MATCHSRC;
	}

	if( pAppend.length() != 0 )
	{
		newName = GetNameLessExt( pFile->name );
		newName.append( pAppend );
		newName.append( "." );
	}
	else
	{
		newName = GetNameLessExt(pDest);
		newName.append(".");
	}

	srcExt = GetExtension(pFile->name);
	transform( srcExt.begin(), srcExt.end(), srcExt.begin(), tolower);

	if(destType == JPG)
	{
		newName.append("jpg");
	}
		
	if(destType == PNG)
	{
		newName.append("png");
	}

	if(destType == MATCHSRC)
	{
		newName.append( GetExtension( pFile->name ) );
	}


	if((srcExt == "jpg") || (srcExt == "jpeg"))
	{
		if( destType == MATCHSRC)
		{
			FileInfo* info = new FileInfo(pFile->name, GetPath(pSrc), JPG, newName, GetPath(pDest), JPG);
			return( info );
		}
		else
		{
			FileInfo* info = new FileInfo(pFile->name, GetPath(pSrc), JPG, newName, GetPath(pDest), destType );
			return( info );
		}
	}

	if(srcExt == "png")
	{
		if( destType == MATCHSRC)
		{
			FileInfo* info = new FileInfo(pFile->name, GetPath(pSrc), PNG, newName, GetPath(pDest), PNG );
			return( info );
		}
		else
		{
			FileInfo* info = new FileInfo(pFile->name, GetPath(pSrc), PNG, newName, GetPath(pDest), destType );
			return( info );
		}
	}
}
//=====================================================================================