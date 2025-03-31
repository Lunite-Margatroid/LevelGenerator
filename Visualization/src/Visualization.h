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
	// 是否绘节点在数据结构中的索引
	bool m_bPrintInd;
	// 是否从特定的标签的节点开始绘制。若指定标签不唯一，随机选择一个节点作为起始节点。
	bool m_bLableBegin;
	// 作为起点的节点的标签
	std::string m_strBeginLabel;
private:
	cv::Mat DrawTreeGraph(const sgm::Graph_Interface& graph, const std::vector<std::vector<int>>& nodes,
		int radius, int depth, int rank) const;
public:
	Visualization(bool bPrintInd);
	Visualization();
	Visualization(const Visualization& other) = default;
	Visualization& operator = (const Visualization& other) = default;
	~Visualization() = default;

	cv::Mat GraphInterface2Img(const sgm::Graph_Interface& gi) const;
	cv::Mat Graph2Img(const ggl::Graph& graph) const;
	cv::Mat GraphGML2Img(const std::string& graphGML) const;
	cv::Mat RuleGML2Img(const std::string& ruleGML) const;
	cv::Mat Rule2Img(const ggl::Rule& rule) const;

	cv::Mat ParseGraph(const std::string& filePath) const;
	cv::Mat ParseRule(const std::string& filePath) const;

	std::string ReadFile(const std::string& filePath) const;

	// properity
	void SetIdxPrint(bool bIdxPrint);
	void SetBeginLabel(bool bLabelBegin,const std::string& label = "");
};