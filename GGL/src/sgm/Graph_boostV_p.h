
#include <algorithm>
#include <cassert>

#include "sgm/Graph_boost.hh"

namespace sgm {

////////////////////////////////////////////////////////////////////////////////

	  // Construction of the interface graph.
	  // @param graphs the vector of boost graphs to use as internal data
	  //               structure
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	SGM_GRAPH_BOOSTV_P_TYPE
	::Graph_boostV_p(	const std::vector< const GRAPH* > & graphs_)
	 :	graphs(graphs_), graphSize(graphs.size()+1, 0)
	{
		for (size_t i=0; i<graphs.size(); ++i) {
			assert(graphs[i] != NULL /*no graph present*/);
			assert(boost::is_undirected(*(graphs[i])) /*Currently only undirected graphs supported*/);
			graphSize[i+1] = graphSize[i]
						   + SGM_GRAPH_BOOST_TYPE::countRealNodeNumber(*(graphs[i]));
		}
	}
	
////////////////////////////////////////////////////////////////////////////////
	
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	void
	SGM_GRAPH_BOOSTV_P_TYPE
	::indexGraphs ( std::vector<GRAPH*> & the_graphs )
	{
		typedef typename boost::property_map<GRAPH, NODE_INDEX_PROPERTY>::type IndexMap; 
		
		typename GRAPH::vertex_iterator vi, v_end;
		
		  // fill property maps
		for (size_t i=0; i<the_graphs.size(); ++i) {
			IndexMap indexMap = boost::get(NODE_INDEX_PROPERTY(), *(the_graphs[i]));
			boost::tie(vi,v_end) = boost::vertices(*(the_graphs[i]));
			size_t idx = 0;
			while (vi != v_end) {
			    boost::put(indexMap, *vi, idx);
				vi++;
				idx++;
			}
		}
	}
		
////////////////////////////////////////////////////////////////////////////////

	  // Destruction
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	SGM_GRAPH_BOOSTV_P_TYPE
	::~Graph_boostV_p()
	{
		graphSize.clear();
	}
	
////////////////////////////////////////////////////////////////////////////////

	  // Access to the number of nodes of the graph
	  // @return the overall node number 
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	size_t
	SGM_GRAPH_BOOSTV_P_TYPE
	::getNodeNumber(void) const
	{
		return *(graphSize.rbegin());
	}
	

////////////////////////////////////////////////////////////////////////////////

	  // Access to the label of a specified node
	  // @param i the index of the node of interest
	  // @return a string representation of the node label
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	std::string
	SGM_GRAPH_BOOSTV_P_TYPE
	::getNodeLabel(const IndexType & i) const
	{
		  // get local node information
		LocalIndex idx = getLocalIndex( i );
		
		  // get access to the node i
		typename GRAPH::vertex_descriptor nodeDescr 
			= boost::vertex( idx.second, *(graphs.at(idx.first)));
		
		  // get label property class
		typename boost::property_map<GRAPH, NODE_LABEL_PROPERTY>::const_type 
			labelMap = boost::get( NODE_LABEL_PROPERTY(), (*(graphs.at(idx.first))) );
		
		return labelMap[nodeDescr];
		
	}
	
////////////////////////////////////////////////////////////////////////////////
	
	  // Access to the local index in graphs of the virtual global node i
	  // @param i index of the global node of intrest
	  // @return the local index of i in graphs
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	std::pair< size_t, size_t >
	SGM_GRAPH_BOOSTV_P_TYPE
	::getLocalIndex( const IndexType & i ) const
	{
		 // check for range
		assert( i < *(graphSize.rbegin()));
		
		 // short access if only one graph in the list
		if (graphs.size() == 1)
			return LocalIndex(0,i);
		
		 // find local graph that contains node i
		std::vector< size_t >::const_iterator g_it = 
			std::lower_bound(	graphSize.begin(),
								graphSize.end(),
								(size_t)i+1 );
		 // get the index in graphs
		size_t g = g_it - graphSize.begin() - 1;
		 // get the local node index
		size_t n = (size_t)i - graphSize.at(g);
		
		return LocalIndex(g,n);
	}
		
////////////////////////////////////////////////////////////////////////////////
	
	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	const std::vector< const GRAPH* > & 
	SGM_GRAPH_BOOSTV_P_TYPE
	::getGraphs(void) const
	{
		return graphs;
	}


////////////////////////////////////////////////////////////////////////////////


	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	Graph_Interface::OutEdge_iterator
	SGM_GRAPH_BOOSTV_P_TYPE::
	getOutEdgesBegin( const IndexType & i ) const
	{
		assert( i<getNodeNumber() );

		  // get local node information
		LocalIndex idx = getLocalIndex( i );

		  // map data to local graph
		const GRAPH& graph = *(graphs.at(idx.first));
		size_t index_shift = graphSize.at(idx.first);

		  // get edge iterators for given node
		typename GRAPH::out_edge_iterator start,end;
		boost::tie(start,end) = boost::out_edges( boost::vertex(idx.second,graph), graph);
		  // return according iterator that describes the iteration start
		return OutEdge_iterator( EdgeDescriptor( start, end, graph, index_shift ));
	}

////////////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	Graph_Interface::OutEdge_iterator
	SGM_GRAPH_BOOSTV_P_TYPE::
	getOutEdgesEnd( const IndexType & i ) const
	{
		assert( i<getNodeNumber() );

		  // get local node information
		LocalIndex idx = getLocalIndex( i );

		  // map data to local graph
		const GRAPH& graph = *(graphs.at(idx.first));
		size_t index_shift = graphSize.at(idx.first);

		  // get edge iterators for given node
		typename GRAPH::out_edge_iterator end
			= boost::out_edges( boost::vertex(idx.second,graph), graph).second;
		  // return according iterator that only describes the iteration end
		return OutEdge_iterator( EdgeDescriptor( end, end, graph, index_shift ) );
	}





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	EdgeDescriptor(	const typename GRAPH::out_edge_iterator& cur_edge_,
					const typename GRAPH::out_edge_iterator& list_end_,
					const GRAPH& graph_,
					const size_t nodeIndexShift_
					)
	 : Graph_Interface::EdgeDescriptor()
		, cur_edge( cur_edge_ )
		, list_end( list_end_ )
		, graph(graph_)
		, nodeIndexShift(nodeIndexShift_)
		, nodeIndexMap( boost::get( NODE_INDEX_PROPERTY(), graph ))
		, edgeLabelMap( boost::get( EDGE_LABEL_PROPERTY(), graph ))
	{
		  // check if no neighbors available
		if (cur_edge != list_end) {
			  // set source node
			from = nodeIndexShift + nodeIndexMap[ boost::source( *cur_edge, graph ) ];
			  // set target node
			to = nodeIndexShift + nodeIndexMap[ boost::target( *cur_edge, graph ) ];
		}
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	~EdgeDescriptor()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	operator==(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge == ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	operator!=(const EdgeDescriptor& ed ) const
	{
		return this->cur_edge != ed.cur_edge;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	bool
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	operator!=(const Graph_Interface::EdgeDescriptor& ed ) const
	{
		  // check if type casting possible
		assert(dynamic_cast<const EdgeDescriptor*>(&ed) != NULL);
		  // forward call via typecast
		return this->operator !=( static_cast<const EdgeDescriptor&>(ed) );
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	typename SGM_GRAPH_BOOSTV_P_TYPE::EdgeDescriptor&
	SGM_GRAPH_BOOSTV_P_TYPE::
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
				to = nodeIndexShift + nodeIndexMap[ boost::target( *cur_edge, graph ) ];
			}

		}

		return *this;
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	typename SGM_GRAPH_BOOSTV_P_TYPE::EdgeDescriptor*
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::
	clone() const
	{
		return new EdgeDescriptor( *this );
	}

	//////////////////////////////////////////////////////////////////////////

	SGM_GRAPH_BOOSTV_P_TEMPLATE
	inline
	const std::string&
	SGM_GRAPH_BOOSTV_P_TYPE::
	EdgeDescriptor::getEdgeLabel(void) const {
		return edgeLabelMap[*cur_edge];;
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
	
////////////////////////////////////////////////////////////////////////////////

} // namespace sgm
