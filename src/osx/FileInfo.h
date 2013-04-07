#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>

enum FileType { JPG, PNG, BMP, GIF, MATCHSRC };

class FileInfo{
public:
	FileInfo( std::string filename, std::string path, FileType type, std::string newName, std::string newPath, FileType newType );
	FileType Type();
	std::string Name();
	std::string Fullpath();
	std::string Path();
	FileType NewType();
	std::string NewName();
	std::string NewPath();
	std::string NewFullpath();

private:
	std::string mName;
	std::string mPath;
	FileType mType;
	std::string mNewName;
	std::string mNewPath;
	FileType mNewType;
};
#endif
