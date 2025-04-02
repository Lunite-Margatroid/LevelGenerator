#include "Common.h"
#include "Application.h"

int main(int argc, char* argv[])
{
	int appRet = 0;
	try
	{
		Application app(argc, argv);
		appRet = app.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return appRet;
}