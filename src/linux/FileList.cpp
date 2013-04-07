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

	std::string tmpBase;

	std::cout << "FileList::FileList(src) == " << src << "\n";

	tmpBase = GetBasePath( src );

	
	if( tmpBase == src )
	{
		GetCWD(tmpBase);
		// no wildcard or filename information was provided
		//return;
	}

	std::cout << "FileList::FileList.tmpBase == " << tmpBase << "\n";
	
	// open the basepath dir
	DIR * dir;
	
	dir = opendir(tmpBase.c_str());
	
	//TODO : need to see if the open dir fails!!
	
	dirent* de;
	
	std::string tmpName;
	tmpName = GetFilename(src);

	
	while((de = readdir(dir)) != NULL)
	{
		// we need to see if it matches the filename/wildcard stuff?
		if( IsMatch( tmpName, de->d_name ) == true )
		{
			std::cout << "file match found\n";
			info = GetInfo(de, src, dest, append);
			mFiles.push_back( info );
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
	char tmpBuffer[MAXPATHLEN];
	if( getcwd( tmpBuffer, sizeof(tmpBuffer) ) == 0 )
	{
		return false;
	}
	else
	{
		std::cout << "FileList.GetCWD.tmpBuffer == " << tmpBuffer << "\n";
		buffer.assign(tmpBuffer);
		return true;
	}
}
//=====================================================================================

FileInfo* FileList::GetInfo(dirent* pFile, std::string pSrc, std::string pDest, std::string pAppend)
{
	//FileInfo* info;
	std::string newName;
	std::string srcExt;
	std::string destExt;
	FileType destType;

	//convert destExt to lowercase
	destExt = GetExtension( pDest );
	
	// convert destExt to lowercase
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
		newName = GetNameLessExt( pFile->d_name );
		newName.append( pAppend );
		newName.append( "." );
	}
	else
	{
		newName = GetNameLessExt(pFile->d_name);
		newName.append(".");
	}

	srcExt = GetExtension(pFile->d_name);
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
		newName.append( GetExtension( pFile->d_name ) );
	}


	if((srcExt == "jpg") || (srcExt == "jpeg"))
	{
		if( destType == MATCHSRC)
		{
			FileInfo* info = new FileInfo(pFile->d_name, GetPath(pSrc), JPG, newName, GetPath(pDest), JPG);
			return( info );
		}
		else
		{
			FileInfo* info = new FileInfo(pFile->d_name, GetPath(pSrc), JPG, newName, GetPath(pDest), destType );
			return( info );
		}
	}

	if(srcExt == "png")
	{
		if( destType == MATCHSRC)
		{
			FileInfo* info = new FileInfo(pFile->d_name, GetPath(pSrc), PNG, newName, GetPath(pDest), PNG );
			return( info );
		}
		else
		{
			FileInfo* info = new FileInfo(pFile->d_name, GetPath(pSrc), PNG, newName, GetPath(pDest), destType );
			return( info );
		}
	}
}
//=====================================================================================

std::string FileList::GetBasePath( std::string pPath )
{
	int res;
	
	res = pPath.rfind( "/" );
	
	if( res == pPath.npos )
	{
		return( pPath );
	}
	else
	{
		std::string basePath;
		basePath = pPath.substr(0, res);
		return( basePath );
	}
}
//=====================================================================================

std::string FileList::GetFilename(std::string pPath )
{
	int res;
	
	res = pPath.rfind( "/" );
	
	if( res == pPath.npos )
	{
		// nothing was found
		return pPath;
	}
	else
	{
		std::string basePath;
		basePath = pPath.substr(res+1);
		return( basePath );
	}
}
//=====================================================================================

std::string FileList::GetExtension( std::string filename )
{
	int res;
	
	res = filename.rfind( "." );
	
	if( res == filename.npos )
	{
		// nothing was found
	}
	else
	{
		std::string extension;
		extension = filename.substr(res+1);
		return( extension );
	}
}
//=====================================================================================

bool FileList::IsMatch(std::string pSearch, std::string pName )
{

	if( fnmatch(pSearch.c_str(), pName.c_str(), NULL ) == FNM_NOMATCH)
	{
		return false;
	}
	else
	{
		return true;
	}

}
//=====================================================================================
