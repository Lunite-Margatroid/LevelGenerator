#pragma once
#include "ggl/Graph.hh"
#include "GridMap.h"
#include <queue>

class CellularAutoma
{
public:
	struct NodeInfo {
		int index;					// �ýڵ���ggl::Graph�е�index ��0��ʼ
		int preIndex;				// ǰ�ýڵ��index
		int depth;					// �ýڵ���������ڵ�����
		std::string label;	// �ýڵ���ggl::Graph��label

		NodeInfo(int i, int pi, int d, const std::string& l = "n") :
			index(i), preIndex(pi), depth(d), label(l){};
	};

	typedef std::pair<int, int> NodePair;
private:
	typedef GridMap::Direction Direction;
private:
	const sgm::Graph_boost<ggl::Graph>& m_GI;
	GridMap m_gridMap;
	std::queue<NodePair> m_que;		// ������ȱ����Ļ��� first:ǰ�ýڵ��index
	std::vector<NodeInfo> m_output;	// ������ȱ�������˳��

	void Step();
	// ���m_output
	void Reset();
	// ������ȱ���ggl::Graph������������m_output
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
