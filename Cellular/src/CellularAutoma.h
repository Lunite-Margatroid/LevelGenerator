#pragma once
#include "ggl/Graph.hh"
#include "GridMap.h"
#include <queue>

class CellularAutoma
{
private:
	struct NodeInfo {
		int index;					// �ýڵ���ggl::Graph�е�index
		int postIndex;				// ǰ�ýڵ��index
		int depth;					// �ýڵ���������ڵ�����
		const std::string& label;	// �ýڵ���ggl::Graph��label

		NodeInfo(int i, int pi, int d, const std::string& l = "n") :
			index(i), postIndex(pi), depth(d), label(l){};
	};

	typedef std::pair<int, int> NodePair;

private:
	const sgm::Graph_boost<ggl::Graph>& m_GI;
	GridMap m_gridMap;
	std::queue<NodePair> m_que;
	std::queue<NodeInfo> m_output;

	void Step();
public:
	CellularAutoma(const sgm::Graph_boost<ggl::Graph>& gi);
	CellularAutoma() = delete;
	CellularAutoma(const CellularAutoma& other) = delete;
	CellularAutoma& operator = (const CellularAutoma& other) = delete;

	void Generate(const std::string& beginLabel = "e");
};