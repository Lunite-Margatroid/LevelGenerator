
#include <cassert>
#include <algorithm>
#include <climits>

namespace sgm
{
////////////////////////////////////////////////////////////////////////////
	
		
	inline
	SubGraph::~SubGraph()
	{
	}

	
////////////////////////////////////////////////////////////////////////////

	inline
	SubGraph::
	OutEdge_iterator
	SubGraph::
	getOutEdgesBegin(const IndexType & i) const
	{
		assert(i<nodeList.size() /* index i out of bounds */);

		  // get first edge in the source graph
		return OutEdge_iterator(
				EdgeDescriptor(
						fullGraph.getOutEdgesBegin( nodeList[i] )
						, fullGraph.getOutEdgesEnd( nodeList[i] )
						, *this
				) );
	}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraph::
	OutEdge_iterator
	SubGraph::
	getOutEdgesEnd(const IndexType & i) const
	{

		  // return end of according edge iteration
		return OutEdge_iterator(
				EdgeDescriptor(
						fullGraph.getOutEdgesEnd( nodeList[i] )
						, fullGraph.getOutEdgesEnd( nodeList[i] )
						, *this
				) );
	}

////////////////////////////////////////////////////////////////////////////
		
	inline
	size_t
	SubGraph::
	getNodeNumber(void) const
	{
		return nodeList.size();
	}
	
////////////////////////////////////////////////////////////////////////////
		
	
	inline
	std::string
	SubGraph::
	getNodeLabel(const IndexType & i) const
	{
		assert(i<nodeList.size() /* index i out of bounds */);
		
		return fullGraph.getNodeLabel(nodeList[i]);
	}
	
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



	inline
	SubGraph::
	EdgeDescriptor::
	~EdgeDescriptor()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	const std::string&
	SubGraph::
	EdgeDescriptor::getEdgeLabel(void) const {
		return curEdge->getEdgeLabel();
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	bool
	SubGraph::
	EdgeDescriptor::
	operator==(const EdgeDescriptor& ed ) const
	{
		return this->curEdge == ed.curEdge;
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	bool
	SubGraph::
	EdgeDescriptor::
	operator!=(const EdgeDescriptor& ed ) const
	{
		return this->curEdge != ed.curEdge;
	}


	//////////////////////////////////////////////////////////////////////////

	inline
	bool
	SubGraph::
	EdgeDescriptor::
	operator!=(const Graph_Interface::EdgeDescriptor& ed ) const
	{
		  // check if type casting possible
		assert(dynamic_cast<const EdgeDescriptor*>(&ed) != NULL);
		  // forward call via typecast
		return this->operator !=( static_cast<const EdgeDescriptor&>(ed) );
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	SubGraph::EdgeDescriptor*
	SubGraph::
	EdgeDescriptor::
	clone() const
	{
		return new EdgeDescriptor( *this );
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


} // namespace sgm




////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////  SUBGRAPHPATTERN
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

namespace sgm
{
////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const NodeList & nodeList )
	 :	SubGraph( fullGraph, nodeList )
		, Pattern( (const Graph_Interface&)*this )
	{}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const CompLabel & compLabel
						, const size_t subGraphLabel )
	 :	SubGraph( fullGraph, compLabel, subGraphLabel )
		, Pattern( (const Graph_Interface&)*this )
	{}


////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const NodeList & nodeList
						, const ConstraintVec & matchConstraints )
	 :	SubGraph( fullGraph, nodeList )
		, Pattern( (const Graph_Interface&)*this, matchConstraints )
	{
		remapConstraints(matchConstraints, this->full2sub, this->matchConstraints );
	}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const CompLabel & compLabel
						, const size_t subGraphLabel
						, const ConstraintVec & matchConstraints )
	 :	SubGraph( fullGraph, compLabel, subGraphLabel )
		, Pattern( (const Graph_Interface&)*this, matchConstraints )
	{
		remapConstraints(matchConstraints, this->full2sub, this->matchConstraints );
	}

////////////////////////////////////////////////////////////////////////////


	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const NodeList & nodeList
						, const std::string &  wildcardToUse )
	 :	SubGraph( fullGraph, nodeList )
		, Pattern( (const Graph_Interface&)*this, wildcardToUse )
	{}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const CompLabel & compLabel
						, const size_t subGraphLabel
						, const std::string &  wildcardToUse )
	 :	SubGraph( fullGraph, compLabel, subGraphLabel )
		, Pattern( (const Graph_Interface&)*this, wildcardToUse )
	{}


////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const NodeList & nodeList
						, const ConstraintVec & matchConstraints
						, const std::string &  wildcardToUse )
	 :	SubGraph( fullGraph, nodeList )
		, Pattern( (const Graph_Interface&)*this, matchConstraints, wildcardToUse )
	{
		remapConstraints(matchConstraints, this->full2sub, this->matchConstraints );
	}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	SubGraphPattern(	const Graph_Interface & fullGraph
						, const CompLabel & compLabel
						, const size_t subGraphLabel
						, const ConstraintVec & matchConstraints
						, const std::string &  wildcardToUse )
	 :	SubGraph( fullGraph, compLabel, subGraphLabel )
		, Pattern( (const Graph_Interface&)*this, matchConstraints, wildcardToUse )
	{
		remapConstraints(matchConstraints, this->full2sub, this->matchConstraints );
	}

////////////////////////////////////////////////////////////////////////////

	inline
	SubGraphPattern::
	~SubGraphPattern()
	{}


////////////////////////////////////////////////////////////////////////////
} // namespace sgm
