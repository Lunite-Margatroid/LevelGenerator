#pragma once
#include "LG_Common.h"
#include "CommonGG.h"
#include "CommonV.h"

#include "Visualization.h"
#include "GraphGrammar.h"
#include "opencv2\opencv.hpp"
#include "FileParser.h"

class LG_DLL_API LevelGenerator
{
	Visualization m_visual;
	FileParser m_parser;
	RuleSet* m_pRuleSet;
	GraphGrammar* m_pGrammar;
	ggl::Graph m_InputGraph;
	
public:
	LevelGenerator();
	LevelGenerator(const LevelGenerator& other) = delete;
	~LevelGenerator();
	LevelGenerator& operator = (const LevelGenerator& other) = delete;

	void Init(const ggl::Graph& graph, const std::string& filePath);
	void Init(const std::string& graphFile, const std::string& ruleFile);

	void SetInputGraph(const ggl::Graph& graph);
	void SetInputGraphGML(const std::string& glm);
	void SetInputGraphFile(const std::string& filePath);

	void SetRuleSet(const std::string& filePath);

	void SetRandSeed(unsigned int seed);
	int Step(int nStep);

	// cv::Mat Graph2Img(const ggl::Graph& graph);

	void Output(const std::string& fileName);

	void SetBeginNodeLabel(const std::string& label, bool b = true);

	void OutputGrid(std::ostream& out);
	void OutputGridAndLevel(std::ostream& out, const std::string& fileName);
};