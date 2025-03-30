#include "CommonV.h"
#include "Visualization.h"

cv::Mat Visualization::DrawTreeGraph(const sgm::Graph_Interface& graph, const std::vector<std::vector<int>>& nodes, int radius, int depth, int rank) const
{
	int pixelWidth = depth * COL_WIDTH;
	int pixelHeight = rank * NODE_GAP;
	int colWidthD2 = COL_WIDTH / 2;
	cv::Mat outImg(pixelHeight, pixelWidth, CV_8UC3, cv::Scalar(255,255,255));
	std::vector<std::pair<int, int>> nodeCoord;
	int nNode = graph.getNodeNumber();
	nodeCoord.resize(nNode);
	for (int i = 0; i < nodes.size(); i++)
	{
		int y0 = (rank - nodes[i].size() + 1) * NODE_GAP / 2;
		for (int j = 0; j < nodes[i].size(); j++)
		{
			int curNode = nodes[i][j];
			int x = i * COL_WIDTH + colWidthD2;
			int y = y0 + j * NODE_GAP;
			nodeCoord[curNode] = std::make_pair(x, y);

			cv::ellipse(outImg, cv::Point(x, y), cv::Size(DIAM, DIAM), 0, 0, 360, cv::Scalar(0, 0, 0), LINE_THICKNESS, LINE_TYPE);

			std::string nodeLabel = graph.getNodeLabel(curNode);
			std::stringstream ss;
			ss.clear();
			ss << curNode << ": " << nodeLabel;
			cv::HersheyFonts font = cv::FONT_HERSHEY_SIMPLEX;
			float fontScale = 1.0;
			int baseLine = y + RADIUS / 2;
			
			cv::Size textRect = cv::getTextSize(ss.str(), font, 1, TEXT_THICKNESS, &baseLine);
			fontScale = float(RADIUS) / float(textRect.height);
			textRect.height *= fontScale;
			textRect.width *= fontScale;
			cv::putText(outImg, ss.str(), cv::Point(x - textRect.width / 2, y + textRect.height / 2), font, fontScale,
				cv::Scalar(0,0,0), TEXT_THICKNESS, LINE_TYPE);
		}
	}

	for (int i = 0; i < nNode; i++)
	{
		for (auto iter = graph.getOutEdgesBegin(i); iter != graph.getOutEdgesEnd(i); iter++)
		{
			int postNode = iter->getToIndex();
			float x1 = nodeCoord[i].first;
			float y1 = nodeCoord[i].second;
			float x2 = nodeCoord[postNode].first;
			float y2 = nodeCoord[postNode].second;
			float deltaX = x2 - x1;
			float deltaY = y2 - y1;
			float length = sqrtf(deltaX * deltaX + deltaY * deltaY);
			float ratio = float(DIAM) / length;
			deltaX *= ratio;
			deltaY *= ratio;
			x1 += deltaX;
			y1 += deltaY;
			x2 -= deltaX;
			y2 -= deltaY;

			cv::line(outImg, cv::Point(int(x1), int(y1)), cv::Point(int(x2), int(y2)), cv::Scalar(0, 0, 0), LINE_THICKNESS, LINE_TYPE);
		}
	}
	

	return outImg;
}

cv::Mat Visualization::GraphInterface2Img(const sgm::Graph_Interface& gi) const
{
	// Get node number
	int nNode = gi.getNodeNumber();
	if (nNode == 0)
		return cv::Mat();
	// init the visit flag
	std::vector<bool> bFlag;
	bFlag.resize(nNode);
	std::fill(bFlag.begin(), bFlag.end(), false);
	// init the queue
	std::queue<int> q;
	// init the params for drawing
	int pixelHeight = 0, pixelWidth = 0;
	int pixelRadius = 50;
	int nDepth = 0;
	int nRank = 0;
	std::vector<std::vector<int>> nodes;
	nodes.push_back(std::vector<int>());
	// traverse
	q.push(0);
	bFlag[0] = true;
	q.push(-1);
	int tRank = 0;
	while (!q.empty())
	{
		// get the front element
		int curNode = q.front();
		q.pop();

		if (curNode >= 0)
			// traverse the edges
		{
			tRank += 1;
			nodes.back().push_back(curNode);
			for (auto iter = gi.getOutEdgesBegin(curNode); iter != gi.getOutEdgesEnd(curNode); iter++)
			{
				int postNode = iter->getToIndex();
				if (!bFlag[postNode])
				{
					q.push(postNode);
					bFlag[postNode] = true;
				}
			}
		}
		else
			// check the depth
		{
			nDepth += 1;
			nRank = std::max(nRank, tRank);
			tRank = 0;
			if (!q.empty())
			{
				q.push(-1);
				nodes.push_back(std::vector<int>());
			}
		}
	}
	return DrawTreeGraph(gi, nodes, pixelRadius, nDepth, nRank);
}

cv::Mat Visualization::Graph2Img(const ggl::Graph& graph) const
{
	// Get the interface of the graph
	sgm::Graph_boost<ggl::Graph> gi(graph);
	return GraphInterface2Img(gi);
}

cv::Mat Visualization::GraphGML2Img(const std::string& graphGML) const
{
	ggl::Graph_GMLparser parser;
	std::pair<ggl::Graph, int> ret = parser.parseGraph(graphGML);
	return Graph2Img(ret.first);
}

cv::Mat Visualization::RuleGML2Img(const std::string& ruleGML) const
{
	std::pair<ggl::Rule, int> v = ggl::Rule_GMLparser::parseRule(ruleGML);
	return Rule2Img(v.first);
}

cv::Mat Visualization::Rule2Img(const ggl::Rule& rule) const
{
	ggl::LeftSidePattern left(rule);
	ggl::RightSidePattern right(rule);
	cv::Mat leftImg = GraphInterface2Img(left);
	cv::Mat rightImg = GraphInterface2Img(right);
	cv::Mat arrowImg(COL_WIDTH, COL_WIDTH + COL_WIDTH / 2, CV_8UC3, cv::Scalar(255,255,255));
	cv::line(arrowImg, cv::Point(COL_WIDTH * 0.2, COL_WIDTH / 2), cv::Point(COL_WIDTH * 1.3, COL_WIDTH / 2),
		cv::Scalar(0, 0, 0), LINE_THICKNESS);
	cv::line(arrowImg, cv::Point(COL_WIDTH * 1.1f, COL_WIDTH * 0.618f ), cv::Point(COL_WIDTH * 1.3, COL_WIDTH / 2),
		cv::Scalar(0, 0, 0), LINE_THICKNESS);
	cv::line(arrowImg, cv::Point(COL_WIDTH * 1.1f, COL_WIDTH * 0.382f ), cv::Point(COL_WIDTH *1.3, COL_WIDTH / 2),
		cv::Scalar(0, 0, 0), LINE_THICKNESS);

	int width = leftImg.cols + arrowImg.cols + rightImg.cols;
	int height = std::max(leftImg.rows, std::max(arrowImg. rows, rightImg.rows));
	cv::Mat outImg( height, width, CV_8UC3, cv::Scalar(255,255,255));
	cv::Rect rect1(0, (height - leftImg.rows) / 2, leftImg.cols, leftImg.rows);
	cv::Rect rect2(rect1.width, (height - arrowImg.rows) / 2, arrowImg.cols, arrowImg.rows);
	cv::Rect rect3(rect1.width + rect2.width, (height - rightImg.rows) / 2, rightImg.cols, rightImg.rows);
	cv::Mat rectRange1 = outImg(rect1);
	cv::Mat rectRange2 = outImg(rect2);
	cv::Mat rectRange3 = outImg(rect3);

	leftImg.copyTo(rectRange1);
	arrowImg.copyTo(rectRange2);
	rightImg.copyTo(rectRange3);
	
	return outImg;
}

cv::Mat Visualization::ParseGraph(const std::string& filePath) const
{
	std::ifstream inFile(filePath, std::ios::in);
	if (!inFile.is_open())
	{
		return cv::Mat(100, 100, CV_8UC3,cv::Scalar(255,255,255));
	}
	std::stringstream ss;
	ss << inFile.rdbuf();

	return GraphGML2Img(ss.str());
}

cv::Mat Visualization::ParseRule(const std::string& filePath) const
{
	std::ifstream inFile(filePath, std::ios::in);
	if (!inFile.is_open())
	{
		return cv::Mat(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));
	}
	std::stringstream ss;
	ss << inFile.rdbuf();

	return RuleGML2Img(ss.str());
}
