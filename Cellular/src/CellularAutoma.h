#pragma once
#include "ggl/Graph.hh"
#include "GridMap.h"
#include <queue>

class CellularAutoma
{
public:
	struct NodeInfo {
		int index;					// 该节点在ggl::Graph中的index 从0开始
		int preIndex;				// 前置节点的index
		int depth;					// 该节点相对于起点节点的深度
		std::string label;	// 该节点在ggl::Graph的label

		NodeInfo(int i, int pi, int d, const std::string& l = "n") :
			index(i), preIndex(pi), depth(d), label(l){};
	};

	typedef std::pair<int, int> NodePair;
private:
	typedef GridMap::Direction Direction;
private:
	const sgm::Graph_boost<ggl::Graph>& m_GI;
	GridMap m_gridMap;
	std::queue<NodePair> m_que;		// 广度优先遍历的缓冲 first:前置节点的index
	std::vector<NodeInfo> m_output;	// 广度优先遍历遍历顺序

	void Step();
	// 清空m_output
	void Reset();
	// 广度优先遍历ggl::Graph，将结果输出到m_output
	void GenOutput(const std::string& beginLabel = "e");
public:
	CellularAutoma(const sgm::Graph_boost<ggl::Graph>& gi);
	CellularAutoma() = delete;
	CellularAutoma(const CellularAutoma& other) = delete;
	CellularAutoma& operator = (const CellularAutoma& other) = delete;

	void Generate(const std::string& beginLabel = "e");
	const GridMap& GetGridMap() const;
	const sgm::Graph_boost<ggl::Graph>& GetGraphInterface() const;
};

std::ostream& operator << (std::ostream& out, const CellularAutoma::NodeInfo& node);
