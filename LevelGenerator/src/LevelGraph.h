#pragma once

#include "LG_Common.h"

#define LG_LEVELGRAPH_DEFAULT_CAPACITY 4
#define LG_DEFAULT_NODE_TYPE 1
#define LG_DEFAULT_EDGE_TYPE 1
#define LG_NULLEDGE 0
#define LG_NULLNODE 0


namespace LG
{
	class LG_DLL_API LevelGraph
	{
	private:
		int m_nNode;		// 节点数量 count of valid nodes
		int m_nCapacity;	// 空间大小 count of nodes including null nodes
		std::vector<int> m_Data;		// 数据指针

		int Expand(int newCapacity);

		void Init();

		int& GetNode(int node);
		int& GetEdge(int preNode, int postNode);
	public:
		LevelGraph();
		LevelGraph(const LevelGraph&) = delete;
		~LevelGraph();
		LevelGraph& operator = (const LevelGraph&) = delete;

		int GetNodeCount() const;
		int GetCapacity() const;

		/// <summary>
		/// Add node to the graph
		/// </summary>
		/// <param name="nodeInfo"> Info of the node. for example, node type </param>
		/// <returns>the index of the node</returns>
		int AddNode(int nodeInfo);

		/// <summary>
		/// Add node to the graph
		/// </summary>
		/// <returns>the index of the node</returns>
		int AddNode();

		/// <summary>
		/// Add Edge to the graph
		/// </summary>
		/// <param name="preNode">Index of the preNode</param>
		/// <param name="postNode">Index of the postNode</param>
		/// <returns>0 if success, -1 if error</returns>
		int AddEdge(int preNode, int postNode);

		/// <summary>
		/// Add Edge to the graph. Throw excption if the Edge has been existing. Call "SetEdge" to set the existing edge.
		/// </summary>
		/// <param name="preNode">Index of the preNode</param>
		/// <param name="postNode">Index of the postNode</param>
		/// <param name="nodeInfo">type of the edge</param>
		/// <returns>0 if success, -1 if error</returns>
		int AddEdge(int preNode, int postNode, int edgeInfo);

		/// <summary>
		/// Set the edge info. Works even if the edge is LG_NULLEDGE. Throw exception if node is LG_NULLNODE.
		/// </summary>
		/// <param name="preNode"></param>
		/// <param name="postNode"></param>
		/// <param name="edgeInfo"></param>
		/// <returns>0 if success</returns>
		int SetEdge(int preNode, int postNode, int edgeInfo);

		/// <summary>
		/// Erase the node and its edge
		/// </summary>
		/// <param name="node">Index of the node</param>
		/// <returns>0 if success, -1 if error , 1 if the node is valid node</returns>
		int EraseNode(int node);

		/// <summary>
		/// Erase Edge of the graph
		/// </summary>
		/// <param name="preNode">Index of preNode</param>
		/// <param name="postNode">Index of postNode</param>
		/// <returns>0 if success, -1 if error</returns>
		int EraseEdge(int preNode, int postNode);


		void PrintGraph(std::string& output) const;


		// TODO
		// void Serialize();
		// void Deserialize();
	};

	
}