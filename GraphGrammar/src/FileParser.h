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
	/// ������#�ָ��gml rule�ļ������ļ��������Rule��gml������֮����#�ָ
	/// </summary>
	/// <param name="filePath"> �ļ�·��</param>
	/// <param name="rules"> �����������������Rule��Ȩ�ء�Ȩ��Ĭ��Ϊ1</param>
	void ParseRuleGMLFileB(const std::string& filePath, std::vector<std::pair<ggl::Rule, float>>& rules);

	/// <summary>
	/// ������#�ָ��gml rule�ļ������ļ��������Rule��gml������֮����#�ָ
	/// </summary>
	/// <param name="filePath"> gml�ļ�·��</param>
	/// <param name="filePathWeight">��¼ruleȨ�ص��ı��ļ����Ի��з��ָȨ��Ϊ��������</param>
	/// <param name="rules">�����������������Rule��Ȩ�ء�</param>
	void ParseRuleGMLFileB(const std::string& filePath, const std::string& filePathWeight, std::vector<std::pair<ggl::Rule, float>>& rules);

	ggl::Graph ParseGraphGML(const std::string& gmlGraph);
	ggl::Graph ParseGraphGMLFile(const std::string& filePath);
};