#include "CommonGG.h"
#include "GraphGrammar.h"
#include "sgm/MR_Storing.hh"

bool GraphGrammar::ApplyRules(const std::vector<std::pair<ggl::Rule, float>>& rules, const sgm::Graph_Interface& targetGI)
{
	float sum = 0.0;
	for (auto [rule, w] : rules)
	{
		sum += w;
	}
	sum = float(std::rand()) / float(RAND_MAX) * sum;
	for (auto [rule, w] : rules)
	{
		sum -= w;
		if (sum <= 0.0f)
		{
			std::vector<ggl::Graph> outVector;
			ggl::GS_STL_pushAllT gsVector(outVector);
			ggl::MR_ApplyRule applyRule(gsVector);

			ggl::LeftSidePattern lPattern(rule);

			sgm::SGM_vf2 sgmVF2;
			sgmVF2.findMatches(lPattern, targetGI, applyRule, UINT_MAX);

			if (outVector.size() > 0)
			{
				m_graphs.emplace_back(std::move(outVector.front()));
				return true;
			}
			break;
		}
	}

	std::vector<ggl::Graph> outVector;
	ggl::GS_STL_pushAllT gsVector(outVector);
	ggl::MR_ApplyRule applyRule(gsVector, true);

	ggl::LeftSidePattern lPattern(rules.back().first);

	sgm::SGM_vf2 sgmVF2;
	sgmVF2.findMatches(lPattern, targetGI, applyRule, UINT_MAX);

	if (outVector.size() > 0)
	{
		m_graphs.emplace_back(std::move(outVector.front()));
		return true;
	}
	return false;
}

GraphGrammar::GraphGrammar(RuleSet& ruleSet)
	:m_ruleSet(ruleSet),m_Seed(0)
{
	std::srand(m_Seed);
}

const ggl::Graph& GraphGrammar::GetLastGraph() const
{
	if (m_graphs.size() > 0)
		return m_graphs.back();
	else
		return m_inputGraph;
}

void GraphGrammar::ResetGC()
{
	m_graphs.clear();
}

void GraphGrammar::SetInputGraph(const ggl::Graph& graph)
{
	m_inputGraph = graph;
	m_graphs.clear();
}

int GraphGrammar::Step()
{
	const ggl::Graph& target = m_graphs.size() > 0 ? m_graphs.back() : m_inputGraph;
	sgm::Graph_boost<ggl::Graph> targetGI(target);

	for (auto rules : m_ruleSet.m_Datas)
	{
		if (Match(ggl::LeftSidePattern(rules.front().first), targetGI))
		{
			ApplyRules(rules, targetGI);
			return 1;
		}
	}
	return 0;
}

int GraphGrammar::Step(int nSteps)
{
	std::srand(m_Seed);
	int ret = 0;
	while (ret < nSteps)
	{
		int nMatch = Step();
		if (nMatch > 0)
			ret += 1;
		else
			break;
	}
	return ret;
}

bool GraphGrammar::Match(const sgm::Pattern_Interface& pattern, const sgm::Graph_Interface& target)
{
	sgm::MR_Storing::Storage storage;
	sgm::MR_Storing mr(storage);

	sgm::SGM_vf2 sgmVF2;
	sgmVF2.findMatches(pattern, target, mr, UINT_MAX);

	if (storage.size() > 0)
	{
		return true;
	}
	return false;
}

void GraphGrammar::SetSeed(unsigned int seed)
{
	m_Seed = seed;
	std::srand(m_Seed);
}
