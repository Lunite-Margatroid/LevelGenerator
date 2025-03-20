#pragma once
class Application
{
private:
	bool m_bRun;
public:
	Application();
	~Application();

	bool IsRun();
	int Run();
};