#pragma once
#include <fstream>
class FileParser
{
private:
	std::ifstream m_inFile;
	std::stringstream m_ss;
	std::string m_buffer;

	void ReadFile(const std::string& filePath);
	void ParseRuleGMLFileBHelper(const std::string& gmlRules, std::vector<std::string_view>& vGMLRule);
	void OutStringWithLineNumber(const std::string& str, std::ostream& outSrream);
	void OutStringWithLineNumber(const std::string_view& str, std::ostream& outSrream);
public:
	FileParser() = default;
	FileParser(const FileParser& other) = delete;
	FileParser& operator = (const FileParser& other) = delete;
	~FileParser() = default;

	ggl::Rule ParseRuleGMLFile(const std::string& filePath);
	ggl::Rule ParseRuleGML(const std::string& gmlRule);

	/// <summary>
	/// 解析以#分割的gml rule文件。该文件包含多个Rule的gml，它们之间以#分割。
	/// </summary>
	/// <param name="filePath"> 文件路径</param>
	/// <param name="rules"> 输出。包含解析出的Rule和权重。权重默认为1</param>
	void ParseRuleGMLFileB(const std::string& filePath, std::vector<std::pair<ggl::Rule, float>>& rules);

	/// <summary>
	/// 解析以#分割的gml rule文件。该文件包含多个Rule的gml，它们之间以#分割。
	/// </summary>
	/// <param name="filePath"> gml文件路径</param>
	/// <param name="filePathWeight">记录rule权重的文本文件，以换行符分割。权重为浮点数。</param>
	/// <param name="rules">输出。包含解析出的Rule和权重。</param>
	void ParseRuleGMLFileB(const std::string& filePath, const std::string& filePathWeight, std::vector<std::pair<ggl::Rule, float>>& rules);

	ggl::Graph ParseGraphGML(const std::string& gmlGraph);
	ggl::Graph ParseGraphGMLFile(const std::string& filePath);
};