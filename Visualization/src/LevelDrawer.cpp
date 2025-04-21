#include "CommonV.h"
#include "GridMap.h"
#include "LevelDrawer.h"

LevelDrawer::LevelDrawer()
	:m_nGridWidth(100),
	m_nGridHeight(71),
	m_nLineWidth(11),
	m_nGapWidth(11),
	m_nPassageWidth(20)
{
	m_cBackColor[0] = 128u;
	m_cBackColor[1] = 128u;
	m_cBackColor[2] = 128u;
	m_cBackColor[3] = 255u;

	m_cLineColor[0] = 0u;
	m_cLineColor[1] = 0u;
	m_cLineColor[2] = 0u;
	m_cLineColor[3] = 255u;

	m_cGroundColor[0] = 255u;
	m_cGroundColor[1] = 255u;
	m_cGroundColor[2] = 255u;
	m_cGroundColor[3] = 255u;
}

void LevelDrawer::SetGridWidth(int input)
{
	m_nGridWidth = input;
}

void LevelDrawer::SetGridHeight(int input)
{
	m_nGridHeight = input;
}

void LevelDrawer::SetLineWidth(int input)
{
	m_nLineWidth = input;
}

void LevelDrawer::SetGapWidth(int input)
{
	m_nGapWidth = input;
}

void LevelDrawer::SetPassageWidth(int input)
{
	m_nPassageWidth = input;
}

void LevelDrawer::SetBackColor(unsigned char* backColor)
{
	memcpy(m_cBackColor, backColor, 4);
}

void LevelDrawer::SetLineColor(unsigned char* lineColor)
{
	memcpy(m_cLineColor, lineColor, 4);
}

void LevelDrawer::SetGroundColor(unsigned char* groundColor)
{
	memcpy(m_cGroundColor, groundColor, 4);
}

cv::Mat LevelDrawer::GridMap2Img(const GridMap& gridMap) const
{
	int xMax = gridMap.GetXMax();
	int xMin = gridMap.GetXMin();
	int yMax = gridMap.GetYMax();
	int yMin = gridMap.GetYMin();
	int nX = xMax - xMin + 1;
	int nY = yMax - yMin + 1;
	int imgWidth = nX * m_nGridWidth + m_nGapWidth * (nX + 1);
	int imgHeight = nY * m_nGridHeight + m_nGapWidth * (nY + 1);
	cv::LineTypes lineType = cv::LINE_8;
	const auto& datas = gridMap.GetData();
	cv::Mat outImg(imgHeight, imgWidth, CV_8UC3, cv::Scalar(m_cBackColor[0], m_cBackColor[1], m_cBackColor[2]));

	auto DrawGrid = [&](int x, int y, std::bitset<4> access)->void {
		int left = x - xMin;
		left = left * m_nGridWidth + (left + 1) * m_nGapWidth;
		left += (m_nGapWidth >> 1);
		int right = left + m_nGridWidth;
		int bottom = y - yMin;
		bottom = bottom * m_nGridHeight + (bottom + 1) * m_nGapWidth;
		bottom += (m_nGridHeight >> 1);
		int top = bottom + m_nGridHeight;
		int halfLineWidth = m_nLineWidth >> 1;
		int midX = left + (m_nGridWidth >> 1);
		int midY = bottom + (m_nGridHeight >> 1);
		// draw ground
		cv::rectangle(outImg, cv::Point(left, imgHeight - bottom), cv::Point(right, imgHeight - top), 
			cv::Scalar(m_cGroundColor[0], m_cGroundColor[1], m_cGroundColor[2] ), -1, lineType);
		// draw framework
		cv::rectangle(outImg, 
			cv::Point(left + halfLineWidth, imgHeight - (bottom + halfLineWidth)),
			cv::Point(right - halfLineWidth, imgHeight - (top - halfLineWidth)),
			cv::Scalar(m_cLineColor[0], m_cLineColor[1], m_cLineColor[2]),
			m_nLineWidth,
			lineType);
		// draw passage
		if (access[static_cast<int>(GridMap::Direction::minus_x)])
		{
			int tLeft = left - m_nGapWidth;
			int tRight = left + m_nLineWidth;
			int tTop = midY + (m_nPassageWidth >> 1);
			int tBottom = tTop - m_nPassageWidth;
			cv::rectangle(
				outImg, cv::Point(tLeft, imgHeight - tBottom),
				cv::Point(tRight, imgHeight - tTop),
				cv::Scalar(m_cGroundColor[0], m_cGroundColor[1], m_cGroundColor[2]),
				-1, lineType);
		}
		if (access[static_cast<int>(GridMap::Direction::plus_x)])
		{
			int tLeft = right - m_nLineWidth;
			int tRight = right + m_nGapWidth;
			int tTop = midY + (m_nPassageWidth >> 1);
			int tBottom = tTop - m_nPassageWidth;
			cv::rectangle(
				outImg, cv::Point(tLeft, imgHeight - tBottom),
				cv::Point(tRight, imgHeight - tTop),
				cv::Scalar(m_cGroundColor[0], m_cGroundColor[1], m_cGroundColor[2]),
				-1, lineType);
		}
		if (access[static_cast<int>(GridMap::Direction::minus_y)])
		{
			int tLeft = midX - (m_nPassageWidth >> 1);
			int tRight = tLeft+ m_nPassageWidth;
			int tTop = bottom + m_nLineWidth;
			int tBottom = bottom - m_nGapWidth;
			cv::rectangle(
				outImg, cv::Point(tLeft, imgHeight - tBottom),
				cv::Point(tRight, imgHeight - tTop),
				cv::Scalar(m_cGroundColor[0], m_cGroundColor[1], m_cGroundColor[2]),
				-1, lineType);
		}
		if (access[static_cast<int>(GridMap::Direction::plus_y)])
		{
			int tLeft = midX - (m_nPassageWidth >> 1);
			int tRight = tLeft + m_nPassageWidth;
			int tTop = top + m_nGapWidth;
			int tBottom = bottom - m_nLineWidth;
			cv::rectangle(
				outImg, cv::Point(tLeft, imgHeight - tBottom),
				cv::Point(tRight, imgHeight - tTop),
				cv::Scalar(m_cGroundColor[0], m_cGroundColor[1], m_cGroundColor[2]),
				-1, lineType);
		}
	};

	for (const GridMap::NodeDesc& node : datas)
	{
		DrawGrid(node.x, node.y, node.con);
	}

	return outImg;
}
