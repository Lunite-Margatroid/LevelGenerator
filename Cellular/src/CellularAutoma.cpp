#include "CellularAutoma.h"



void CellularAutoma::Step()
{
}

void CellularAutoma::GenOutput(const std::string& beginLabel /*= "e"*/)
{
	// ��ö�������
	int nNode = m_GI.getNodeNumber();

	// ��ʼ�����ʱ�ǩ
	std::vector<bool> flag;
	flag.resize(nNode);
	std::fill(flag.begin(), flag.end(), false);

	// ��ʼ���������
	while(!m_que.empty())
		m_que.pop();

	// ��ȡ��ʼ�ڵ�
	int beginIndex = 0;
	for (int i = 0; i < nNode; i++)
	{// �����ڵ� �ҵ���ʼ��ǩ ���û�� ʹ��0�Žڵ�Ϊ��ʼ�ڵ�
		if (m_GI.getNodeLabel(i) == beginLabel)
		{
			beginIndex = i;
			break;
		}
	}
	// �����ʼ�ڵ�
	m_que.push(std::make_pair(-1, beginIndex));	// ��ʼ�ڵ�û��ǰ�ýڵ� ��Ϊ-1
	flag[beginIndex] = true;
	// ������ȱ�ǩ�ڵ�
	m_que.push(std::make_pair(-1, -1));
	int nDepth = 0;

	// ����
	while (!m_que.empty())
	{
		// ��õ�ǰ�ڵ㼰��ǰ�ýڵ�
		int curPreNode = m_que.front().first;
		int curNode = m_que.front().second;
		m_que.pop();

		if (curNode >= 0)
		{// �ýڵ㲻����ȱ�־
			m_output.push(NodeInfo(curNode, curPreNode, nDepth, beginLabel));
			// �������ڽڵ�
			for (auto iter = m_GI.getOutEdgesBegin(curNode); iter != m_GI.getOutEdgesEnd(curNode); iter++)
			{
				// ��ú��ýڵ�
				int postNode = iter->getToIndex();
				if (!flag[postNode])
				{// �ýڵ�û�з��ʹ�
					// ���
					m_que.push(std::make_pair(curNode, postNode));
					flag[postNode = true];
				}
			}
		}
		else
		{// �ýڵ�����ȱ�־
			nDepth++;	// ���++
			if (!m_que.empty())
			{// ������в��ǿյ� �����µ���ȱ�־
				m_que.push(std::make_pair(-1, -1));
			}
		}
	}
}

CellularAutoma::CellularAutoma(const sgm::Graph_boost<ggl::Graph>& gi)
:m_GI(gi)
{
}

void CellularAutoma::Generate(const std::string& beginLabel)
{
}



