#include "CommonV.h"
#include "Visualization.h"
#include "utilPrintGraph_Interface.h"

#include <fstream>
#include <sstream>

int main(int argn, char** argv)
{
	std::fstream inFile;
	std::string filePath("./res/graph-a-001.txt");
	inFile.open(filePath, std::ios::in);
	std::stringstream ss;
	if (!inFile.is_open())
	{
		std::cout << "Can't open the file: " << filePath << std::endl;
		return 0;
	}

	ss << inFile.rdbuf();
	Visualization visual;
	
	ggl::Graph_GMLparser parser;
	auto v = parser.parseGraph(ss.str());
	auto graph = v.first;

	sgm::Graph_boost<ggl::Graph> gi(graph);
	print(gi);

	cv::Mat imgGraph = visual.Graph2Img(graph);

	cv::imshow("Display Window", imgGraph);
	cv::waitKey(0); // 等待按键按下
	return 0;
}