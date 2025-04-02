#pragma once
class GraphGrammar;

class RuleSet
{
	friend class GraphGrammar;
private:
	std::vector<std::vector<std::pair<ggl::Rule, float>>> m_Datas;
public:
	bool SameLeftPattern(const ggl::LeftSidePattern& p1, const ggl::LeftSidePattern& p2) const;
public:
	RuleSet();
	~RuleSet() = default;
	RuleSet& operator = (const RuleSet&) = delete;

	void AddRule(const ggl::Rule& rule, float w = 1.0f);
	void AddRule(ggl::Rule&& rule, float w = 1.0f);
	void AddRule(const std::string& ruleGML, float w = 1.0f);

	void Reset();
};