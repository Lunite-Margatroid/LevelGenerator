#include "CommonV.h"
#include "Visualization.h"
#include "utilPrintGraph_Interface.h"


#include <sstream>

int main(int argn, char** argv)
{
	Visualization visual;
	std::string graphFile("./res/graph-a-001.txt");
	std::string ruleFile("./res/rule-a-001.txt");
	cv::Mat graph = visual.ParseGraph(graphFile);
	cv::Mat rule = visual.ParseRule(ruleFile);
	

	cv::imwrite("./res/graphImg.jpg", graph);
	cv::imwrite("./res/ruleImg.jpg", rule);


	return 0;
}