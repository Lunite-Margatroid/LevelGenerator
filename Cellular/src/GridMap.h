#pragma once
#include <list>
#include <bitset>
#include <vector>
#include <iomanip>
#include <map>

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

	typedef int NodeIndex;		// 节点信息在缓存中(m_Data)的偏移量
	typedef int NodeID;			// 节点的id

	struct NodeDesc
	{
		NodeID id;				// 节点的id 唯一
		int x, y;				// 节点的坐标
		std::bitset<4> con;		// 节点在网格中对四领域节点的连通性
		NodeDesc();
		NodeDesc(NodeID iid, int xx, int yy, unsigned int conn);
		void SetAccess(Direction dir);		// 将对应方向的连通性设置为1
		void ResetAccess(Direction dir);	// 将对应方向的连通性设置为0
		bool GetAccess(Direction dir);		// 获得对应方向的连通性
	};

	std::vector<NodeDesc> m_Data;
	std::map<NodeID, NodeIndex> m_mapId2Index;

	std::list<std::list<NodeIndex>> m_xLinkedListList;
	std::list<std::list<NodeIndex>> m_yLinkedListList;

public:
	GridMap() = default;
	GridMap(const GridMap& other) = delete;
	GridMap& operator = (const GridMap& other) = delete;
	~GridMap() = default;

	NodeID GetNodeID(int x, int y) const;

	// 如果指定坐标已存在节点  不进行任何操作
	NodeDesc* InsertNode(int x, int y, NodeID id);
	// 如果指定坐标已存在节点  不进行任何操作
	NodeDesc* InsertNode(const NodeDesc& nodeDesc);

	NodeDesc* GetNodeDesc(int x, int y);
	const NodeDesc* GetNodeDesc(int x, int y) const;
	NodeDesc* GetNodeDesc(NodeID id);
	const NodeDesc* GetNodeDesc(NodeID id) const;
	bool NodeExist(int x, int y)const;

	void PrintNode(std::ostream& outStream)const;
	void PrintASCII(std::ostream& outStream, int charWidth = 1) const;
	void PrintLabel(std::ostream& outStream, const std::vector<std::string>& labelMap, int charWidth = 1) const;

	int GetXMin() const;
	int GetYMin() const;
	int GetXMax() const;
	int GetYMax() const;

	void Clear();

	const std::vector<NodeDesc>& GetData() const;
};