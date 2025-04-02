#pragma once
#include "ggl/Graph.hh"

class CellularAutoma
{
private:
	const ggl::Graph* m_pInputGraph;
	void Step();
public:
	CellularAutoma(const ggl::Graph* pGraph);
	CellularAutoma();
	CellularAutoma(const CellularAutoma& other) = delete;
	CellularAutoma& operator = (const CellularAutoma& other) = delete;

	void SetInputGraph(const ggl::Graph* pGraph);
	void Generate();
};