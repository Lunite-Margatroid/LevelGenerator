
#include <cassert>

#include <sgm/Graph_Interface.hh>

namespace ggl {


////////////////////////////////////////////////////////////////////////////////


	inline
	LeftSidePattern
	::~LeftSidePattern ()
	{
		if (symmBreakList != NULL) {
			delete symmBreakList;
			symmBreakList = NULL;
		}
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule &
	LeftSidePattern
	::getRule () const
	{
		return rule;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	size_t
	LeftSidePattern
	::getNodeNumber(void) const
	{
		return rule.getLeftSide().nodes.size();
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	std::string
	LeftSidePattern
	::getNodeLabel(const IndexType & i) const
	{
		assert( i < rule.getLeftSide().nodes.size() /* index out of scope */ );
		
		  // get access to the label of node i
		return nodeLabel[ boost::vertex( rule.getLeftSide().nodes.at(i), rule.getCore()) ];
		
	}
	
//////////////////////////////////////////////////////////////////////////////////


	inline
	sgm::PA_OrderCheck
	LeftSidePattern
	::getGraphAutomorphism( ) const
	{
		return getGraphAutomorphismT< sgm::GM_vf2 >( );
	}

////////////////////////////////////////////////////////////////////////////////


	template< class GRAPHMATCHER >
	inline
	sgm::PA_OrderCheck
	LeftSidePattern
	::getGraphAutomorphismT( ) const
	{

		  // create CheckList if not present
		if ( symmBreakList == NULL ) {
			  // get graph automorphisms for the left side pattern 
			sgm::PA_OrderCheck ga_ls
				= sgm::PA_OrderCheck::getGraphAutomorphismT<GRAPHMATCHER>( *this );
			
			  // check if there are automorphisms for the left side pattern
			if (ga_ls.getCheckList().size() > 0) {
				
				  // check for automorphisms of the right side pattern
				ggl::RightSidePattern rs( rule );
				sgm::Pattern rsp(rs);
				  // check if wildcard matching is to be applied
				if (this->getUsedWildcard() != NULL) {
					rsp = sgm::Pattern( rs, *(this->getUsedWildcard()) );
				}
				sgm::PA_OrderCheck ga_rs
					= sgm::PA_OrderCheck::getGraphAutomorphismT<GRAPHMATCHER>( rsp );
				
				  // check if there are automorphisms for the right side pattern
				if (ga_rs.getCheckList().size() > 0) {
					  // generate new order check list
					symmBreakList = new sgm::PA_OrderCheck::CheckList();
					std::back_insert_iterator< sgm::PA_OrderCheck::CheckList >
						inCL(*symmBreakList);
					  // calculate order check intersection 
					  // of left and right side pattern
					std::set_intersection( ga_ls.getCheckList().begin()
											, ga_ls.getCheckList().end()
											, ga_rs.getCheckList().begin()
											, ga_rs.getCheckList().end()
											, inCL );
				} else {
					  // no right side pattern automorphisms --> no checks at all
					symmBreakList = new sgm::PA_OrderCheck::CheckList();
				}
			} else {
				  // no left side pattern automorphisms --> no checks at all
				symmBreakList = new sgm::PA_OrderCheck::CheckList();
			}

		}
		
		  // return new symmetry handler
		return sgm::PA_OrderCheck( *this, *symmBreakList );
	}

	
////////////////////////////////////////////////////////////////////////////////
	
	  // Access to the component labeling of this pattern.
	  // @return the component labeling

	inline
	const sgm::Graph_Interface::CompLabel&
	LeftSidePattern
	::getComponentLabeling( void ) const
	{
		return compLabels;
	}
	
	
////////////////////////////////////////////////////////////////////////////////
	
	
	  // Access to the first index of each component of this pattern.
	  // @return a set of the first index for each component

	inline
	const LeftSidePattern::IndexSet &
	LeftSidePattern
	::getFirstOfEachComponent( void ) const
	{
		return firstOfEachComponent;
	}
	
	
////////////////////////////////////////////////////////////////////////////////
	
	
	  // Access to the first index of each component of this pattern.
	  // @return a set of the first index for each component

	inline
	const sgm::Pattern_Interface::ConstraintVec &
	LeftSidePattern
	::getConstraints( void ) const
	{
		return  rule.getLeftSide().constraints;
	}


////////////////////////////////////////////////////////////////////////////////


	  // Access to the first index of each component of this pattern.
	  // @return a set of the first index for each component

	inline
	const std::string *
	LeftSidePattern
	::getUsedWildcard( void ) const
	{
		  // return wildcard information stored in the rule
		return  rule.getUsedWildcard();
	}


////////////////////////////////////////////////////////////////////////////////


	  // Access to the first index of each component of this pattern.
	  // @return a set of the first index for each component

	inline
	const sgm::Graph_Interface &
	LeftSidePattern
	::getPatternGraph( void ) const
	{
		return  *this;
	}


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


	inline
	LeftSidePattern::
	EdgeDescriptor::
	~EdgeDescriptor()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	const std::string&
	LeftSidePattern::
	EdgeDescriptor::
	getEdgeLabel(void) const {
		return parent.edgeLabel[*cur_edge];
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	bool
	LeftSidePattern::
	EdgeDescriptor::
	operator==(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge == ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	bool
	LeftSidePattern::
	EdgeDescriptor::
	operator!=(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge != ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	bool
	LeftSidePattern::
	EdgeDescriptor::
	operator!=(const sgm::Graph_Interface::EdgeDescriptor& ed ) const
	{
		  // check if type casting possible
		assert(dynamic_cast<const EdgeDescriptor*>(&ed) != NULL);
		  // forward call via typecast
		return this->operator !=( static_cast<const EdgeDescriptor&>(ed) );
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	LeftSidePattern::EdgeDescriptor*
	LeftSidePattern::
	EdgeDescriptor::
	clone() const
	{
		return new EdgeDescriptor( *this );
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	
} // namespace ggl


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace ggl {

////////////////////////////////////////////////////////////////////////////////


	inline
	RightSidePattern
	::RightSidePattern (const Rule& rule_)
	 :	rule(rule_)
		, edgeLabel(boost::get( Rule::EdgeLabelProperty(), rule.getCore() ))
		, nodeLabel(boost::get( Rule::NodeLabelProperty(), rule.getCore() ))
		, nodeRightLabel(boost::get( Rule::NodeRightLabelProperty(), rule.getCore() ))
		, nodeIndex(boost::get( Rule::NodeIndexProperty(), rule.getCore() ))
		, edgeContext(boost::get( Rule::EdgeContextProperty(), rule.getCore() ))
		, nodeContext(boost::get( Rule::NodeContextProperty(), rule.getCore() ))
	{
	}


////////////////////////////////////////////////////////////////////////////////


	inline
	RightSidePattern
	::~RightSidePattern ()
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule &
	RightSidePattern
	::getRule () const
	{
		return rule;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	size_t
	RightSidePattern
	::getNodeNumber(void) const
	{
		return rule.getRightSide().nodes.size();
	}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////


	inline
	RightSidePattern::
	EdgeDescriptor::
	~EdgeDescriptor()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	const std::string&
	RightSidePattern::
	EdgeDescriptor::
	getEdgeLabel(void) const {
		return parent.edgeLabel[*cur_edge];
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	bool
	RightSidePattern::
	EdgeDescriptor::
	operator==(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge == ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	bool
	RightSidePattern::
	EdgeDescriptor::
	operator!=(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge != ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	inline
	bool
	RightSidePattern::
	EdgeDescriptor::
	operator!=(const sgm::Graph_Interface::EdgeDescriptor& ed ) const
	{
		  // check if type casting possible
		assert(dynamic_cast<const EdgeDescriptor*>(&ed) != NULL);
		  // forward call via typecast
		return this->operator !=( static_cast<const EdgeDescriptor&>(ed) );
	}

	//////////////////////////////////////////////////////////////////////////


	inline
	RightSidePattern::EdgeDescriptor*
	RightSidePattern::
	EdgeDescriptor::
	clone() const
	{
		return new EdgeDescriptor( *this );
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
	

} // namespace ggl
