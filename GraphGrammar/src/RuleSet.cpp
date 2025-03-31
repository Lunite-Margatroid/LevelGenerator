#include "CommonGG.h"
#include "RuleSet.h"
#include "sgm/MR_Counting.hh"

bool RuleSet::SameLeftPattern(const ggl::LeftSidePattern& p1, const ggl::LeftSidePattern& p2) const
{
	const sgm::Pattern_Interface* pi1 = dynamic_cast<const sgm::Pattern_Interface*>(&p1);
	const sgm::Pattern_Interface* pi2 = dynamic_cast<const sgm::Pattern_Interface*>(&p2);
	assert(pi1);
	assert(pi2);
	return *pi1 == *pi2;
}

void RuleSet::AddRule(const ggl::Rule& rule, float w /* w = 1.0 */)
{
	for (int i = 0; i < m_Datas.size(); i++)
	{
		if (m_Datas[i].size() > 0)
		{
			ggl::LeftSidePattern lPattern ( m_Datas[i][0].first);
			if (this->SameLeftPattern(lPattern, ggl::LeftSidePattern(rule)))
			{
				m_Datas[i].emplace_back(rule, w);
				return;
			}
		}
	}
	m_Datas.emplace_back(std::vector<std::pair<ggl::Rule, float>>());
	m_Datas.back().emplace_back(rule, w);
}

void RuleSet::AddRule(ggl::Rule&& rule, float w /* w = 1.0 */)
{
	for (int i = 0; i < m_Datas.size(); i++)
	{
		if (m_Datas[i].size() > 0)
		{
			ggl::LeftSidePattern lPattern(m_Datas[i][0].first);
			if (this->SameLeftPattern(lPattern, ggl::LeftSidePattern(rule)))
			{
				m_Datas[i].emplace_back(rule, std::move(w));
				return;
			}
		}
	}
	m_Datas.emplace_back(std::vector<std::pair<ggl::Rule, float>>());
	m_Datas.back().emplace_back(rule, std::move(w));
}

void RuleSet::AddRule(const std::string& ruleGML, float w /* w = 1.0 */)
{
	std::pair<ggl::Rule, int> v = ggl::Rule_GMLparser::parseRule(ruleGML);
	AddRule(std::move(v.first), w);
}
