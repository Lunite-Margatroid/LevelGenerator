#include "Common.h"
#include "Application.h"
#include "LevelGenerator.h"

Application::Application(int argn, char** argv)
	:m_bRun(true),
	m_nArg(argn),
	m_vArgs(argv)
{
}

Application::~Application()
{
}

bool Application::IsRun()
{
	return m_bRun;
}

int Application::Run()
{
	while (IsRun())
	{
		if (m_nArg < 4)
		{
			std::cout << "[error] argument is not enough\n";
			break;
		}
		std::cout << "Executable: " << m_vArgs[0] << std::endl;
		std::cout << "Input Graph: " << m_vArgs[1] << std::endl;
		std::cout << "Input Rule: " << m_vArgs[2] << std::endl;
		std::cout << "Output File: " << m_vArgs[3] << std::endl;
		LevelGenerator lg;
		lg.Init(m_vArgs[1], m_vArgs[2]);
		lg.SetBeginNodeLabel("e");
		if (m_nArg >= 5)
		{
			int seed = atoi(m_vArgs[4]);
			std::cout << "Rand Seed: " << seed << std::endl;
			lg.SetRandSeed(seed);
		}
		std::cout << "Step: " << lg.Step(30) << std::endl; 
		lg.Output(m_vArgs[3]);
		lg.OutputGridAndLevel(std::cout, m_vArgs[3]);

		m_bRun = false;
	}
	return 0;
}
