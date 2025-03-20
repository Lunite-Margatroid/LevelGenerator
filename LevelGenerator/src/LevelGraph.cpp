#include "LevelGraph.h"

namespace LG
{

	LevelGraph::LevelGraph()
		:m_nNode(0), m_nCapacity(LEVELGRAPH_DEFAULT_CAPACITY)
	{
	}

	LevelGraph::~LevelGraph()
	{
	}

	int LevelGraph::GetNodeCount() const
	{
		return m_nNode;
	}

	int LevelGraph::GetCapacity() const
	{
		return m_nCapacity;
	}

	extern LG_DLL_API int add(int a, int b)
	{
		return a + b;
	}
}