#pragma once

#include "RuleSet.h"

class GraphGrammar
{
private:
	RuleSet& m_ruleSet;
	ggl::Graph m_inputGraph;
	std::vector<ggl::Graph> m_graphs;
	unsigned int m_Seed;

	// ���������ͬleft pattern��rule����Ȩ�أ�ִ��һ��graph grammar��
	bool ApplyRules(const std::vector<std::pair<ggl::Rule, float>>& rules, const sgm::Graph_Interface& targetGI);
public:
	GraphGrammar() = delete;
	GraphGrammar(RuleSet& ruleSet);
	~GraphGrammar() = default;
	GraphGrammar(const GraphGrammar& other) = delete;
	GraphGrammar& operator = (const GraphGrammar& other) = delete;
	// �������µ�graph grammar���
	const ggl::Graph& GetLastGraph() const;
	// �����������
	void ResetGC();
	// ��������graph ͬʱ�����������
	void SetInputGraph(const ggl::Graph& graph);
	// ִ��һ��graph grammar. ���û��ƥ�䵽�κι��򣬷���0 ���򷵻�1�������������
	int Step();
	// ִ��nSteps�ι��� ���سɹ�ƥ�䵽����Ĵ�������������� std::srand(m_Seed)
	int Step(int nSteps);
	// pattern�Ƿ����ƥ��target
	bool Match(const sgm::Pattern_Interface& pattern, const sgm::Graph_Interface& target);
	// �����������
	void SetSeed(unsigned int seed);

	const std::vector<ggl::Graph>& GetOutputVector() const;
};