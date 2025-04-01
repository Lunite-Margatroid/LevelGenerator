#include "opencv2/opencv.hpp"
#include "CommonGG.h"
#include "Visualization.h"
#include "GraphGrammar.h"
#include "FileParser.h"
#include "utilPrintRule.h"

void printConstraints(const ggl::Rule rule);
void printCopyAndPaste(const ggl::Rule rule);
void printWildcard(const ggl::Rule rule);

int testMain();

int testReader();

int LevelGeneratr();

int SameTest();

int main(int argn, char** argv)
{
	return LevelGeneratr();
}

int SameTest()
{
	FileParser parser;
	std::vector<std::pair<ggl::Rule, float>> rules;
	parser.ParseRuleGMLFileB("./res/rule-b-001.txt", rules);

	RuleSet ruleSet;
	ggl_util::printLeftSidePattern(rules[2].first);
	ggl_util::printLeftSidePattern(rules[3].first);
	std::cout << "rule3 == rule4 ? " <<
		(ruleSet.SameLeftPattern(ggl::LeftSidePattern(rules[2].first), ggl::LeftSidePattern(rules[3].first)) ? "yes" : "no" )<< std::endl;
	return 0;
}

int LevelGeneratr()
{
	FileParser parser;
	RuleSet ruleSet;
	Visualization visual;
	visual.SetBeginLabel(true, "e");
	visual.SetIdxPrint(false);
	std::vector<std::pair<ggl::Rule, float>> rules;
	parser.ParseRuleGMLFileB("./res/rule-b-001.txt", rules);
	for (std::pair<ggl::Rule, float> rule : rules)
	{
		ggl_util::printRule(rule.first);
		ggl_util::printLeftSidePattern(rule.first);
		ggl_util::printRightSidePattern(rule.first);
		ruleSet.AddRule(rule.first, rule.second);
	}
	GraphGrammar gg(ruleSet);

	ggl::Graph graph = parser.ParseGraphGMLFile("./res/graph-a-003.txt");
	gg.SetInputGraph(graph);

	for (int i = 0; i < 10; i++)
	{
		gg.SetSeed(i);
		gg.ResetGC();
		int nSteps = 0;
		while (gg.Step() > 0 && nSteps < 30)
		{
			nSteps++;

			cv::Mat outImg = visual.Graph2Img(gg.GetLastGraph());
			std::stringstream ss;
			ss.clear();
			ss << "./res/LGTestOutImg_"<< i << '_' << nSteps << ".jpg";
			std::cout << "Step: " << nSteps << std::endl;
			cv::imwrite(ss.str(), outImg);
		}
	}
	return 0;
}

int testMain()
{
	Visualization visual;
	visual.SetBeginLabel(true, "s");
	std::string graphFileA001("./res/graph-a-001.txt");
	std::string graphFileA002("./res/graph-a-002.txt");
	std::string ruleFileA001("./res/rule-a-001.txt");
	std::string ruleFileA002("./res/rule-a-002.txt");
	std::string ruleFileA003("./res/rule-a-003.txt");
	std::string ruleFileA004("./res/rule-a-004.txt");
	std::string ruleFileA005("./res/rule-a-005.txt");
	std::string ruleFileA006("./res/rule-a-006.txt");

	std::string gmlGraphTarget = visual.ReadFile(graphFileA002);
	std::string gmlRuleA003 = visual.ReadFile(ruleFileA005);

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
	printWildcard(vRule.first);
	printConstraints(vRule.first);
	printCopyAndPaste(vRule.first);

	GraphGrammar graphGrammar(ruleSet);
	graphGrammar.SetInputGraph(vGraph.first);
	int ret = graphGrammar.Step(10);
	const ggl::Graph& outputGraph = graphGrammar.GetLastGraph();

	cv::Mat imgOutput = visual.Graph2Img(outputGraph);
	cv::Mat imgInput = visual.Graph2Img(vGraph.first);

	cv::imwrite("./res/GraphGrammarInputImg.jpg", imgInput);
	cv::imwrite("./res/GraphGrammarOutputImg-a-005.jpg", imgOutput);

	std::cout.flush();

	return ret;
}

int testReader()
{
	FileParser parser;
	// std::vector<std::pair<ggl::Rule, float>> rules;
	// parser.ParseRuleGMLFileB("./res/rule-b-001.txt","./res/rule-w-001.txt",rules);
	// 
	// for (auto& [rule, w] : rules)
	// {
	// 	std::cout << "============ weight =============\n";
	// 	std::cout << "========  " << w << "  ===========\n";
	// 	std::cout << "=================================\n";
	// 
	// 	// ggl_util::printRule(rule);
	// 	// ggl_util::printLeftSidePattern(rule);
	// 	// ggl_util::printRightSidePattern(rule);
	// }

	ggl::Graph g =parser.ParseGraphGMLFile("./res/graph-a-001.txt");
	sgm::Graph_boost<ggl::Graph> gi(g);
	ggl_util::print(gi);

	return 0;
}

void printConstraints(const ggl::Rule rule)
{
	std::cout << "\n number of constraints = " << rule.getLeftSide().constraints.size() << std::endl;

	typedef std::vector< sgm::Pattern_Interface::Match_Constraint* > CV;
	const CV& cv = rule.getLeftSide().constraints;
	for (CV::const_iterator c = cv.begin(); c != cv.end(); ++c) {
		const sgm::MC_NodeLabel* cur = dynamic_cast<const sgm::MC_NodeLabel*>(*c);
		{
			if (cur != NULL) {
				std::cout << " + MC_NodeLabel " << std::endl;
				std::cout << "   id " << cur->constrainedNodeID << std::endl;
				std::cout << "   op " << (cur->compareType == sgm::MC_NodeLabel::ALLOWED ? "=" : "!") << std::endl;
				std::cout << "   nodeLabels = ";
				for (sgm::MC_NodeLabel::LabelSet::const_iterator l = cur->nodeLabels.begin(); l != cur->nodeLabels.end(); ++l)
					std::cout << " '" << *l << "'";
				std::cout << std::endl;
				continue;
			}} {
			const sgm::MC_EdgeLabel* cur = dynamic_cast<const sgm::MC_EdgeLabel*>(*c);
			if (cur != NULL) {
				std::cout << " + MC_EdgeLabel " << std::endl;
				std::cout << "   from " << cur->constrainedFromID << std::endl;
				std::cout << "   to   " << cur->constrainedToID << std::endl;
				std::cout << "   op " << (cur->compareType == sgm::MC_EdgeLabel::ALLOWED ? "=" : "!") << std::endl;
				std::cout << "   edgeLabels = ";
				for (sgm::MC_EdgeLabel::LabelSet::const_iterator l = cur->edgeLabels.begin(); l != cur->edgeLabels.end(); ++l)
					std::cout << " '" << *l << "'";
				std::cout << std::endl;
				continue;
			}} {
				const sgm::MC_NoEdge* cur = dynamic_cast<const sgm::MC_NoEdge*>(*c);
				if (cur != NULL) {
					std::cout << " + MC_NoEdge " << std::endl;
					std::cout << "   from " << cur->constrainedFromID << std::endl;
					std::cout << "   to   " << cur->constrainedToID << std::endl;
					continue;
				}} {
				const sgm::MC_NodeAdjacency* cur = dynamic_cast<const sgm::MC_NodeAdjacency*>(*c);
				if (cur != NULL) {
					std::cout << " + MC_NodeAdjacency " << std::endl;
					std::cout << "   id " << cur->constrainedNodeID << std::endl;
					std::cout << "   op ";
					switch (cur->op) {
					case sgm::MC_NodeAdjacency::MC_EQ: std::cout << "="; break;
					case sgm::MC_NodeAdjacency::MC_G: std::cout << ">"; break;
					case sgm::MC_NodeAdjacency::MC_GQ: std::cout << ">="; break;
					case sgm::MC_NodeAdjacency::MC_L: std::cout << "<"; break;
					case sgm::MC_NodeAdjacency::MC_LQ: std::cout << "<="; break;
					default: std::cout << "unknown operator type";
					}
					std::cout << std::endl;
					std::cout << "   count " << cur->count << std::endl;
					std::cout << "   nodeLabels = ";
					for (sgm::MC_NodeAdjacency::LabelSet::const_iterator l = cur->nodeLabels.begin(); l != cur->nodeLabels.end(); ++l)
						std::cout << " '" << *l << "'";
					std::cout << std::endl;
					std::cout << "   edgeLabels = ";
					for (sgm::MC_NodeAdjacency::LabelSet::const_iterator l = cur->edgeLabels.begin(); l != cur->edgeLabels.end(); ++l)
						std::cout << " '" << *l << "'";
					std::cout << std::endl;

					continue;
				}}
			std::cout << " !!! unknown constraint type !!! " << std::endl;
	}

}

void printCopyAndPaste(const ggl::Rule rule)
{
	std::cout << "\n number of nodes with copy-and-paste operations = " << rule.getCopyAndPasteOperations().size() << "\n" << std::endl;
	for (ggl::Rule::CopyAndPasteOperations::const_iterator n = rule.getCopyAndPasteOperations().begin(); n != rule.getCopyAndPasteOperations().end(); n++) {
		for (ggl::Rule::CopyAndPasteOperations::mapped_type::const_iterator cnp = n->second.begin(); cnp != n->second.end(); cnp++) {
			std::cout << " copy-and-paste : source(" << cnp->source << ") pasteID(" << cnp->pasteID << ") target(";
			if (cnp->target != (size_t)INT_MAX)
				std::cout << cnp->target;
			std::cout << ") edgeLabels (";
			for (ggl::Rule::RuleCnP::LabelSet::const_iterator l = cnp->edgeLabels.begin(); l != cnp->edgeLabels.end(); ++l)
				std::cout << " '" << *l << "'";
			std::cout << ")" << std::endl;
		}
	}
}

void printWildcard(const ggl::Rule rule)
{
	std::cout << "\n wildcard pattern = " << (rule.getUsedWildcard() == NULL ? "NULL" : "'" + *(rule.getUsedWildcard()) + "'") << std::endl;
}
