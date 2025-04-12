#pragma once
#include <list>
#include <bitset>
#include <vector>
#include <iomanip>

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

	typedef int NodeIndex;		// �ڵ���Ϣ�ڻ�����(m_Data)��ƫ����
	typedef int NodeID;			// �ڵ��id

	struct NodeDesc
	{
		NodeID id;				// �ڵ��id Ψһ
		int x, y;				// �ڵ������
		std::bitset<4> con;		// �ڵ��������ж�������ڵ����ͨ��
		NodeDesc();
		NodeDesc(NodeID iid, int xx, int yy, unsigned int conn);
		void SetAccess(Direction dir);		// ����Ӧ�������ͨ������Ϊ1
		void ResetAccess(Direction dir);	// ����Ӧ�������ͨ������Ϊ0
		bool GetAccess(Direction dir);		// ��ö�Ӧ�������ͨ��
	};

	std::vector<NodeDesc> m_Data;
	

	std::list<std::list<NodeIndex>> m_xLinkedListList;
	std::list<std::list<NodeIndex>> m_yLinkedListList;
	
	NodeDesc& GetNodeDesc(NodeIndex index);
	const NodeDesc& GetNodeDesc(NodeIndex) const;

public:
	GridMap() = default;
	GridMap(const GridMap& other) = delete;
	GridMap& operator = (const GridMap& other) = delete;
	~GridMap() = default;

	NodeID GetNodeID(int x, int y) const;

	// ���ָ�������Ѵ��ڽڵ�  �������κβ���
	void InsertNode(int x, int y, NodeID id);
	// ���ָ�������Ѵ��ڽڵ�  �������κβ���
	void InsertNode(const NodeDesc& nodeDesc);

	NodeDesc* GetNodeDesc(int x, int y);
	const NodeDesc* GetNodeDesc(int x, int y) const;
	bool NodeExist(int x, int y)const;

	void PrintNode(std::ostream& outStream)const;
	void PrintASCII(std::ostream& outStream, int charWidth = 1) const;

	void Clear();
};