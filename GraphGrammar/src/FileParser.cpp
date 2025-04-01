#include "CommonGG.h"
#include "FileParser.h"

void FileParser::ReadFile(const std::string& filePath)
{
	std::fstream inFile;
	std::stringstream ss;
	inFile.open(filePath, std::ios::in);
	if (inFile.is_open())
	{
		ss << inFile.rdbuf();
		m_buffer.clear();
		m_buffer = ss.str();
		inFile.close();
		return;
	}
	std::cout << "[FileParser][error] File openning failed.\n";
}

void FileParser::ParseRuleGMLFileBHelper(const std::string& gmlRules, std::vector<std::string_view>& vGMLRule)
{
	int offset = -1;
	int len = 1;
	int idx = 0;
	const int length = gmlRules.length();
	while (idx < length)
	{
		offset += len;
		while (gmlRules[offset] == '#' && offset < length)
		{
			offset++;
		}
		idx = offset;
		while (idx < length && gmlRules[idx] != '#')
		{
			idx++;
		}
		len = idx - offset;
		if (len <= 0)
			break;
		else
		{
			vGMLRule.emplace_back(std::string_view(gmlRules.c_str() + offset, len));
		}
	}
}

void FileParser::OutStringWithLineNumber(const std::string& str, std::ostream& outStream)
{
	OutStringWithLineNumber(std::string_view(str.c_str(), str.length()), outStream);
}

void FileParser::OutStringWithLineNumber(const std::string_view& str, std::ostream& outStream)
{
		int lineNumber = 1;  // 行号从1开始

		// 查找第一个非空字符位置，避免空行
		size_t startPos = 0;

		// 如果字符串不为空
		if (startPos < str.length()) {
			// 输出第一行行号
			outStream << lineNumber++ << ": ";
		}

		// 遍历字符串中的每个字符
		for (size_t i = startPos; i < str.length(); ++i) {
			// 输出当前字符
			outStream << str[i];

			// 如果遇到换行符且不是最后一个字符
			if (str[i] == '\n' && i + 1 < str.length()) {
				// 输出下一行行号
				outStream << lineNumber++ << ": ";
			}
		}

		// 确保最后有一个换行
		if (!str.empty() && str.back() != '\n') {
			outStream << std::endl;
		}
}


ggl::Rule FileParser::ParseRuleGMLFile(const std::string& filePath)
{
	ReadFile(filePath);
	return this->ParseRuleGML(m_buffer);
}

ggl::Rule FileParser::ParseRuleGML(const std::string& gmlRule)
{
	// std::cout << gmlRule << std::endl;
	std::pair<ggl::Rule, int> v = ggl::Rule_GMLparser::parseRule(gmlRule);
	if (v.second >= 0)
	{
		std::cout << "[FileParser][error] GML Rule Parsing Failed. Line: " << v.second <<  std::endl;
		OutStringWithLineNumber( gmlRule ,std::cout);
	}
	return v.first;
}

void FileParser::ParseRuleGMLFileB(const std::string& filePath, std::vector<std::pair<ggl::Rule, float>>& rules)
{
	ReadFile(filePath);
	std::vector<std::string_view> vGMLRule;

	ParseRuleGMLFileBHelper(m_buffer, vGMLRule);


	for (const std::string_view& gml : vGMLRule)
	{
		try {
			rules.emplace_back(
				std::make_pair(
					std::move(ParseRuleGML(std::string(gml))),
					1.0f));

		}
		catch (const ggl::Rule_GML_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void FileParser::ParseRuleGMLFileB(const std::string& filePath, const std::string& filePathWeight, std::vector<std::pair<ggl::Rule, float>>& rules)
{
	float w;
	std::ifstream inFile(filePathWeight, std::ios::in);
	if (!inFile.is_open())
	{
		ParseRuleGMLFileB(filePath, rules);
		std::cout << "[FileParser][error] File containing weights open failed. Set the weights default value 1.0\n";
		return;
	}
	ReadFile(filePath);
	std::vector<std::string_view> gmls;
	ParseRuleGMLFileBHelper(m_buffer, gmls);
	for (const std::string_view& gml : gmls)
	{
		if (inFile >> w)
		{
			rules.emplace_back(
				std::make_pair(
					std::move(ParseRuleGML(std::string(gml))),
					w));
		}
		else
		{
			rules.emplace_back(
				std::make_pair(
					std::move(ParseRuleGML(std::string(gml))),
					1.0f));
			std::cout << "[FileParser][error] Weights in File is not enough. Set the weight default value 1.0\n";
		}
	}

	inFile.close();
}

ggl::Graph FileParser::ParseGraphGML(const std::string& gmlGraph)
{
	std::pair<ggl::Graph, int> v = ggl::Graph_GMLparser::parseGraph(gmlGraph);
	if (v.second >= 0)
	{
		std::cout << "[FileParser][error] GML Graph Parsing Failed. Line: " << v.second  << std::endl;
		OutStringWithLineNumber(gmlGraph, std::cout);
	}
	return v.first;
}

ggl::Graph FileParser::ParseGraphGMLFile(const std::string& filePath)
{
	ReadFile(filePath);
	return ParseGraphGML(m_buffer);
}
