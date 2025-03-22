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
		srand(1);
		for (int i = 0; i < 10; i++)
		{
			graph.AddNode(rand() % 9 + 1);
		}

		for (int j = 0; j < 10; j++)
		{
			graph.SetEdge(rand() % 10, rand() % 10, rand() % 3 + 1);
		}

		std::cout << "Count: " << graph.GetNodeCount() << std::endl;
		std::cout << "Capacity: " << graph.GetCapacity() << std::endl;

		std::string output;
		graph.PrintGraph(output);
		std::cout << output << std::endl;

		m_bRun = false;
	}
	return 0;
}
