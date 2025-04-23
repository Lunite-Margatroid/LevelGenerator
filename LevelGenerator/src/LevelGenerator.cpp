#include "LevelGenerator.h"
#include "ggl/Graph_GML_writer.hh"
#include "CellularAutoma.h"
#include "LevelDrawer.h"
void LevelGenerator::Init(const ggl::Graph& graph, const std::string& filePath)
{
	SetInputGraph(graph);
	SetRuleSet(filePath);
}

void LevelGenerator::Init(const std::string& graphFile, const std::string& ruleFile)
{
	SetInputGraphFile(graphFile);
	SetRuleSet(ruleFile);
}

LevelGenerator::LevelGenerator()
	:m_InputGraph(),
	m_pRuleSet(nullptr),
	m_pGrammar(nullptr)
{
	m_visual.SetIdxPrint(false);
}

LevelGenerator::~LevelGenerator()
{
	if (m_pRuleSet) { 
		delete m_pRuleSet;
		m_pRuleSet = nullptr;
	}
	if (m_pGrammar)
	{
		delete m_pGrammar;
		m_pGrammar = nullptr;
	}

}

void LevelGenerator::SetInputGraph(const ggl::Graph& graph)
{
	m_InputGraph = graph;
}

void LevelGenerator::SetInputGraphGML(const std::string& glm)
{
	m_InputGraph = m_parser.ParseGraphGML(glm);
}

void LevelGenerator::SetInputGraphFile(const std::string& filePath)
{
	m_InputGraph = m_parser.ParseGraphGMLFile(filePath);
}

void LevelGenerator::SetRuleSet(const std::string& filePath)
{
	if (m_pRuleSet == nullptr)
	{
		m_pRuleSet = new RuleSet();
		m_pGrammar = new GraphGrammar(*m_pRuleSet);
	}
	// m_pRuleSet->Reset();
	std::vector<std::pair<ggl::Rule, float>> rules;
	m_parser.ParseRuleGMLFileB(filePath, rules);

	for (std::pair<ggl::Rule, float> rule : rules)
	{
		m_pRuleSet->AddRule(rule.first, rule.second);
	}
}

void LevelGenerator::SetRandSeed(unsigned int seed)
{
	m_pGrammar->SetSeed(seed);
}

int LevelGenerator::Step(int nStep)
{
	m_pGrammar->SetInputGraph(m_InputGraph);
	return m_pGrammar->Step(nStep);
}

void LevelGenerator::Output(const std::string& fileName)
{
	const std::vector<ggl::Graph>& graphs = m_pGrammar->GetOutputVector();


	int count = 0;

	// Output original graph to Img
	std::stringstream sss;
	sss.clear();
	sss << fileName << '_' << count << ".jpg";
	cv::imwrite(sss.str(), m_visual.Graph2Img(m_InputGraph));
	std::cout << "Img Write: " << sss.str() << std::endl;
	
	// Output intermediate graph and final graph as Img
	for (const auto& graph : graphs)
	{
		std::stringstream ss;
		ss.clear();
		ss << fileName << '_' << ++count << ".jpg";
		cv::imwrite(ss.str(), m_visual.Graph2Img(graph));
		std::cout << "Img Write: " << ss.str() << std::endl;
	}

	// Output final graph as GML
	std::stringstream gmlFilePath;
	gmlFilePath << fileName << ".txt";
	std::ofstream gmlFile;
	gmlFile.open(gmlFilePath.str(), std::ios::out);
	if (gmlFile.is_open())
	{
		ggl::Graph_GML_writer::write(gmlFile, graphs.back());
		std::cout << "GML output: " << gmlFilePath.str() << std::endl;
		gmlFile.close();
	}
	else
	{
		std::cout << "Creating file failed. Cant output GML File.\n";
	}
}

void LevelGenerator::SetBeginNodeLabel(const std::string& label, bool b)
{
	m_visual.SetBeginLabel(b, label);
}

void LevelGenerator::OutputGrid(std::ostream& out)
{
	if (m_pGrammar && m_pGrammar->GetOutputVector().size() > 0)
	{
		const sgm::Graph_boost<ggl::Graph> gi(m_pGrammar->GetLastGraph());
		CellularAutoma gridMap(gi);
		gridMap.Generate();
	}
}

void LevelGenerator::OutputGridAndLevel(std::ostream& out, const std::string& fileName)
{
	if (m_pGrammar && m_pGrammar->GetOutputVector().size() > 0)
	{
		const sgm::Graph_boost<ggl::Graph> gi(m_pGrammar->GetLastGraph());
		CellularAutoma gridMap(gi);
		gridMap.Generate();

		// Output physicial Level
		{
			LevelDrawer ld;
			std::stringstream ss;
			ss << fileName << "_level.jpg";
			cv::imwrite(ss.str(), ld.GridMap2Img(gridMap));
			std::cout << "Level Img Output: " << ss.str() << std::endl;
		}
	}
}
