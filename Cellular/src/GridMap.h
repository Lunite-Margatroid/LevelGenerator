#pragma once
#include <list>
#include <bitset>
#include <vector>
class GridMap
{
public:
	enum class Direction
	{
		minus_x = 0,
		plus_x = 1,
		minus_y = 2,
		plus_y = 3
	};

	typedef int NodeIndex;
	typedef int NodeID;

	struct NodeDesc
	{
		NodeID id;
		int x, y;
		std::bitset<4> con;
		NodeDesc();
		NodeDesc(NodeID iid, int xx, int yy, unsigned int conn);
		void SetAccess(Direction dir);
		void ResetAccess(Direction dir);
		bool GetAccess(Direction dir);
	};

	std::vector<NodeDesc> m_Data;
	

	std::list<std::list<NodeIndex>> m_xLinkedListList;
	std::list<std::list<NodeIndex>> m_yLinkedListList;
	
	NodeDesc& GetNodeDesc(NodeIndex index);
	const NodeDesc& GetNodeDesc(NodeIndex) const;

public:
	NodeID GetNodeID(int x, int y) const;
	void InsertNode(int x, int y, NodeID id);
	void InsertNode(const NodeDesc& nodeDesc);

	NodeDesc* GetNodeDesc(int x, int y);
	const NodeDesc* GetNodeDesc(int x, int y) const;
	bool NodeExist(int x, int y)const;
};