#include "ProcessDefault.h"
#include <iostream>
ProcessDefault::ProcessDefault(Process* successor)
{
	mSuccessor = successor;
}

void ProcessDefault::proc(Args* pArgs)
{
	showUsage();
}


void ProcessDefault::showUsage()
{
	std::cout << "\n";
	std::cout << "picprep [1.1.0] - a command line image manipulation utility: \n";
	std::cout << "-------------------------------------------------------------------------\n";
	std::cout << "\n";

	std::cout << "NOTE : \n";
	
	#ifdef osx
		std::cout << " - ALL PARAMETER VALUES MUST BE WRAPPED IN SINGLE OR DOUBLE QUOTES\n\t(ie : append='-xps' )\n";
	#endif

	std::cout << " - ALL COMMANDS ARE CASE SENSITIVE!!\n\n";
	
	std::cout << "scale by percentage [p] \n\t : scales images by the specified percentage\n\n";

	std::cout << "scale absolute [a] \n\t : scales images to specified pixel size\n\n";

	std::cout << "change image format [f] \n\t : "
				 "chages the file format that the image is stored in\n\n";

	std::cout << "change bit depth [b] \n\t : "
				 "changes the bit depth of the image\n\n";

	std::cout << "-------------------------------------------------------------------------\n";

	std::cout << "brought to you by the minds @ myndkryme laboratories\n"
				 "website : www.myndkryme.com/product-picprep.html\n";

	std::cout << "=========================================================================\n";
}

