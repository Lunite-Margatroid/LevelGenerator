#include "Common.h"
#include "Application.h"

int main(int argc, char* argv[])
{
	int appRet = 0;
	try
	{
		Application app;
		appRet = app.Run();
	}
	catch (const LG::LGException& e)
	{
		std::cout << e.what() << std::endl;
	}

	return appRet;
}