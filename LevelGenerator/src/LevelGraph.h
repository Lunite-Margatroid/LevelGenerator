#pragma once
#ifdef LG_DLL_EXPORTS
	#define LG_DLL_API __declspec(dllexport)
#else
	#define LG_DLL_API __declspec(dllimport)
#endif // LG_DLL_EXPORTS

#define LEVELGRAPH_DEFAULT_CAPACITY 4

namespace LG
{

	extern "C" LG_DLL_API int add(int a, int b);
	class LG_DLL_API LevelGraph
	{
	private:
		int m_nNode;
		int m_nCapacity;
	public:
		LevelGraph();
		LevelGraph(const LevelGraph&) = delete;
		~LevelGraph();
		LevelGraph& operator = (const LevelGraph&) = delete;

		int GetNodeCount() const;
		int GetCapacity() const;
	};
}