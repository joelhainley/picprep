
picprep : args.o param.o Logger.o ProcessDefault.o ProcessScaleAbsolute.o ProcessFormat.o ProcessScaleRatio.o ProcessBPP.o FileList.o FileInfo.o
	g++ -I ../../FreeImage/Dist -o ../test/picprep picprep.cpp args.o param.o Logger.o ProcessDefault.o ProcessFormat.o ProcessScaleAbsolute.o ProcessScaleRatio.o ProcessBPP.o FileInfo.o FileList.o /Users/jhainley/work/FreeImage/Dist/libfreeimage.a


ProcessDefault.o : ProcessDefault.cpp ProcessDefault.h
	g++ -c ProcessDefault.cpp

ProcessScaleAbsolute.o : ProcessScaleAbsolute.cpp ProcessScaleAbsolute.h
	g++ -I ../../FreeImage/Dist -c ProcessScaleAbsolute.cpp

ProcessScaleRatio.o : ProcessScaleRatio.cpp ProcessScaleRatio.h
	g++ -I ../../FreeImage/Dist -c ProcessScaleRatio.cpp

ProcessFormat.o : ProcessFormat.cpp ProcessFormat.h
	g++ -I ../../FreeImage/Dist -c ProcessFormat.cpp
		
ProcessBPP.o : ProcessBPP.cpp ProcessBPP.h
	g++ -I ../../FreeImage/Dist -c ProcessBPP.cpp

FileList.o : osx/FileList.cpp osx/FileList.h 
	g++ -c osx/FileList.cpp

FileInfo.o : 
	g++ -c osx/FileInfo.cpp 

Logger.o : Logger.cpp Logger.h
	g++ -c Logger.cpp


args.o : args.cpp args.h
	g++ -c args.cpp
	
