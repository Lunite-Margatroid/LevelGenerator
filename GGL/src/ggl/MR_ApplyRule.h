

#include "sgm/HashMap.hh"
#if HAVE_UNORDERED_MAP > 0
	#include <unordered_map>
#elif HAVE_TR1_UNORDERED_MAP > 0
	#include <tr1/unordered_map>
#elif HAVE_GNU_HASH_MAP > 0
	#include <ext/hash_map>
#else
	#include <map>
#endif

#include <boost/graph/copy.hpp>

#include <iterator>
#include <algorithm>
#include <cassert>



namespace ggl {

////////////////////////////////////////////////////////////////////////////////


	inline
	MR_ApplyRule
	::MR_ApplyRule( Graph_Storage & storage_
					, const bool addEachComponent_ )
	 :	storage(storage_)
	 	, undirectedRule( 
	 			boost::is_same< Rule::CoreGraph::directed_selector
								, boost::undirectedS>::value)
		, addEachComponent(addEachComponent_)
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	MR_ApplyRule
	::~MR_ApplyRule()
	{
	}
	
	
////////////////////////////////////////////////////////////////////////////////

} // namespace ggl

