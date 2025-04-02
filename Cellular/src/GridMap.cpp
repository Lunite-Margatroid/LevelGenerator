#include "GridMap.h"

GridMap::NodeDesc::NodeDesc()
	: id(-1), x(0), y(0), con(0x0)
{
}

GridMap::NodeDesc::NodeDesc(NodeID iid, int xx, int yy, unsigned int conn)
	:id(iid), x(xx), y(yy), con(conn)
{
}

void GridMap::NodeDesc::SetAccess(Direction dir)
{
	con.set(static_cast<unsigned int>(dir));
}

void GridMap::NodeDesc::ResetAccess(Direction dir)
{
	con.reset(static_cast<unsigned int>(dir));
}

bool GridMap::NodeDesc::GetAccess(Direction dir)
{
	return con.test(static_cast<unsigned int>(dir));
}

GridMap::NodeDesc& GridMap::GetNodeDesc(NodeIndex index)
{
	return m_Data[static_cast<int>(index)];
}

const GridMap::NodeDesc& GridMap::GetNodeDesc(NodeIndex index) const
{
	return m_Data[static_cast<int>(index)];
}

GridMap::NodeID GridMap::GetNodeID(int x, int y) const
{
	return GetNodeDesc(x, y)->id;
}

void GridMap::InsertNode(int x, int y, GridMap::NodeID id)
{
	InsertNode(NodeDesc(id, x, y, 0x0));
}

void GridMap::InsertNode(const NodeDesc& nodeDesc)
{
	if (NodeExist(nodeDesc.x, nodeDesc.y))
		return;
	NodeIndex index = m_Data.size();
	m_Data.push_back(nodeDesc);
	// TODO : Insert the Node
}

GridMap::NodeDesc* GridMap::GetNodeDesc(int x, int y)
{
	// grid为空
	if (m_xLinkedListList.size() == 0) return nullptr;

	// 从x链表开始搜索
	auto iterListList = m_xLinkedListList.begin();
	for (; iterListList != m_xLinkedListList.end(); iterListList++)
	{
		if (iterListList->size() > 0)
		{
			auto iterList = iterListList->begin();
			// 如果x不在包含区域内
			NodeIndex tIndex = *(iterList);
			if(GetNodeDesc(tIndex).x > x)
				return nullptr;
			// 找到x
			if (GetNodeDesc(tIndex).x == x)
			{
				for (; iterList != iterListList->end(); iterList++)
				{
					if (GetNodeDesc(*iterList).y > y)
						return nullptr;
					if (GetNodeDesc(*iterList).y == y)
						return &GetNodeDesc(*iterList);
				}
			}
		}
	}

	// 没有找到
	return nullptr;
}

const GridMap::NodeDesc* GridMap::GetNodeDesc(int x, int y) const
{
	// grid为空
	if (m_xLinkedListList.size() == 0) return nullptr;

	// 从x链表开始搜索
	auto iterListList = m_xLinkedListList.begin();
	for (; iterListList != m_xLinkedListList.end(); iterListList++)
	{
		if (iterListList->size() > 0)
		{
			auto iterList = iterListList->begin();
			// 如果x不在包含区域内
			NodeIndex tIndex = *(iterList);
			if (GetNodeDesc(tIndex).x > x)
				return nullptr;
			// 找到x
			if (GetNodeDesc(tIndex).x == x)
			{
				for (; iterList != iterListList->end(); iterList++)
				{
					if (GetNodeDesc(*iterList).y > y)
						return nullptr;
					if (GetNodeDesc(*iterList).y == y)
						return static_cast<const GridMap::NodeDesc*>(&GetNodeDesc(*iterList));
				}
			}
		}
	}

	// 没有找到
	return nullptr;
}

bool GridMap::NodeExist(int x, int y) const
{
	return GetNodeDesc(x, y) != nullptr;
}
