#ifndef FILELIST_H
#define FILELIST_H

#include <vector>
#include <io.h>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <direct.h>
#include "FileInfo.h"




class FileList{
public:
	FileList(std::string src, std::string dest, std::string append);
	int Count();
	FileInfo* GetFileInfo(int index);

private:
	std::vector<FileInfo*> mFiles;
	struct _finddata_t	mFile;					// contains the current result from findfile
	bool		mFindCalled;			// holds a value indicating whether the find function
												// has already been called once
    long		mFileHandle;
	bool		FileIsDir(_finddata_t* pFile);			// private utility function
	std::string GetPath( std::string pattern );
	std::string GetExtension( std::string filename );
	std::string GetNameLessExt( std::string filename );
	bool		GetCWD(std::string& buffer);
	FileInfo*	GetInfo( _finddata_t* pFile, std::string pSrc, std::string pDest, std::string pAppend);
};
#endif