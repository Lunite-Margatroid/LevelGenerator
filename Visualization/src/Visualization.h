#pragma once
#define RADIUS			20
#define DIAM			RADIUS * 2
#define COL_WIDTH		160
#define NODE_GAP		160
#define LINE_THICKNESS	2
#define TEXT_THICKNESS	2
#define LINE_TYPE		cv::LINE_AA


class Visualization
{
private:
	cv::Mat DrawTreeGraph(const sgm::Graph_Interface& graph, const std::vector<std::vector<int>>& nodes,
		int radius, int depth, int rank) const;

public:
	cv::Mat Graph2Img(const ggl::Graph& graph) const;
	cv::Mat GML2Img(const std::string& graphGML) const;
};