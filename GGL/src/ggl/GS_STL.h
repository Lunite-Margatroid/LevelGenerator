
#include "sgm/Pattern.hh"

namespace ggl {

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLT_TEMPLATE
	inline
	GGL_GS_STL_PUSHALLT_TYPE
	::GS_STL_pushAllT( STL_CONTAINER & storage_ )
	 :	storage(storage_)
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLT_TEMPLATE
	inline
	GGL_GS_STL_PUSHALLT_TYPE
	::~GS_STL_pushAllT()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLT_TEMPLATE
	inline
	void
	GGL_GS_STL_PUSHALLT_TYPE
	::add( const Graph & graph )
	{
		  // add the graph to the STL container
		storage.push_back(graph);
	}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

} // namespace ggl





namespace ggl {

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHALLPT_TYPE
	::GS_STL_pushAllPT( STL_CONTAINER & storage_ )
	 :	storage(storage_)
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHALLPT_TYPE
	::~GS_STL_pushAllPT()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHALLPT_TEMPLATE
	inline
	void
	GGL_GS_STL_PUSHALLPT_TYPE
	::add( const Graph & graph )
	{
		  // add the graph to the STL container
		storage.push_back( new Graph(graph) );
	}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

} // namespace ggl




#include "sgm/MR_Counting.hh"
#include "ggl/Graph.hh"

namespace ggl {

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUET_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUET_TYPE
	::GS_STL_pushUniqueT(	STL_CONTAINER & storage_
							, sgm::GraphMatching& matcher_ )
	 :	storage(storage_)
	 	, matcher(matcher_)
		, wildcard(NULL)
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUET_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUET_TYPE
	::GS_STL_pushUniqueT(	STL_CONTAINER & storage_
							, sgm::GraphMatching& matcher_
							, const std::string& wildcard_ )
	 :	storage(storage_)
	 	, matcher(matcher_)
		, wildcard(new std::string(wildcard_))
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUET_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUET_TYPE
	::GS_STL_pushUniqueT(	const GGL_GS_STL_PUSHUNIQUET_TYPE &toCopy )
	 :	storage(toCopy.storage)
	 	, matcher(toCopy.matcher)
		, wildcard( toCopy.wildcard != NULL ? new std::string(*(toCopy.wildcard)) : NULL)
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUET_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUET_TYPE
	::~GS_STL_pushUniqueT()
	{
		if (wildcard != NULL)
			delete wildcard;
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUET_TEMPLATE
	inline
	void
	GGL_GS_STL_PUSHUNIQUET_TYPE
	::add( const Graph & graph )
	{
		bool add2storage = true;
								
		Graph_boost patternGraph( graph );
		size_t patternSize = patternGraph.getNodeNumber();
		sgm::Pattern pattern( patternGraph );
		if (wildcard != NULL) {
			pattern = sgm::Pattern( patternGraph, *wildcard );
		}
		
		sgm::MR_Counting matchCount;
		
		for (	typename STL_CONTAINER::const_iterator it = storage.begin();
				add2storage && it != storage.end(); ++it )
		{
			  // check if equal number of nodes
			if (patternSize == boost::num_vertices(*it)) {
				  // create target graph wrapper
				Graph_boost target( *it );
				  // reset counter match reporter
				matchCount.resetHits();
				  // find a match if any
				matcher.findMatches( pattern, target, matchCount, 1 );
				  // check if graph equals to storage[it]
				add2storage = (matchCount.getHits() == 0);
			}
		}
		
		if (add2storage) {
			  // add the graph to the STL container
			storage.push_back(graph);
		}
	}

////////////////////////////////////////////////////////////////////////////////

} // namespace ggl


#include "sgm/MR_Counting.hh"

namespace ggl {

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUEPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUEPT_TYPE
	::GS_STL_pushUniquePT(	STL_CONTAINER & storage_
							, sgm::GraphMatching& matcher_ )
	 :	storage(storage_)
	 	, matcher(matcher_)
		, wildcard(NULL)
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUEPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUEPT_TYPE
	::GS_STL_pushUniquePT(	STL_CONTAINER & storage_
							, sgm::GraphMatching& matcher_
							, const std::string& wildcard_ )
	 :	storage(storage_)
	 	, matcher(matcher_)
		, wildcard(new std::string(wildcard_))
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUEPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUEPT_TYPE
	::~GS_STL_pushUniquePT()
	{
		if( wildcard != NULL )
			delete wildcard;
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUEPT_TEMPLATE
	inline
	GGL_GS_STL_PUSHUNIQUEPT_TYPE
	::GS_STL_pushUniquePT(	const GGL_GS_STL_PUSHUNIQUEPT_TYPE &toCopy )
	{
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_GS_STL_PUSHUNIQUEPT_TEMPLATE
	inline
	void
	GGL_GS_STL_PUSHUNIQUEPT_TYPE
	::add( const Graph & graph )
	{
		bool add2storage = true;
		
		Graph_boost patternGraph( graph );
		size_t patternSize = patternGraph.getNodeNumber();
		sgm::Pattern pattern( patternGraph );
		if (wildcard != NULL) {
			pattern = sgm::Pattern( patternGraph, *wildcard );
		}
		
		sgm::MR_Counting matchCount;
		
		for (	typename STL_CONTAINER::const_iterator it = storage.begin();
				add2storage && it != storage.end(); ++it )
		{
			  // check if equal number of nodes
			if (patternSize == boost::num_vertices(**it)) {
				  // create target graph wrapper
				Graph_boost target( **it );
				  // reset counter match reporter
				matchCount.resetHits();
				  // find a match if any
				matcher.findMatches( pattern, target, matchCount, 1 );
				  // check if graph equals to storage[it]
				add2storage = (matchCount.getHits() == 0);
			}
		}
		
		if (add2storage) {
			  // add a new allocated copy of the graph to the STL container
			storage.push_back( new Graph(graph) );
		}
	}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

} // namespace ggl

