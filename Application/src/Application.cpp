#include "Common.h"
#include "Application.h"

Application::Application()
	:m_bRun(true)
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
		LG::LevelGraph graph;

		std::cout << "Count: " << graph.GetNodeCount() << std::endl;
		std::cout << "Capacity: " << graph.GetCapacity() << std::endl;
		std::cout << "Count + Capacity = " << LG::add(graph.GetNodeCount(), graph.GetCapacity()) << std::endl;
		m_bRun = false;
	}
	return 0;
}
