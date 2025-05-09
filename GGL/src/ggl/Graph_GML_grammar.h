
#include <algorithm>
#include <boost/tuple/tuple_io.hpp>

#include <iomanip>
#include <cassert>

namespace ggl {


//##############################################################################


	inline
	Graph_GML_grammar
	::Graph_GML_grammar( Graph& toFill )
	  : g2fill(toFill)
		, nodeLabel(boost::get( PropNodeLabel(), g2fill ))
		, edgeLabel(boost::get( PropEdgeLabel(), g2fill ))
	{
	}

	
//##############################################################################
		


	inline
	std::pair< Graph, int >
	Graph_GML_grammar
    ::parseGraph( const std::string & GML_string )
    {
		 // the graph to fill
    	Graph toFill;
    	
		// create grammar object
		Graph_GML_grammar gml_grammar(toFill);
		
		// parse smiles string into graph while ignoring whitespaces
		NS_BOOSTSPIRIT::parse_info<std::string::const_iterator>
			info = NS_BOOSTSPIRIT::parse( GML_string.begin()
										, GML_string.end()
										, gml_grammar
										, NS_BOOSTSPIRIT::space_p);
	
		// check if parsing was successful
		if (!info.full
				&& (GML_string.find_first_not_of(
							" \t\n",(info.stop-GML_string.begin())) 
						!= std::string::npos) ) 
		{

			  // reset to empty graph
			toFill = Graph();
			  // give parsing error 
			return std::pair<Graph, int>(Graph(toFill)
								, (int)(info.stop-GML_string.begin()));
		}
		
		// return filled graph
		return std::pair<Graph, int>(Graph(toFill), -1);
    }
		
	
//##############################################################################
	

	template <	typename ScannerT >  // definition template arguments
	inline
	Graph_GML_grammar
	::definition< ScannerT >
	::definition(Graph_GML_grammar const& self_)
	  :	self(self_)
	{
		reset_data_structures();
		using namespace NS_BOOSTSPIRIT;
		using namespace phoenix;
		
	      gml
		= keyvalues[phoenix::bind(&definition::create_Graph)(var(*this))]
		;

	      keyvalues
		=  keyvalue
		>> *(keyvalue)
		;
	      
	      keyvalue
		=  (key
		    >> value
		    )[phoenix::bind(&definition::keyValueAction)(var(*this),
								 keyvalue.key,
								 keyvalue.strval,
								 keyvalue.numval,
								 keyvalue.dblval)]
		;

	      key
		= ( lexeme_d[alpha_p >> *(alnum_p)]
		  ) [keyvalue.key = construct_<std::string>(arg1,arg2)]
		;

	      value
		= real
		| integer
		| string
		| list
		;

	      list
		= ch_p('[')[phoenix::bind(&definition::openList)(var(*this),
								 keyvalue.key)]
		>> keyvalues
		>> ch_p(']')[phoenix::bind(&definition::closeList)(var(*this))]
		;
	      
	      integer
		= int_p[keyvalue.numval = arg1]
		;

	      real
		= strict_real_p[keyvalue.dblval = arg1]
		;

	      string
		= (confix_p('"', (*anychar_p), '"')
		   | confix_p("\"&",   (+alpha_p), "\";"))
		[keyvalue.strval = construct_<std::string>(arg1,arg2)]
	      	;
	      
		#ifdef _DEBUG_
		    BOOST_SPIRIT_DEBUG_GRAPH(gml);
		    BOOST_SPIRIT_DEBUG_GRAPH(keyvalues);
		    BOOST_SPIRIT_DEBUG_GRAPH(keyvalue);
		    BOOST_SPIRIT_DEBUG_GRAPH(key);
		    BOOST_SPIRIT_DEBUG_GRAPH(value);
		    BOOST_SPIRIT_DEBUG_GRAPH(list);    
		    BOOST_SPIRIT_DEBUG_GRAPH(integer);
		    BOOST_SPIRIT_DEBUG_GRAPH(real);
		    BOOST_SPIRIT_DEBUG_GRAPH(string);
		#endif

	}
	
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	NS_BOOSTSPIRIT::rule<ScannerT> const&
	Graph_GML_grammar
	::definition< ScannerT >
	::start() const 
	{ 
		return gml; 
	}
	
//##############################################################################
	

	template <	typename ScannerT >  // definition template arguments
	inline
	bool 
	Graph_GML_grammar
	::definition< ScannerT >
	::is_valid_node(node_t& a)
    {
		if (a.get<0>() < 0) 
			return (false);
		return (true);
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool 
	Graph_GML_grammar
	::definition< ScannerT >
    ::is_valid_edge(edge_t& e)
    {
		if (e.get<0>() < 0 || e.get<1>() < 0)
			return (false);
		return (true);
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	std::string 
	Graph_GML_grammar
	::definition< ScannerT >
    ::spacer(int level)
    {
		std::ostringstream s;
		for (int i=0; i<level; ++i ) 
			s << " ";
		return (s.str());
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void 
	Graph_GML_grammar
	::definition< ScannerT >
    ::reset_data_structures(void)
    {
		level = 0;
		keystack = keystack_t();
		boolstack = boolstack_t();
		clear_tmp_node_data();
		clear_tmp_edge_data();
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void 
	Graph_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_node_data(void)
    {
		boost::get<0>(tmp_node) = -1;
		boost::get<1>(tmp_node).clear();
		boost::get<2>(tmp_node).clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_edge_data(void)
    {
		boost::get<0>(tmp_edge) = -1;
		boost::get<1>(tmp_edge) = -1;
		boost::get<2>(tmp_edge).clear();
		boost::get<3>(tmp_edge).clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::dumpvec(void)
    {
		std::copy(	keystack.begin(), keystack.end(),
					std::ostream_iterator<std::string>(std::cerr, " "));
		std::cerr << std::endl;

		std::copy(	boolstack.begin(), boolstack.end(),
					std::ostream_iterator<bool>(std::cerr, " "));
		std::cerr << std::endl;

		Dump();
    }


//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::openList(std::string s)
    {
		if (keys.lookup(s) == LST_VAL) {

			/* memorize key of list-value */
			keystack.push_back(s);
			level++;
			
			if (boolstack.empty()) {
				boolstack.push_back(true);
			} else if (boolstack[boolstack.size()-1] == false) {
			    boolstack.push_back(false);
			} else {
			    boolstack.push_back(true);
			}
		
			/* set context of node|edge to enclosing key */
			for(	keystack_t::reverse_iterator ri=keystack.rbegin();
			    	ri != keystack.rend(); ++ri)
			{
				/* skip unqualified keys for outer context */
				if (keys.lookup(*ri)  != LST_VAL)  continue;
				if (keys.context(*ri) == N_CONTXT) continue;
			  
				/* else */
				boost::get<3>(tmp_edge) = *ri;
				boost::get<2>(tmp_node) = *ri;
		
#ifdef _GML_DEBUG_
				std::cerr << "new context = " << *ri << std::endl;
#endif
				break;
			}
		} else {
			keystack.push_back(s);
			boolstack.push_back(false);
		}

#ifdef _GML_DEBUG_      
		std::cerr << "keystack after push: ";
		dumpvec();
#endif
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::closeList(void)
    {
		std::string s;
		if (keystack.empty()) {
			s = std::string();
		} else {
			s = keystack[keystack.size()-1];
			keystack.pop_back();
			level--;
		}

		if (boolstack[boolstack.size()-1] == true) {
			/* memorize nodes and edges */
			if (s == "node") {
				if (is_valid_node(tmp_node)) {
					nodes.insert(tmp_node);
					clear_tmp_node_data();
				}
			} else if (s == "edge") {
				if ( is_valid_edge(tmp_edge) ) {
					edges.insert(tmp_edge);
					clear_tmp_edge_data();
				}
			}
		}
      
		//clear_tmp_node_data();
		//clear_tmp_edge_data();      
      	boolstack.pop_back();

      	/* set context of node|edge to enclosing key */
      	for(	keystack_t::reverse_iterator ri=keystack.rbegin();
      			ri != keystack.rend(); ++ri)
      	{

      		/* skip unqualified keys for outer context */
      		if (keys.lookup(*ri)  != LST_VAL)  continue;
      		if (keys.context(*ri) == N_CONTXT) continue;

      		/* else */
      		boost::get<3>(tmp_edge) = *ri;
      		boost::get<2>(tmp_node) = *ri;

#ifdef _GML_DEBUG_
      		std::cerr << "new context = " << *ri << std::endl;
#endif
      		break;
      	}	

#ifdef _GML_DEBUG_
      	std::cerr << "keystack after  pop: ";
      	dumpvec();
#endif
      
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
	::create_Graph(void)
	{
		typename nodes_t::iterator n;
		typename edges_t::iterator e;
		

#if HAVE_UNORDERED_MAP > 0
		typedef std::unordered_map<int,size_t> Int2Size_tMap;
#elif HAVE_TR1_UNORDERED_MAP > 0
		typedef std::tr1::unordered_map<int,size_t> Int2Size_tMap;
#elif HAVE_GNU_HASH_MAP > 0
		class hash_int {
		public:

			size_t operator()(const int& v) const
			{
				return (size_t)v;
			}
			     
		};
		typedef __gnu_cxx::hash_map<int,size_t,hash_int> Int2Size_tMap;
#else
		typedef std::map<int,size_t> Int2Size_tMap;
#endif

		Int2Size_tMap id2index;
		Int2Size_tMap::const_iterator nodeIndex1, nodeIndex2;
		size_t nodeCount = 0; 

		for (n = nodes.begin(); n != nodes.end(); ++n) {
			
			  // check if node already known
			nodeIndex1 = id2index.find((*n).get<0>());
			bool indexKnown = nodeIndex1 != id2index.end();
			
			  // access to node --> insert if necessary
			typename Graph::vertex_descriptor newVertex;
			if (indexKnown) {
				  // access to existing vertex
				newVertex = boost::vertex( nodeIndex1->second, self.g2fill);
			} else {
				  // add new vertex
				newVertex = boost::add_vertex( self.g2fill );
				id2index[(*n).get<0>()] = nodeCount;
				nodeCount++;
			}
			
			  // set context and label
			std::string contextString = (std::string)(*n).get<2>();
			std::string label = (std::string)(*n).get<1>();
			  // check if obsolete '"' quotes are present
			if (	label.size() >= 2 
				&& ((*(label.begin()) == '\"' && *(label.rbegin()) =='\"')
					|| (*(label.begin()) == '\'' && *(label.rbegin()) =='\''))
				) 
			{
				label = label.substr(1,label.size()-2);
			}
			
			  // set label
			assert(!indexKnown /* strange second occurrence of this node */);
			self.nodeLabel[newVertex] = label;
			
			reset_data_structures();
		}

		for (e = edges.begin(); e != edges.end(); ++e) {
			
			nodeIndex1 = id2index.find((*e).get<0>());
			assert(nodeIndex1 != id2index.end() /* first node id unknown */);
			nodeIndex2 = id2index.find((*e).get<1>());
			assert(nodeIndex2 != id2index.end() /* second node id unknown */);
			
			  // add new edge
			std::pair< typename Graph::edge_descriptor, bool>
			newEdge = boost::add_edge(	boost::vertex( nodeIndex1->second, self.g2fill )
										, boost::vertex( nodeIndex2->second, self.g2fill )
										, self.g2fill );

			  // set context and label
			std::string contextString = (std::string)(*e).get<3>();
			std::string label = (std::string)(*e).get<2>();
			  // check if obsolete "" or '' quotes are present
			if (	label.size() >= 2 
				&& ((*(label.begin()) == '\"' && *(label.rbegin()) =='\"')
					|| (*(label.begin()) == '\'' && *(label.rbegin()) =='\''))
				) 
			{
				label = label.substr(1,label.size()-2);
			}
			
			  // set label
			self.edgeLabel[newEdge.first] = label;

		}
		nodes.clear();
		edges.clear();
    }
    
//##############################################################################
    

	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::Dump(void)
    {
		typename nodes_t::iterator n;
		typename edges_t::iterator e;

		if (!nodes.empty())
			std::cerr << "nodes:" << std::endl;
		for (n = nodes.begin(); n != nodes.end(); ++n) {
			std::cerr	<< boost::tuples::set_open('[')
		  				<< boost::tuples::set_close(']')
		  				<< boost::tuples::set_delimiter(',')
		  				<< *n
	  					<< std::endl;
		}

		if (!edges.empty())
			std::cerr << "edges:" << std::endl;
		for (e = edges.begin(); e != edges.end(); ++e) {
			std::cerr	<< boost::tuples::set_open('[')
						<< boost::tuples::set_close(']')
				  		<< boost::tuples::set_delimiter(',')
				  		<< *e
			  			<< std::endl;    
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::dumpKeyValues(std::string k, std::string s, int i, double d)
    {
		if ( k.empty() ) {
			return;
		}
		int value = keys.lookup(k);
		switch (value) {
		case INT_VAL:
			std::cerr << k << " <=> " << i << std::endl;
			break;
		case DBL_VAL:
			std::cerr << k << " <=> " << d << std::endl;
			break;
		case STR_VAL:
			std::cerr << k << " <=> " << s << std::endl;
			break;
		case LST_VAL:
			/* std::cerr << k << " is a list-value" << std::endl; */
			break;
		default:
			/* ignore key value pair */
			;
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::memorize_node(void)
    {
		nodes.insert(tmp_node);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::memorize_edge(void)
    {
		edges.insert(tmp_edge);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::set_node_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "id")    boost::get<0>(tmp_node) = i;
		else if (k == "label") boost::get<1>(tmp_node) = s;
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::set_edge_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "source") boost::get<0>(tmp_edge) = i;
     	else if (k == "target") boost::get<1>(tmp_edge) = i;
     	else if (k == "label")  boost::get<2>(tmp_edge) = s;
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Graph_GML_grammar
	::definition< ScannerT >
    ::keyValueAction(std::string k, std::string s, int i, double d)
    {
      	if ( keystack.empty() ) {
      		return;
      	}
    	if (keystack[keystack.size()-1] != "|") {
    		/* key with list value type we want to remember */

    		if ( ! k.empty()) {
    			/* dumpKeyValues(k, s, i, d) */
    	  
    			if (keystack[keystack.size()-1] == "node") {
    				set_node_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "edge") {
    				set_edge_data(k, s, i, d);
    			}
    			/* dumpKeyValues(k, s, i, d) */
    		}
    	}
    }
    
//##############################################################################

} // namespace ggl

