#pragma once
#include "ggl/Graph.hh"
#include "GridMap.h"
#include <queue>

class CellularAutoma
{
private:
	const sgm::Graph_boost<ggl::Graph>& m_GI;
	GridMap m_gridMap;
	std::queue<int> m_que;


	void Step();
public:
	CellularAutoma(const sgm::Graph_boost<ggl::Graph>& gi);
	CellularAutoma() = delete;
	CellularAutoma(const CellularAutoma& other) = delete;
	CellularAutoma& operator = (const CellularAutoma& other) = delete;

	void Generate();
};