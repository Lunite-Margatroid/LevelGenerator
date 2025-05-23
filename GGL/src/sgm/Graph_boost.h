
#include <algorithm>
#include <cassert>

namespace sgm {

////////////////////////////////////////////////////////////////////////////////

	  // Construction of the interface graph.
	  // @param graphs the vector of boost graphs to use as internal data
	  //               structure
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	SGM_GRAPH_BOOST_TYPE
	::Graph_boost(	const GRAPH & graph_)
	 :	graph(graph_)
		, graphSize( countRealNodeNumber(graph) )
		, nodeIndexMap(boost::get( NODE_INDEX_PROPERTY(), graph ))
		, nodeLabelMap(boost::get( NODE_LABEL_PROPERTY(), graph ))
		, edgeLabelMap(boost::get( EDGE_LABEL_PROPERTY(), graph ))
	{
		assert(boost::is_undirected(graph) /*Currently only undirected graphs supported*/);
	}
	
////////////////////////////////////////////////////////////////////////////////
	
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	void
	SGM_GRAPH_BOOST_TYPE
	::indexGraph ( GRAPH & the_graph )
	{
		
		typename GRAPH::vertex_iterator vi, v_end;
		
		typename boost::property_map<GRAPH, NODE_INDEX_PROPERTY>::type 
			indexMap = boost::get(NODE_INDEX_PROPERTY(), the_graph);

		  // fill property map
		boost::tie(vi,v_end) = boost::vertices(the_graph);
		size_t idx = 0;
		while (vi != v_end) {
		    boost::put(indexMap, *vi, idx);
			vi++;
			idx++;
		}
	}
		
////////////////////////////////////////////////////////////////////////////////

	  // Destruction
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	SGM_GRAPH_BOOST_TYPE
	::~Graph_boost()
	{
	}
	
////////////////////////////////////////////////////////////////////////////////

	  // Access to the number of nodes of the graph
	  // @return the overall node number 
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	size_t
	SGM_GRAPH_BOOST_TYPE
	::getNodeNumber(void) const
	{
		return graphSize;
	}
	
////////////////////////////////////////////////////////////////////////////////


	SGM_GRAPH_BOOST_TEMPLATE
	inline
	Graph_Interface::OutEdge_iterator
	SGM_GRAPH_BOOST_TYPE::
	getOutEdgesBegin( const IndexType & i ) const
	{
		assert( i<getNodeNumber() );
		  // get edge iterators for given node
		typename GRAPH::out_edge_iterator start,end;
		boost::tie(start,end) = boost::out_edges( boost::vertex(i,graph), graph);
		  // return according iterator that describes the iteration start
		return OutEdge_iterator( EdgeDescriptor( start, end, *this ) );
	}

////////////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	Graph_Interface::OutEdge_iterator
	SGM_GRAPH_BOOST_TYPE::
	getOutEdgesEnd( const IndexType & i ) const
	{
		assert( i<getNodeNumber() );
		  // get edge iterators for given node
		typename GRAPH::out_edge_iterator end
				= boost::out_edges( boost::vertex(i,graph), graph).second;
		  // return according iterator that only describes the iteration end
		return OutEdge_iterator( EdgeDescriptor( end, end, *this ) );
	}


////////////////////////////////////////////////////////////////////////////////

	  // Access to the label of a specified node
	  // @param i the index of the node of interest
	  // @return a string representation of the node label
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	std::string
	SGM_GRAPH_BOOST_TYPE
	::getNodeLabel(const IndexType & i) const
	{
		  // get label of node i
		return nodeLabelMap[ boost::vertex( i, graph ) ];
		
	}
	

////////////////////////////////////////////////////////////////////////////////
	
	SGM_GRAPH_BOOST_TEMPLATE
	inline
	const GRAPH & 
	SGM_GRAPH_BOOST_TYPE
	::getGraph(void) const
	{
		return graph;
	}


	
////////////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	size_t
	SGM_GRAPH_BOOST_TYPE
	::countRealNodeNumber( const GRAPH & graph )
	{
		size_t nodeNum = 0;
		  // count node number via iteration over all vertices
		typename boost::graph_traits<GRAPH>::vertex_iterator vi, vi_end;
		boost::tie(vi, vi_end) = boost::vertices(graph);
		for (; vi != vi_end; ++vi) {
			nodeNum++;
		}
		return nodeNum;
	}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


	SGM_GRAPH_BOOST_TEMPLATE
	inline
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	EdgeDescriptor(	const typename GRAPH::out_edge_iterator& cur_edge_,
					const typename GRAPH::out_edge_iterator& list_end_,
					const Graph_boost& parent_ )
	 : Graph_Interface::EdgeDescriptor()
		, cur_edge( cur_edge_ )
		, list_end( list_end_ )
		, parent(parent_)
	{
		  // check if no neighbors available
		if (cur_edge != list_end) {
			  // set source node
			from = parent.nodeIndexMap[ boost::source( *cur_edge, parent.graph ) ];
			  // set target node
			to = parent.nodeIndexMap[ boost::target( *cur_edge, parent.graph ) ];
		}
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	~EdgeDescriptor()
	{
	}


	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	const std::string&
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	getEdgeLabel(void) const {
		return parent.edgeLabelMap[*cur_edge];
	}
	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	operator==(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge == ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	operator!=(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge != ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	operator!=(const Graph_Interface::EdgeDescriptor& ed ) const
	{
		  // check if type casting possible
		assert(dynamic_cast<const EdgeDescriptor*>(&ed) != NULL);
		  // forward call via typecast
		return this->operator !=( static_cast<const EdgeDescriptor&>(ed) );
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	typename SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor&
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	operator++()
	{
		if (cur_edge != list_end) {
			  // increase iterator
			++cur_edge;
			  // update data
			  // check if no neighbors available
			if (cur_edge != list_end) {
				  // set target node
				to = parent.nodeIndexMap[ boost::target( *cur_edge, parent.graph ) ];
			}
		}

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOST_TEMPLATE
	inline
	typename SGM_GRAPH_BOOST_TYPE::EdgeDescriptor*
	SGM_GRAPH_BOOST_TYPE::
	EdgeDescriptor::
	clone() const
	{
		return new EdgeDescriptor( *this );
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace sgm

