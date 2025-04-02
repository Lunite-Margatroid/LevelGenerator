#pragma once
class Application
{
private:
	bool m_bRun;
	int m_nArg;
	char** m_vArgs;
public:
	Application(int argn, char** argv);
	~Application();

	bool IsRun();
	int Run();
};