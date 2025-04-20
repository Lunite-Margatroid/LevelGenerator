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

GridMap::NodeID GridMap::GetNodeID(int x, int y) const
{
	return GetNodeDesc(x, y)->id;
}

GridMap::NodeDesc* GridMap::InsertNode(int x, int y, GridMap::NodeID id)
{
	return InsertNode(NodeDesc(id, x, y, 0x0));
}

GridMap::NodeDesc* GridMap::InsertNode(const NodeDesc& nodeDesc)
{
	if (NodeExist(nodeDesc.x, nodeDesc.y))
		return nullptr;
	NodeIndex index = m_Data.size();
	m_Data.push_back(nodeDesc);
	m_mapId2Index[nodeDesc.id] = index;
	// 如果表中没有节点
	if (m_xLinkedListList.empty())
	{
		std::list<NodeIndex> xList;
		std::list<NodeIndex> yList;
		xList.push_back(index);
		yList.push_back(index);
		m_xLinkedListList.emplace_back(std::move(xList));
		m_yLinkedListList.emplace_back(std::move(yList));
		return &m_Data.back();
	}

	// ============= 插入xList ================
	auto xMinList = m_xLinkedListList.front();
	auto xMaxList = m_xLinkedListList.back();
	int minX = m_Data[xMinList.front()].x;
	int maxX = m_Data[xMaxList.front()].x;
	if (minX > nodeDesc.x)
	{// 如果不在范围内 在下界之外
		while (minX != nodeDesc.x)
		{
			m_xLinkedListList.emplace_front(std::list<NodeIndex>());
			minX--;
		}
		std::list<NodeIndex>& xNewMinList = m_xLinkedListList.front();
		xNewMinList.push_back(index);

	}
	else if (maxX < nodeDesc.x)
	{// 如果在上界之外
		while (maxX != nodeDesc.x)
		{
			m_xLinkedListList.emplace_back(std::list<NodeIndex>());
			maxX++;
		}
		std::list<NodeIndex>& xNewMaxList = m_xLinkedListList.back();
		xNewMaxList.push_back(index);
	}
	else
	{// 如果在范围内
		auto iterListList = m_xLinkedListList.begin();
		while (minX < nodeDesc.x)
		{
			minX++;
			iterListList++;
		}
		auto iterList = iterListList->begin();

		while (iterList != iterListList->end() && m_Data[*iterList].y < nodeDesc.y)
		{
			iterList++;
		}
		iterListList->insert(iterList, index);
	}
	// ============= 插入xList / end ==============

	// ============= 插入yList ================
	auto yMinList = m_yLinkedListList.front();
	auto yMaxList = m_yLinkedListList.back();
	int minY = m_Data[yMinList.front()].y;
	int maxY = m_Data[yMaxList.front()].y;
	if (minY > nodeDesc.y)
	{// 如果不在范围内 在下界之外
		while (minY != nodeDesc.y)
		{
			m_yLinkedListList.emplace_front(std::list<NodeIndex>());
			minY--;
		}
		std::list<NodeIndex>& yNewMinList = m_yLinkedListList.front();
		yNewMinList.push_back(index);

	}
	else if (maxY < nodeDesc.y)
	{// 如果在上界之外
		while (maxY != nodeDesc.y)
		{
			m_yLinkedListList.emplace_back(std::list<NodeIndex>());
			maxY++;
		}
		std::list<NodeIndex>& yNewMaxList = m_yLinkedListList.back();
		yNewMaxList.push_back(index);
	}
	else
	{// 如果在范围内
		auto iterListList = m_yLinkedListList.begin();
		while (minY < nodeDesc.y)
		{
			iterListList++;
			minY++;
		}
		auto iterList = iterListList->begin();

		while (iterList != iterListList->end() && m_Data[*iterList].x < nodeDesc.x)
		{
			iterList++;
		}
		iterListList->insert(iterList, index);
	}
	// ============= 插入yList / end ==============

	return &m_Data.back();
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
			if(m_Data[tIndex].x > x)
				return nullptr;
			// 找到x
			if (m_Data[tIndex].x == x)
			{
				for (; iterList != iterListList->end(); iterList++)
				{
					if (m_Data[*iterList].y > y)
						return nullptr;
					if (m_Data[*iterList].y == y)
						return &m_Data[*iterList];
				}
			}
		}
	}

	// 没有找到
	return nullptr;
}

const GridMap::NodeDesc* GridMap::GetNodeDesc(int x, int y) const
{
	// 从x链表开始搜索
	auto iterListList = m_xLinkedListList.begin();
	for (; iterListList != m_xLinkedListList.end(); iterListList++)
	{
		if (iterListList->size() > 0)
		{
			auto iterList = iterListList->begin();
			// 如果x不在包含区域内
			NodeIndex tIndex = *(iterList);
			if (m_Data[tIndex].x > x)
				return nullptr;
			// 找到x
			if (m_Data[tIndex].x == x)
			{
				for (; iterList != iterListList->end(); iterList++)
				{
					if (m_Data[*iterList].y > y)
						return nullptr;
					if (m_Data[*iterList].y == y)
						return static_cast<const GridMap::NodeDesc*>(&m_Data[*iterList]);
				}
			}
		}
	}

	// 没有找到
	return nullptr;
}

GridMap::NodeDesc* GridMap::GetNodeDesc(GridMap::NodeID id)
{
	return &m_Data[m_mapId2Index[id]];
}

const GridMap::NodeDesc* GridMap::GetNodeDesc(GridMap::NodeID id) const
{
	return &m_Data[static_cast<int>((*m_mapId2Index.find(id)).second)];
}

bool GridMap::NodeExist(int x, int y) const
{
	return GetNodeDesc(x, y) != nullptr;
}

void GridMap::PrintNode(std::ostream& outStream) const
{
	int minX, maxX, minY, maxY;
	minX = m_Data[m_xLinkedListList.front().front()].x;
	maxX = m_Data[m_xLinkedListList.back().back()].x;
	minY = m_Data[m_yLinkedListList.front().front()].y;
	maxY = m_Data[m_yLinkedListList.back().back()].y;

	int wid = 1;
	int t = std::max(std::max(abs(minX), abs(maxX)), std::max(abs(minY), abs(maxY)));
	while (t > 0)
	{
		wid++;
		t /= 10;
	}

	for (auto xList : m_xLinkedListList)
	{
		for (NodeIndex index : xList)
		{
			const NodeDesc& desc = m_Data[index];
			outStream << "ID: " << std::setw(wid) << desc.id << "   Coord: (" << std::setw(wid) << desc.x << ", " << std::setw(wid) << desc.y << ")\n";
		}
	}

}

void GridMap::PrintASCII(std::ostream& outStream, int charWidth) const
{
	int minX, maxX, minY, maxY;
	minX = m_Data[m_xLinkedListList.front().front()].x;
	maxX = m_Data[m_xLinkedListList.back().back()].x;
	minY = m_Data[m_yLinkedListList.front().front()].y;
	maxY = m_Data[m_yLinkedListList.back().back()].y;

	int wid = 1;
	int t = std::max(std::max(abs(minX), abs(maxX)), std::max(abs(minY), abs(maxY)));
	while (t > 0)
	{
		wid++;
		t /= 10;
	}
	wid = std::max(wid, charWidth + 1);

	int curX, curY;
	curY = maxY;
	curX = minX;
	std::string edgeTop(wid * (maxX - minX + 1) , '-');
	outStream << std::setw(wid) << "Y" << '+' <<edgeTop << '+'<< std::endl;
	for (auto iterList = m_yLinkedListList.rbegin();iterList != m_yLinkedListList.rend();iterList ++)
	{

		curX = minX;
		outStream<< std::setw(wid) << curY << '|';
		for (auto iter = iterList->begin();iter != iterList->end();iter++)
		{
			NodeIndex index = *iter;
			const NodeDesc& desc = m_Data[index];
			while (curX < desc.x)
			{
				outStream << std::setw(wid) << ".";
				curX++;
			}
			outStream << std::setw(wid) << desc.id;
			curX += 1;
		}
		while (curX <= maxX)
		{
			outStream << std::setw(wid) << '.';
			curX++;
		}
		outStream << '|' << std::endl;
		curY -= 1;
	}
	outStream << std::setw(wid) << 'Y' << '+' << std::string(wid * (maxX - minX + 1), '-') <<'+'<< std::endl;
	outStream << std::setw(wid) << 'X';
	for (curX = minX; curX <= maxX; curX++)
	{
		outStream << std::setw(wid) << curX ;
	}
	outStream << std::setw(wid) << "X" << std::endl;
}

void GridMap::PrintLabel(std::ostream& outStream, const std::vector<std::string>& labelMap, int charWidth) const
{
	int minX, maxX, minY, maxY;
	minX = m_Data[m_xLinkedListList.front().front()].x;
	maxX = m_Data[m_xLinkedListList.back().back()].x;
	minY = m_Data[m_yLinkedListList.front().front()].y;
	maxY = m_Data[m_yLinkedListList.back().back()].y;

	int wid = 1;
	int t = std::max(std::max(abs(minX), abs(maxX)), std::max(abs(minY), abs(maxY)));
	while (t > 0)
	{
		wid++;
		t /= 10;
	}
	wid = std::max(wid, charWidth + 1);

	for (const std::string& labs : labelMap)
	{
		wid = std::max(wid, int(labs.length() + 1));
	}

	int curX, curY;
	curY = maxY;
	curX = minX;
	std::string edgeTop(wid * (maxX - minX + 1), '-');
	outStream << std::setw(wid) << "Y" << '+' << edgeTop << '+' << std::endl;
	for (auto iterList = m_yLinkedListList.rbegin(); iterList != m_yLinkedListList.rend(); iterList++)
	{

		curX = minX;
		outStream << std::setw(wid) << curY << '|';
		for (auto iter = iterList->begin(); iter != iterList->end(); iter++)
		{
			NodeIndex index = *iter;
			const NodeDesc& desc = m_Data[index];
			while (curX < desc.x)
			{
				outStream << std::setw(wid) << ".";
				curX++;
			}
			outStream << std::setw(wid) << labelMap[desc.id];
			curX += 1;
		}
		while (curX <= maxX)
		{
			outStream << std::setw(wid) << '.';
			curX++;
		}
		outStream << '|' << std::endl;
		curY -= 1;
	}
	outStream << std::setw(wid) << 'Y' << '+' << std::string(wid * (maxX - minX + 1), '-') << '+' << std::endl;
	outStream << std::setw(wid) << 'X';
	for (curX = minX; curX <= maxX; curX++)
	{
		outStream << std::setw(wid) << curX;
	}
	outStream << std::setw(wid) << "X" << std::endl;
}

void GridMap::Clear()
{
	m_Data.clear();
	m_xLinkedListList.clear();
	m_yLinkedListList.clear();
}
