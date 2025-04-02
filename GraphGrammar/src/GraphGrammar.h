#pragma once

#include "RuleSet.h"

class GraphGrammar
{
private:
	RuleSet& m_ruleSet;
	ggl::Graph m_inputGraph;
	std::vector<ggl::Graph> m_graphs;
	unsigned int m_Seed;

	// 输入具有相同left pattern的rule及其权重，执行一次graph grammar。
	bool ApplyRules(const std::vector<std::pair<ggl::Rule, float>>& rules, const sgm::Graph_Interface& targetGI);
public:
	GraphGrammar() = delete;
	GraphGrammar(RuleSet& ruleSet);
	~GraphGrammar() = default;
	GraphGrammar(const GraphGrammar& other) = delete;
	GraphGrammar& operator = (const GraphGrammar& other) = delete;
	// 返回最新的graph grammar输出
	const ggl::Graph& GetLastGraph() const;
	// 清空生成内容
	void ResetGC();
	// 设置输入graph 同时清空生成内容
	void SetInputGraph(const ggl::Graph& graph);
	// 执行一步graph grammar. 如果没有匹配到任何规则，返回0 否则返回1。不重置随机数
	int Step();
	// 执行nSteps次规则 返回成功匹配到规则的次数。重置随机数 std::srand(m_Seed)
	int Step(int nSteps);
	// pattern是否可以匹配target
	bool Match(const sgm::Pattern_Interface& pattern, const sgm::Graph_Interface& target);
	// 设置随机种子
	void SetSeed(unsigned int seed);

	const std::vector<ggl::Graph>& GetOutputVector() const;
};