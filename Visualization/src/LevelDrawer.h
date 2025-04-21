#pragma once
class LevelDrawer
{
private:
	int m_nGridWidth;
	int m_nGridHeight;
	int m_nLineWidth;
	int m_nGapWidth;
	int m_nPassageWidth;
	unsigned char m_cBackColor[4];
	unsigned char m_cLineColor[4];
	unsigned char m_cGroundColor[4];

public:
	LevelDrawer();
	void SetGridWidth(int input);
	void SetGridHeight(int input);
	void SetLineWidth(int input);
	void SetGapWidth(int input);
	void SetPassageWidth(int input);
	void SetBackColor(unsigned char * backColor);
	void SetLineColor(unsigned char* lineColor);
	void SetGroundColor(unsigned char* groundColor);

	cv::Mat GridMap2Img(const GridMap& gridMap)const;
};