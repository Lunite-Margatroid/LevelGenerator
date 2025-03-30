/*
*   RULE
* 
* 1(B)         1(A) - 3(B)
* |      =>            |
* 0(A)         0(a) - 2(b)
*/
#include <fstream>
#include <sstream>

#include "ggl/Graph.hh"
#include "ggl/Rule.hh"
#include "ggl/Rule_GMLparser.hh"
#include "ggl/Rule_GML_grammar.hh"
#include "ggl/Rule_GML_writer.hh"

#include "sgm/Graph_boost.hh"
#include "utilPrintRule.h"

#include "TypeDef.h"


int main(int argn, char** argv)
{
	std::ifstream inFile;
	std::string filePath("./res/rule-a-001.txt");
	inFile.open(filePath, std::ios::in);
	if (inFile.is_open())
	{
		std::stringstream ss;
		ss << inFile.rdbuf();
		
		std::cout << "============= RULE GML ===============\n";
		std::cout << "File: \"" << filePath << "\"\n";
		std::cout << ss.str() << std::endl;

		std::pair<ggl::Rule, int> rule = ggl::Rule_GMLparser::parseRule(ss.str());

		printRule(rule.first);
		printLeftSidePattern(rule.first);
		printRightSidePattern(rule.first);


	}
	else
	{
		std::cout << "Can't open the file " << filePath << std::endl;
	}

	return 0;
}