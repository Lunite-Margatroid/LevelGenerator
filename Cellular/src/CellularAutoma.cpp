#include "CellularAutoma.h"



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
			m_output.push(NodeInfo(curNode, curPreNode, nDepth, beginLabel));
			// 访问相邻节点
			for (auto iter = m_GI.getOutEdgesBegin(curNode); iter != m_GI.getOutEdgesEnd(curNode); iter++)
			{
				// 获得后置节点
				int postNode = iter->getToIndex();
				if (!flag[postNode])
				{// 该节点没有访问过
					// 入队
					m_que.push(std::make_pair(curNode, postNode));
					flag[postNode = true];
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
}



