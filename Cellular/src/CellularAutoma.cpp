#include "CellularAutoma.h"



std::ostream& operator<<(std::ostream& out, const CellularAutoma::NodeInfo& node)
{
		return out << "Index: " << node.index \
			<< "    Pre Node: " << node.preIndex \
			<< "    Depth: " << node.depth\
			<< "    Label: " << node.label;
}

void CellularAutoma::Step()
{
}

void CellularAutoma::GenOutput(const std::string& beginLabel /*= "e"*/)
{
	// 获得顶点数量
	int nNode = m_GI.getNodeNumber();

	// 初始化访问标签
	std::vector<bool> flag;
	flag.resize(nNode);
	std::fill(flag.begin(), flag.end(), false);

	// 初始化缓冲队列
	while(!m_que.empty())
		m_que.pop();

	// 获取初始节点
	int beginIndex = 0;
	for (int i = 0; i < nNode; i++)
	{// 遍历节点 找到起始标签 如果没有 使用0号节点为起始节点
		if (m_GI.getNodeLabel(i) == beginLabel)
		{
			beginIndex = i;
			break;
		}
	}
	// 放入初始节点
	m_que.push(std::make_pair(-1, beginIndex));	// 初始节点没有前置节点 置为-1
	flag[beginIndex] = true;
	// 放入深度标签节点
	m_que.push(std::make_pair(-1, -1));
	int nDepth = 0;

	// 遍历
	while (!m_que.empty())
	{
		// 获得当前节点及其前置节点
		int curPreNode = m_que.front().first;
		int curNode = m_que.front().second;
		m_que.pop();

		if (curNode >= 0)
		{// 该节点不是深度标志
			m_output.emplace_back(NodeInfo(curNode, curPreNode, nDepth, m_GI.getNodeLabel(curNode)));
			// 访问相邻节点
			for (auto iter = m_GI.getOutEdgesBegin(curNode); iter != m_GI.getOutEdgesEnd(curNode); iter++)
			{
				// 获得后置节点
				int postNode = iter->getToIndex();
				if (!flag[postNode])
				{// 该节点没有访问过
					// 入队
					m_que.push(std::make_pair(curNode, postNode));
					flag[postNode] = true;
				}
			}
		}
		else
		{// 该节点是深度标志
			nDepth++;	// 深度++
			if (!m_que.empty())
			{// 如果队列不是空的 加入新的深度标志
				m_que.push(std::make_pair(-1, -1));
			}
		}
	}
}

CellularAutoma::CellularAutoma(const sgm::Graph_boost<ggl::Graph>& gi)
:m_GI(gi)
{
}

void CellularAutoma::Generate(const std::string& beginLabel)
{
	GenOutput(beginLabel);
	int lastX = 0, lastY = 0;
	std::vector<Direction> tempContainer;
	tempContainer.reserve(4);
	int xx[] = {-1, 1, 0, 0};
	int yy[] = {0, 0, -1, 1};
	Direction directions[] = {Direction::minus_x, Direction::plus_x, Direction::minus_y, Direction::plus_y};
	Direction oppositDir[] = {Direction::plus_x, Direction::minus_x, Direction::plus_y, Direction::minus_y };
	auto Check4Neighbor = [&](int x, int y) -> void {
		tempContainer.clear();
		for (int i = 0; i < 4; i++)
		{
			// check the 4 neighbors
			if (!m_gridMap.NodeExist(x + xx[i], y + yy[i]))
			{
				tempContainer.push_back(directions[i]);
			}
		}
	};

	auto RandomWalkExtend = [&](const NodeInfo& node, int preIdd) -> int {
		const GridMap::NodeDesc* pLastNodeDesc = m_gridMap.GetNodeDesc(lastX, lastY);
		GridMap::NodeDesc* pPreNodeDesc = m_gridMap.GetNodeDesc(preIdd);
		int preX = pPreNodeDesc->x;
		int preY = pPreNodeDesc->y;
		// get all accessiable direction
		Check4Neighbor(preX, preY);
		int nDir = tempContainer.size();
		if (nDir > 0)
		{// Extendable grid exists
			// TODO: Use better extending methord
			// Randomly selet the direction
			Direction dir = tempContainer[rand() % nDir];
			GridMap::NodeDesc* curNode = m_gridMap.InsertNode(preX + xx[static_cast<int>(dir)], preY + yy[static_cast<int>(dir)], node.index);
			assert(curNode);
			pPreNodeDesc->SetAccess(dir);
			curNode->SetAccess(oppositDir[static_cast<int>(dir)]);
			lastX = curNode->x;
			lastY = curNode->y;
		}
		return nDir;
	};

	auto GetPreNodeId = [&](int nodeId)->int {
		if (nodeId < 0) return -1;
		std::vector<NodeInfo>::const_iterator iterNode = std::find_if(m_output.begin(), m_output.end(),
			[=](const NodeInfo& node) ->bool { return node.index == nodeId; });
		return (*iterNode).preIndex;
	};

	for (const NodeInfo& node : m_output)
	{
		std::cout << node << std::endl;
		int preId = node.preIndex;
		if (preId == -1)
		{
			// insert the first node
			m_gridMap.InsertNode(0, 0, node.index);
		}
		else
		{
			int nDir = RandomWalkExtend(node, preId);
			// Extendable grid doesnt exist
			// find extendable grid via prenode of prenode
			while (nDir == 0)
			{
				preId = GetPreNodeId(preId);
				if (preId == -1)
					break;	// all prenodes cant extend

				nDir = RandomWalkExtend(node, preId);
			}
			if (nDir == 0)
			{// all preodes cant extend
				// TODO: Solute this condition
			}
		}
	}

	std::vector<std::string> labMap;
	int nNodeCount = m_GI.getNodeNumber();
	for (int i = 0; i < nNodeCount; i++)
	{
		labMap.emplace_back(m_GI.getNodeLabel(i));
	}
	m_gridMap.PrintLabel(std::cout, labMap);
}



