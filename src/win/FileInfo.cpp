#include "FileInfo.h"

FileInfo::FileInfo( std::string filename, std::string path, FileType type, std::string newName, std::string newPath, FileType newType )
{
	mName = filename;
	mPath = path;
	mType = type;
	mNewName = newName;
	mNewPath = newPath;
	mNewType = newType;
}

FileType FileInfo::Type()
{
	return( mType );
}

std::string FileInfo::Name()
{
	return( mName );
}

std::string FileInfo::Path()
{
	return( mPath );
}


std::string FileInfo::Fullpath()
{
	std::string tmp;

	tmp = mPath;
	tmp.append( "\\");
	tmp.append( mName );

	return( tmp );
}
FileType FileInfo::NewType()
{
	return( mNewType );
}

std::string FileInfo::NewName()
{
	return( mNewName );
}

std::string FileInfo::NewPath()
{
	return( mNewPath );
}

std::string FileInfo::NewFullpath()
{
	std::string tmp;

	tmp = mNewPath;
	tmp.append( "\\");
	tmp.append( mNewName );

	return( tmp );
}