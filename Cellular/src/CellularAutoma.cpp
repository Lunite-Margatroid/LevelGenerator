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
	// ��ö�������
	int nNode = m_GI.getNodeNumber();

	// ��ʼ�����ʱ�ǩ
	std::vector<bool> flag;
	flag.resize(nNode);
	std::fill(flag.begin(), flag.end(), false);

	// ��ʼ���������
	while(!m_que.empty())
		m_que.pop();

	// ��ȡ��ʼ�ڵ�
	int beginIndex = 0;
	for (int i = 0; i < nNode; i++)
	{// �����ڵ� �ҵ���ʼ��ǩ ���û�� ʹ��0�Žڵ�Ϊ��ʼ�ڵ�
		if (m_GI.getNodeLabel(i) == beginLabel)
		{
			beginIndex = i;
			break;
		}
	}
	// �����ʼ�ڵ�
	m_que.push(std::make_pair(-1, beginIndex));	// ��ʼ�ڵ�û��ǰ�ýڵ� ��Ϊ-1
	flag[beginIndex] = true;
	// ������ȱ�ǩ�ڵ�
	m_que.push(std::make_pair(-1, -1));
	int nDepth = 0;

	// ����
	while (!m_que.empty())
	{
		// ��õ�ǰ�ڵ㼰��ǰ�ýڵ�
		int curPreNode = m_que.front().first;
		int curNode = m_que.front().second;
		m_que.pop();

		if (curNode >= 0)
		{// �ýڵ㲻����ȱ�־
			m_output.emplace_back(NodeInfo(curNode, curPreNode, nDepth, m_GI.getNodeLabel(curNode)));
			// �������ڽڵ�
			for (auto iter = m_GI.getOutEdgesBegin(curNode); iter != m_GI.getOutEdgesEnd(curNode); iter++)
			{
				// ��ú��ýڵ�
				int postNode = iter->getToIndex();
				if (!flag[postNode])
				{// �ýڵ�û�з��ʹ�
					// ���
					m_que.push(std::make_pair(curNode, postNode));
					flag[postNode] = true;
				}
			}
		}
		else
		{// �ýڵ�����ȱ�־
			nDepth++;	// ���++
			if (!m_que.empty())
			{// ������в��ǿյ� �����µ���ȱ�־
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



