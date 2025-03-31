#include "CommonV.h"
#include "Visualization.h"
#include "utilPrintGraph_Interface.h"

#include "sgm/MR_Storing.hh"
#include "sgm/Pattern.hh"
#include "sgm/SGM_vf2.hh"
#include "sgm/Graph_boost.hh"
#include "sgm/MC_Node.hh"

#include "ggl/Graph_Storage.hh"
#include "ggl/GS_stream.hh"
#include "ggl/GS_STL.hh"

#include <sstream>

int main(int argn, char** argv)
{
	Visualization visual;
	visual.SetBeginLabel(true, "s");
	visual.SetIdxPrint(false);
	std::string graphFile("./res/graph-a-001.txt");
	std::string ruleFile("./res/rule-a-001.txt");
	std::string ruleFileA002("./res/rule-a-002.txt");
	std::string ruleFileA003("./res/rule-a-003.txt");
	std::string wildcard("*");	// 通配符
	// cv::Mat graph = visual.ParseGraph(graphFile);
	// cv::Mat rule = visual.ParseRule(ruleFile);
	// 
	// 
	// cv::imwrite("./res/graphImg.jpg", graph);
	// cv::imwrite("./res/ruleImg.jpg", rule);

	ggl::Graph_GMLparser graphParser;
	ggl::Rule_GMLparser ruleParser;

	std::pair<ggl::Graph, int> vGraph = graphParser.parseGraph(visual.ReadFile(graphFile));
	std::pair<ggl::Rule, int> vRule = ruleParser.parseRule(visual.ReadFile(ruleFileA003));

	ggl::GS_stream gsStream(std::cout);
	std::vector<ggl::Graph> graphVector;
	ggl::GS_STL_pushAllT gsVector(graphVector);

	ggl::MR_ApplyRule applyRule(gsVector);

	ggl::LeftSidePattern lPattern(vRule.first);
	sgm::Graph_boost<ggl::Graph> gi(vGraph.first);

	sgm::Pattern_Interface::ConstraintVec constraints; // 约束向量

	sgm::Pattern toFind(lPattern, constraints, wildcard);

	sgm::SGM_vf2 sgmVF2;
	sgmVF2.findMatches(lPattern, gi, applyRule, UINT_MAX);

	std::cout.flush();

	// applyRule.reportHit(lPattern, gi, mr);
	for (int i =0;i < graphVector.size(); i++)
	{
		cv::Mat outImg = visual.Graph2Img(graphVector[i]);
		std::string out_1("./res/testout");
		std::string outExt(".jpg");
		std::stringstream ss;
		ss << out_1 << i << outExt;
		cv::imwrite(ss.str(), outImg);
	}

	return 0;
}