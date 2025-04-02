#include "CellularAutoma.h"

CellularAutoma::CellularAutoma(const ggl::Graph* pGraph)
	:m_pInputGraph(pGraph)
{
}

CellularAutoma::CellularAutoma()
	:m_pInputGraph(nullptr)
{
}

void CellularAutoma::SetInputGraph(const ggl::Graph* pGraph)
{
	m_pInputGraph = pGraph;
}
