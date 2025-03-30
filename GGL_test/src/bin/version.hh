#ifndef VERSION_HH
#define VERSION_HH


#define PACKAGE_NAME 0
#define PACKAGE_VERSION 0
#define PACKAGE_URL 0
#include <iostream>

void
giveVersion()
{
	std::cout	<<"\n " <<PACKAGE_NAME <<" package version " <<PACKAGE_VERSION
				<<"\n"
				<<"\n " <<PACKAGE_URL
				<<"\n"
				<<std::endl;
}

#endif /*VERSION_HH*/
