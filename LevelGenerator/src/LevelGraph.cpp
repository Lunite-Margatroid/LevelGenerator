#include "LGException.h"
#include "LevelGraph.h"

namespace LG
{
	int LevelGraph::Expand(int newCapacity)
	{
		if (newCapacity <= m_nCapacity)
			return m_nCapacity;
		// init new array
		std::vector<int> newData(newCapacity * (newCapacity + 1));
		auto newIter = newData.begin();
		std::fill(newIter, newData.end(), 0);
		// copy from old array
		auto oldIter = m_Data.begin();
		// 1. copy edge info
		for (int i = 0; i < m_nCapacity; i++)
		{
			std::copy(oldIter, oldIter + m_nCapacity, newIter + newCapacity);
			oldIter += m_nCapacity;
			newIter += newCapacity;
		}
		// 2. copy node info
		newIter += newCapacity * (newCapacity - m_nCapacity);
		std::copy(oldIter, m_Data.end(), newIter);
		// 3. move
		m_Data = std::move(newData);
		m_nCapacity = newCapacity;
		return m_nCapacity;
	}
	void LevelGraph::Init()
	{
		// former "capacity * capacity" store edge info
		// latter "capacity" store node info
		m_Data.resize(m_nCapacity * (m_nCapacity + 1));
	}
	int& LevelGraph::GetNode(int node)
	{
		// TODO: insert return statement here
		LG_ASSERT_INFO(node >=0, Minus index!);
		LG_ASSERT_INFO(node < m_nCapacity, Node index over the max index.);
		return m_Data[m_nCapacity * m_nCapacity + node];
	}
	int& LevelGraph::GetEdge(int preNode, int postNode)
	{
		// TODO: insert return statement here
		LG_ASSERT_INFO(GetNode(preNode) != LG_NULLNODE && GetNode(postNode) != LG_NULLNODE, Edge with valid node.);
		return m_Data[preNode * m_nCapacity + postNode];
	}
	LevelGraph::LevelGraph()
		:m_nNode(0), m_nCapacity(LG_LEVELGRAPH_DEFAULT_CAPACITY)
		,m_Data()
	{
		Init();
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

	int LevelGraph::AddNode(int nodeInfo)
	{
		if (m_nNode < m_nCapacity)
		{
			int offset = m_nCapacity * m_nCapacity;
			int ret = 0;
			while (m_Data[offset + ret] != 0)
			{
				ret++;
			}
			m_Data[offset + ret] = nodeInfo;
			m_nNode += 1;
			return ret;
		}
		int oldCapacity = m_nCapacity;
		Expand(oldCapacity + (oldCapacity >> 1));
		GetNode(oldCapacity) = nodeInfo;
		m_nNode += 1;
		return oldCapacity;
	}

	int LevelGraph::AddNode()
	{
		return AddNode(LG_DEFAULT_NODE_TYPE);
	}

	int LevelGraph::AddEdge(int preNode, int postNode)
	{
		return AddEdge(preNode, postNode, LG_DEFAULT_EDGE_TYPE);
	}

	int LevelGraph::AddEdge(int preNode, int postNode, int edgeInfo)
	{
		int& edge = GetEdge(preNode, postNode);
		LG_ASSERT_INFO(edge == LG_NULLEDGE, The edge has been existing.);
		edge = edgeInfo;
		return 0;
	}

	int LevelGraph::SetEdge(int preNode, int postNode, int edgeInfo)
	{
		int& edge = GetEdge(preNode, postNode);
		edge = edgeInfo;
		return 0;
	}

	int LevelGraph::EraseNode(int node)
	{
		LG_ASSERT_INFO(node >=0 , Minus index.);
		LG_ASSERT_INFO(node > m_nCapacity, Index over the max index.);
		int& nodeInfo = GetNode(node);
		if (nodeInfo == LG_NULLNODE) return 1;

		// erase edges
		// 1. erase edges with the node as prenode
		auto iter = m_Data.begin() + m_nCapacity * node;
		std::fill(iter, iter + m_nCapacity, LG_NULLEDGE);
		// 2. erase edges with the node as postNode
		int preNode = 0;
		int count = 0;
		while (count < m_nNode && preNode < m_nCapacity)
		{
			int nodeInfo = GetNode(preNode);
			int& edge = GetEdge(preNode, node);
			preNode += 1;
			if (nodeInfo == LG_NULLNODE)
			{
				continue;
			}
			count += 1;
			edge = LG_NULLEDGE;
		}
		// 3. erase the node
		nodeInfo = LG_NULLNODE;
		m_nNode -= 1;

		return 0;
	}

	int LevelGraph::EraseEdge(int preNode, int postNode)
	{
		if (GetEdge(preNode, postNode) == LG_NULLEDGE)
			return 1;
		return SetEdge(preNode, postNode, LG_NULLEDGE);
	}

	void LevelGraph::PrintGraph(std::string& output) const
	{
		output.clear();
		std::ostringstream oss;
		oss << std::setw(2) << " ";
		for (int i = 0; i < m_nCapacity; i++)
		{
			oss << std::setw(2) << i;
		}
		oss << std::endl;
		auto iter = m_Data.cbegin();
		for (int i = 0; i < m_nCapacity; i++)
		{
			oss << std::setw(2) << i;
			for (int j = 0; j < m_nCapacity; j++)
			{
				oss << std::setw(2) << *iter;
				iter++;
			}
			oss << std::endl;
		}
		oss << std::endl;
		for (int i = 0; i < m_nCapacity; i++)
		{
			oss << std::setw(2) << *iter;
			iter++;
		}
		oss << std::endl;

		output = oss.str();
	}
}