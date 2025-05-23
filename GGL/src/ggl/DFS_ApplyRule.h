

#include "sgm/MR_SymmBreak.hh"

#include "ggl/MR_ApplyRule.hh"

namespace ggl {

	//////////////////////////////////////////////////////////////////////////


	inline
	DFS_ApplyRule
	::DFS_ApplyRule()
	 :	rulePattern()
		, solutionStorage(NULL)
		, visitor(NULL)
		, sgm(NULL)
		, reporter()
		, finalTrace(NULL)
		, currentTrace()
	{
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	DFS_ApplyRule
	::~DFS_ApplyRule()
	{
	}

	//////////////////////////////////////////////////////////////////////////


}  // namespace ggl
