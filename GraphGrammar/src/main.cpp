#include "opencv2/opencv.hpp"
#include "CommonGG.h"
#include "Visualization.h"
#include "GraphGrammar.h"

#include "utilPrintRule.h"

int main(int argn, char** argv)
{
	Visualization visual;
	visual.SetBeginLabel(true, "s");
	std::string graphFileA001("./res/graph-a-001.txt");
	std::string ruleFileA001("./res/rule-a-001.txt");
	std::string ruleFileA002("./res/rule-a-002.txt");
	std::string ruleFileA003("./res/rule-a-003.txt");
	std::string wildcard("*");	// Í¨Åä·û

	std::string gmlGraphTarget = visual.ReadFile(graphFileA001);
	std::string gmlRuleA003 = visual.ReadFile(ruleFileA003);

	auto vRule = ggl::Rule_GMLparser::parseRule(gmlRuleA003);
	if (vRule.second > 0)
	{
		std::cout << "[error] rule GML parsing fail\n";
		return 0;
	}

	auto vGraph = ggl::Graph_GMLparser::parseGraph(gmlGraphTarget);
	if (vGraph.second > 0)
	{
		std::cout << "[error] graph GML parsing fail\n";
		return 0;
	}

	RuleSet ruleSet;
	ruleSet.AddRule(vRule.first);
	std::cout << ruleFileA003 << std::endl;
	std::cout << gmlRuleA003 << std::endl;
	ggl_util::printRule(vRule.first);
	ggl_util::printLeftSidePattern(vRule.first);
	ggl_util::printRightSidePattern(vRule.first);

	GraphGrammar graphGrammar(ruleSet);
	graphGrammar.SetInputGraph(vGraph.first);
	int ret = graphGrammar.Step(10);
	const ggl::Graph& outputGraph = graphGrammar.GetLastGraph();

	cv::Mat imgOutput = visual.Graph2Img(outputGraph);
	cv::Mat imgInput = visual.Graph2Img(vGraph.first);
	
	cv::imwrite("./res/GraphGrammarInputImg.jpg", imgInput);
	cv::imwrite("./res/GraphGrammarOutputImg.jpg", imgOutput);

	std::cout.flush();

	return ret;
}