/*
  Last changed Time-stamp: <2009-06-26 13:15:55 xtof>
  $Id: Rule_GML_grammar.icc,v 1.36 2015/04/30 09:38:27 mmann Exp $
*/
#include <algorithm>
#include <boost/tuple/tuple_io.hpp>
#include <boost/lexical_cast.hpp>

#include "ggl/Graph.hh"
#include <iostream>
#include <iomanip>

//#define _GML_DEBUG_

namespace ggl {


//##############################################################################


	inline
	Rule_GML_grammar
	::Rule_GML_grammar( Rule::CoreGraph& toFill
							, std::string & ruleID_
							, std::vector< sgm::Pattern_Interface::Match_Constraint* > & ruleConstraints_
							, Rule::CopyAndPasteOperations & copyAndPaste_
							, std::string & wildcard_ )
	  : g2fill(toFill)
	  	, ruleID(ruleID_)
		, ruleConstraints(ruleConstraints_)
		, copyAndPaste(copyAndPaste_)
		, wildcard(wildcard_)
		, nodeLabel(boost::get( Rule::NodeLabelProperty(), g2fill ))
		, nodeLabelRight(boost::get( Rule::NodeRightLabelProperty(), g2fill ))
		, nodeContext(boost::get( Rule::NodeContextProperty(), g2fill ))
		, edgeLabel(boost::get( Rule::EdgeLabelProperty(), g2fill ))
		, edgeContext(boost::get( Rule::EdgeContextProperty(), g2fill ))
	{
	}

	
//##############################################################################
		


	inline
	std::string
	Rule_GML_grammar
    ::trimQuotes( const std::string & s )
    {
		size_t from = 0;
		size_t length = s.size();
		if (	s.size() >= 2
			&& ((*(s.begin()) == '\"' && *(s.rbegin()) =='\"')
				|| (*(s.begin()) == '\'' && *(s.rbegin()) =='\''))
			)
		{
			from = 1;
			length = s.size()-2;
		} else
		if ( s.size() >= 4
			&& (s.substr(0,2) == "\"&")
			&& (s.substr(s.size()-2,2) == "\";") )
		{
			from = 2;
			length = s.size()-4;
		}
		return s.substr(from,length);
    }
//##############################################################################



	inline
	std::pair< Rule, int >
	Rule_GML_grammar
    ::parseRule( const std::string & GML_string ) throw (Rule_GML_error)
    {
		 // the graph to fill
    	Rule::CoreGraph toFill;
    	 // the rule ID to set
    	std::string ruleID;
    	 // the rule constraints to fill
    	std::vector< sgm::Pattern_Interface::Match_Constraint* > ruleConstr;
    	 // the CnP operation container to fill
    	Rule::CopyAndPasteOperations copyAndPaste;
    	 // the wildcard to set
    	std::string wildcard = "#NOT-SET#";
    	
		// create grammar object
    	Rule_GML_grammar gml_grammar(toFill, ruleID, ruleConstr, copyAndPaste, wildcard );
		
    	NS_BOOSTSPIRIT::parse_info<std::string::const_iterator> info;
		try {
			// parse GML string into temporary data structures ignoring whitespaces
			info = NS_BOOSTSPIRIT::parse( GML_string.begin()
											, GML_string.end()
											, gml_grammar
											, NS_BOOSTSPIRIT::space_p);
		} catch (ggl::Rule_GML_error &ex) {
			  // delete all constraints parsed for this rule
			for (std::vector< sgm::Pattern_Interface::Match_Constraint * >::iterator rC = ruleConstr.begin();
					rC != ruleConstr.end(); ++rC)
			{
				delete (*rC);
			}
			std::cerr <<" exception raised : '" <<ex.what() <<"'\n";
			  // throw new error to forward the exception,
			  // the CATCH was only needed for garbage collection of ruleConstr
			throw Rule_GML_error( ex.what() );
		}
		  // assume successful parsing
		int returnValue = -1;

//	std::cerr <<" parsing done : info.full = " <<(info.full?"true":"false")<<"\n";

		// check if parsing was successful
		if (!info.full
				&& (GML_string.find_first_not_of(
							" \t\n",(info.stop-GML_string.begin())) 
						!= std::string::npos) ) 
		{
//	std::cerr <<" error case \n";
			  // reset to empty graph
			toFill = Rule::CoreGraph();
			  // note parsing error
			returnValue = (int)(info.stop-GML_string.begin());
		}
		
		  // create new rule
		Rule rule(toFill,ruleID, ruleConstr, copyAndPaste);
		  // set wildcard if parsed
		if (wildcard.compare("#NOT-SET#") != 0) {
			rule.setUsedWildcard(&wildcard);
		}

		  // delete all constraints parsed for this rule
		for (std::vector< sgm::Pattern_Interface::Match_Constraint * >::iterator rC = ruleConstr.begin();
				rC != ruleConstr.end(); ++rC)
		{
			delete (*rC);
		}
		ruleConstr.clear();

		// return filled graph
//	std::cerr <<" return \n";
		return std::pair<Rule, int>(rule, returnValue);
    }
		
	
//##############################################################################
	

	template <	typename ScannerT >  // definition template arguments
	inline
	Rule_GML_grammar
	::definition< ScannerT >
	::definition(Rule_GML_grammar const& self_)
	  :	self(self_)
	{
		reset_data_structures();
		using namespace NS_BOOSTSPIRIT;
		using namespace phoenix;
		
	      gml
		= keyvalues[phoenix::bind(&definition::create_Rule)(var(*this))]
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
		| relop
		| list
		;

	      list
		=	// list with entries
			(ch_p('[')[phoenix::bind(&definition::openList)(var(*this),keyvalue.key)]
				>> keyvalues
				>> ch_p(']')[phoenix::bind(&definition::closeList)(var(*this))] )
			// empty list
			| (ch_p('[')[phoenix::bind(&definition::openList)(var(*this),keyvalue.key)]
				>> ch_p(']')[phoenix::bind(&definition::closeList)(var(*this))])
		;
	      
	      integer
		= int_p[keyvalue.numval = arg1]
		;

	      real
		= strict_real_p[keyvalue.dblval = arg1]
		;

	      relop
	    = (str_p("=") | str_p("<") | str_p(">") | str_p("!"))[keyvalue.strval = construct_<std::string>(arg1,arg2)]
	    ;

	      string
		= (confix_p('"', (*anychar_p), '"')
		   | confix_p('\'', (*anychar_p), '\'')
		   | confix_p("\"&",   (+alpha_p), "\";"))
		[keyvalue.strval = construct_<std::string>(arg1,arg2)]
	      	;
	      
		#ifdef _DEBUG_
		    BOOST_SPIRIT_DEBUG_RULE(gml);
		    BOOST_SPIRIT_DEBUG_RULE(keyvalues);
		    BOOST_SPIRIT_DEBUG_RULE(keyvalue);
		    BOOST_SPIRIT_DEBUG_RULE(key);
		    BOOST_SPIRIT_DEBUG_RULE(value);
		    BOOST_SPIRIT_DEBUG_RULE(list);    
		    BOOST_SPIRIT_DEBUG_RULE(integer);
		    BOOST_SPIRIT_DEBUG_RULE(real);
		    BOOST_SPIRIT_DEBUG_RULE(string);
		#endif


	}
	

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	NS_BOOSTSPIRIT::rule<ScannerT> const&
	Rule_GML_grammar
	::definition< ScannerT >
	::start() const 
	{ 
		return gml; 
	}
	
//##############################################################################
	

	template <	typename ScannerT >  // definition template arguments
	inline
	bool 
	Rule_GML_grammar
	::definition< ScannerT >
	::is_valid_node(const node_t& a)
    {
		  // check if ID is at least 0
		if (a.get<0>() < 0) {
			throw Rule_GML_error("node ID '"
					+ boost::lexical_cast<std::string>(a.get<0>())
					+ "' is less than zero");
			return (false);
		}

		return (true);
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool 
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_edge(const edge_t& e)
    {
		  // check if node IDs are at least zero
		if ( e.get<0>()<0 || e.get<1>()<0 ) {
			throw Rule_GML_error("edge "
					+ boost::lexical_cast<std::string>(e.get<0>())
					+" --> "
					+ boost::lexical_cast<std::string>(e.get<1>())
					+ ": node ID is less than zero");
			return false;
		}

		return (true);
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_MC_NodeAdjacency(const sgm::MC_NodeAdjacency& c)
    {
		  // check if node ID set
		if (c.constrainedNodeID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainAdj without specified 'id' found");
			return false;
		}
		  // check if count was set
		if (c.count == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainAdj without specified 'count' found");
			return false;
		}
//		  // check if either edge or node labels was set
//		if (c.edgeLabels.empty() && c.nodeLabels.empty()) {
//			throw Rule_GML_error("constrainAdj without specified 'edgeLabels' nor 'nodeLabels' found");
//			return false;
//		}
		return (true);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_MC_NodeLabel(const sgm::MC_NodeLabel& c)
    {
		  // check if node ID set
		if (c.constrainedNodeID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainNode without specified 'id' found");
			return false;
		}
		  // check if count was set
		if (c.nodeLabels.empty()) {
			throw Rule_GML_error("constrainNode without specified 'nodeLabels' found");
			return false;
		}
		return (true);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_MC_EdgeLabel(const sgm::MC_EdgeLabel& c)
    {
		  // check if node ID set
		if (c.constrainedFromID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainEdge without specified 'source' found");
			return false;
		}
		if (c.constrainedToID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainEdge without specified 'target' found");
			return false;
		}
		  // check if count was set
		if (c.edgeLabels.empty()) {
			throw Rule_GML_error("constrainEdge without specified 'edgeLabels' found");
			return false;
		}
		return (true);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_MC_NoEdge(const sgm::MC_NoEdge& c)
    {
		  // check if node ID set
		if (c.constrainedFromID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainNoEdge without specified 'source' found");
			return false;
		}
		if (c.constrainedToID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("constrainNoEdge without specified 'target' found");
			return false;
		}
		return (true);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	bool
	Rule_GML_grammar
	::definition< ScannerT >
    ::is_valid_copyAndPaste(const Rule::RuleCnP & cnp)
    {
		  // check if node ID set
		if (cnp.source == ((size_t)INT_MAX)) {
			throw Rule_GML_error("copyAndPaste without specified 'source' found");
			return false;
		}
		if (cnp.pasteID == ((size_t)INT_MAX)) {
			throw Rule_GML_error("copyAndPaste without specified 'id' found");
			return false;
		}
		if (cnp.source == cnp.pasteID) {
			throw Rule_GML_error("copyAndPaste with equal 'source' and 'id' found");
			return false;
		}
		return (true);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	std::string 
	Rule_GML_grammar
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
	Rule_GML_grammar
	::definition< ScannerT >
    ::reset_data_structures(void)
    {
		level = 0;
		tmp_ruleID = std::string("#NOT-SET#");
		tmp_wildcard = std::string("#NOT-SET#");
		keystack = keystack_t();
		boolstack = boolstack_t();
		clear_tmp_node_data();
		clear_tmp_edge_data();
		clear_tmp_MC_NodeAdjacency();
		clear_tmp_MC_NodeLabel();
		clear_tmp_MC_NoEdge();
		clear_tmp_MC_EdgeLabel();
		clear_tmp_copyAndPaste();
    }
    
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void 
	Rule_GML_grammar
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
	Rule_GML_grammar
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
	Rule_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_MC_NodeAdjacency(void)
    {
//std::cerr <<"\n ## CLEAR RULE ##"
//		<<"\n source     = " <<tmp_MC_NodeAdjacency.constrainedNodeID
//		<<"\n op         = " <<(tmp_MC_NodeAdjacency.op == sgm::MC_NodeAdjacency::MC_EQ?"'='":(tmp_MC_NodeAdjacency.op == sgm::MC_NodeAdjacency::MC_L?"'<'":(tmp_MC_NodeAdjacency.op == sgm::MC_NodeAdjacency::MC_G?"'>'":"??")))
//		<<"\n count      = " <<tmp_MC_NodeAdjacency.count
//		<<"\n nodeLabels =";
//for (std::set<std::string>::const_iterator it=tmp_MC_NodeAdjacency.nodeLabels.begin(); it!=tmp_MC_NodeAdjacency.nodeLabels.end(); ++it )
//	std::cerr <<" '" <<*it <<"'";
//std::cerr <<"\n edgeLabels =";
//for (std::set<std::string>::const_iterator it=tmp_MC_NodeAdjacency.edgeLabels.begin(); it!=tmp_MC_NodeAdjacency.edgeLabels.end(); ++it )
//	std::cerr <<" '" <<*it <<"'";
//std::cerr <<"\n";
		tmp_MC_NodeAdjacency.constrainedNodeID = ((size_t)INT_MAX);
		tmp_MC_NodeAdjacency.op = sgm::MC_NodeAdjacency::MC_EQ;
		tmp_MC_NodeAdjacency.count = ((size_t)INT_MAX);
		tmp_MC_NodeAdjacency.nodeLabels.clear();
		tmp_MC_NodeAdjacency.edgeLabels.clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_MC_NodeLabel(void)
    {
		tmp_MC_NodeLabel.constrainedNodeID = ((size_t)INT_MAX);
		tmp_MC_NodeLabel.compareType = sgm::MC_NodeLabel::ALLOWED;
		tmp_MC_NodeLabel.nodeLabels.clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_MC_EdgeLabel(void)
    {
		tmp_MC_EdgeLabel.constrainedFromID = ((size_t)INT_MAX);
		tmp_MC_EdgeLabel.constrainedToID = ((size_t)INT_MAX);
		tmp_MC_EdgeLabel.compareType = sgm::MC_EdgeLabel::ALLOWED;
		tmp_MC_EdgeLabel.edgeLabels.clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_MC_NoEdge(void)
    {
		tmp_MC_NoEdge.constrainedFromID = ((size_t)INT_MAX);
		tmp_MC_NoEdge.constrainedToID = ((size_t)INT_MAX);
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::clear_tmp_copyAndPaste(void)
    {
		tmp_copyAndPaste.source = ((size_t)INT_MAX);
		tmp_copyAndPaste.pasteID = ((size_t)INT_MAX);
		tmp_copyAndPaste.target = ((size_t)INT_MAX);
		tmp_copyAndPaste.edgeLabels.clear();
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
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
	Rule_GML_grammar
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
	Rule_GML_grammar
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
				}
				clear_tmp_node_data();
			} else if (s == "edge") {
				if ( is_valid_edge(tmp_edge) ) {
					edges.insert(tmp_edge);
				}
				clear_tmp_edge_data();
			} else if (s == "constrainAdj") {
				if ( is_valid_MC_NodeAdjacency(tmp_MC_NodeAdjacency) ) {
					  // store in global rule storage
					self.ruleConstraints.push_back( tmp_MC_NodeAdjacency.clone() );
				}
				clear_tmp_MC_NodeAdjacency();
			} else if (s == "constrainNode") {
				if ( is_valid_MC_NodeLabel(tmp_MC_NodeLabel) ) {
					  // store in global rule storage
					self.ruleConstraints.push_back( tmp_MC_NodeLabel.clone() );
				}
				clear_tmp_MC_NodeLabel();
			} else if (s == "constrainNoEdge") {
				if ( is_valid_MC_NoEdge(tmp_MC_NoEdge) ) {
					  // store in global rule storage
					self.ruleConstraints.push_back( tmp_MC_NoEdge.clone() );
				}
				clear_tmp_MC_NoEdge();
			} else if (s == "constrainEdge") {
				if ( is_valid_MC_EdgeLabel(tmp_MC_EdgeLabel) ) {
					  // store in global rule storage
					self.ruleConstraints.push_back( tmp_MC_EdgeLabel.clone() );
				}
				clear_tmp_MC_EdgeLabel();
			} else if (s == "copyAndPaste") {
				if ( is_valid_copyAndPaste(tmp_copyAndPaste) ) {
					  // store in global copy-and-paste storage
					self.copyAndPaste[tmp_copyAndPaste.source].insert( tmp_copyAndPaste );
				}
				clear_tmp_copyAndPaste();
			}
		}
      
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
	Rule_GML_grammar
	::definition< ScannerT >
	::create_Rule(void)
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
		
		  // copy parsed rule ID
		if (tmp_ruleID.compare("#NOT-SET#") == 0) {
			throw Rule_GML_error("no ruleID specified");
		}
		self.ruleID = tmp_ruleID;

		  // copy parsed wildcard
		bool useWildcard = tmp_wildcard.compare("#NOT-SET#") != 0;
		bool foundWildcardLabel = false;
		if (useWildcard) {
			self.wildcard = tmp_wildcard;
		}

		  // insert all nodes
		for (n = nodes.begin(); n != nodes.end(); ++n) {
			
			  // check if node already known
			nodeIndex1 = id2index.find((*n).get<0>());
			bool indexKnown = nodeIndex1 != id2index.end();
			
			  // access to node --> insert if necessary
			Rule::CoreGraph::vertex_descriptor newVertex;
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
			label = trimQuotes(label);
			  // write label
			if (contextString.compare("context") == 0) {
				  // check if ID is unknown
				if ( indexKnown ) {
					throw Rule_GML_error("node ID '"
							+ boost::lexical_cast<std::string>(n->get<0>())
							+ "' is not unique");
				}
				self.nodeContext[newVertex] = ggl::Rule::RULE_CONTEXT;
				self.nodeLabel[newVertex] = label;
				  // check if wildcard used
				if (useWildcard && !foundWildcardLabel && label.compare(self.wildcard) ==  0) {
					foundWildcardLabel = true;
				}
			} else if (contextString.compare("left") == 0) {
				if (indexKnown) {
					  // check if node is unknown
					if ( self.nodeContext[newVertex] != ggl::Rule::RULE_RIGHT_SIDE) {
						throw Rule_GML_error("node ID '"
								+ boost::lexical_cast<std::string>(n->get<0>())
								+ "' is in 'left' but at least once present in non-'right' too");
					}
					  // copy current right side label to right label change prop
					self.nodeLabelRight[newVertex] = self.nodeLabel[newVertex];
					self.nodeContext[newVertex] = ggl::Rule::RULE_LABEL_CHANGE;
					  // check if label is really changed
					if ( self.nodeLabelRight[newVertex].compare(label) == 0 ) {
						throw Rule_GML_error("node ID '"
								+ boost::lexical_cast<std::string>(n->get<0>())
								+ "' is in 'left' and 'right' but no label is changed");
					}
				} else {
					self.nodeContext[newVertex] = ggl::Rule::RULE_LEFT_SIDE;
				}
				self.nodeLabel[newVertex] = label;
				  // check if wildcard used
				if (useWildcard && !foundWildcardLabel && label.compare(self.wildcard) ==  0) {
					foundWildcardLabel = true;
				}
			} else if (contextString.compare("right") == 0) {
				  // check if wildcard used --> not allowed in right context
				if (label.compare(self.wildcard) ==  0) {
					throw Rule_GML_error("wildcard node label '"
							+ self.wildcard
							+ "' is not allowed in 'right' specification");
				}
				if (indexKnown) {
					  // check if node is unknown
					if ( self.nodeContext[newVertex] != ggl::Rule::RULE_LEFT_SIDE) {
						throw Rule_GML_error("node ID '"
								+ boost::lexical_cast<std::string>(n->get<0>())
								+ "' is in 'right' but at least once present in non-'left' too");
					}
					self.nodeContext[newVertex] = ggl::Rule::RULE_LABEL_CHANGE;
					self.nodeLabelRight[newVertex] = label;
					  // check if label is really changed
					if ( self.nodeLabel[newVertex].compare(label) == 0 ) {
						throw Rule_GML_error("node ID '"
								+ boost::lexical_cast<std::string>(n->get<0>())
								+ "' is in 'right' and 'left' but no label is changed");
					}
				} else {
					self.nodeContext[newVertex] = ggl::Rule::RULE_RIGHT_SIDE;
					self.nodeLabel[newVertex] = label;
				}
			} else {
				throw Rule_GML_error("unknown node context '" + contextString + "' found");
			}  
			  // clear data structures for next iteration
			reset_data_structures();
		}

		  // insert all edges
		for (e = edges.begin(); e != edges.end(); ++e) {

			  // get new indices and check whether or not old node IDs are known
			nodeIndex1 = id2index.find((*e).get<0>());
			if ( nodeIndex1 == id2index.end() ) {
				throw Rule_GML_error("edge "
						+ boost::lexical_cast<std::string>(e->get<0>())
						+" --> "
						+ boost::lexical_cast<std::string>(e->get<1>())
						+ ": first node ID is unknown");
			}
			nodeIndex2 = id2index.find((*e).get<1>());
			if ( nodeIndex2 == id2index.end() ) {
				throw Rule_GML_error("edge "
						+ boost::lexical_cast<std::string>(e->get<0>())
						+" --> "
						+ boost::lexical_cast<std::string>(e->get<1>())
						+ ": second node ID is unknown");
			}
			
			std::pair< Rule::CoreGraph::edge_descriptor, bool>
		  		newEdge = boost::add_edge(	boost::vertex( nodeIndex1->second, self.g2fill )
				  							, boost::vertex( nodeIndex2->second, self.g2fill )
				  							, self.g2fill );

			  // set context and label
			std::string contextString = (std::string)(*e).get<3>();
			std::string label = (std::string)(*e).get<2>();
			  // check if obsolete "" or '' quotes are present
			label = trimQuotes(label);
			  // write label
			if (contextString.compare("context") == 0) {
				self.edgeContext[newEdge.first] = ggl::Rule::RULE_CONTEXT;
				self.edgeLabel[newEdge.first] = label;
				  // check if wildcard used
				if (useWildcard && !foundWildcardLabel && label.compare(self.wildcard) ==  0) {
					foundWildcardLabel = true;
				}
			} else if (contextString.compare("left") == 0) {
				self.edgeContext[newEdge.first] = ggl::Rule::RULE_LEFT_SIDE;
				self.edgeLabel[newEdge.first] = label;
				  // check if wildcard used
				if (useWildcard && !foundWildcardLabel && label.compare(self.wildcard) ==  0) {
					foundWildcardLabel = true;
				}
			} else if (contextString.compare("right") == 0) {
				  // check if wildcard used --> not allowed in right context
				if (label.compare(self.wildcard) ==  0) {
					throw Rule_GML_error("wildcard edge label '"
							+ self.wildcard
							+ "' is not allowed in 'right' specification");
				}
				self.edgeContext[newEdge.first] = ggl::Rule::RULE_RIGHT_SIDE;
				self.edgeLabel[newEdge.first] = label;
			} else {
				throw Rule_GML_error("unknown edge context '" + contextString + "' found");
			}  

//			if((std::string)(*e).get<3>()=="left")
//				self.addEdge((*e).get<0>(), (*e).get<1>(), (*e).get<2>(), "");
//				self.m_.add_bond((*e).get<0>(), (*e).get<1>(), (*e).get<2>(), "");
//			if((std::string)(*e).get<3>()=="right")
//				self.addEdge((*e).get<0>(), (*e).get<1>(), "", (*e).get<2>());
//				self.m_.add_bond((*e).get<0>(), (*e).get<1>(), "", (*e).get<2>());
		}

		  // clear temporary data structures
		nodes.clear();
		edges.clear();

		  // check if non-left edges have only non-left source/target
		{
			  // get access to edge descriptors
			Rule::CoreGraph::edge_iterator ei, e_end;
			  // check all edges
			for (boost::tie(ei, e_end) = boost::edges(self.g2fill); ei != e_end; ++ei) {
				  // check non-left edges if they have non-left source/target
				if ( self.edgeContext[*ei] != ggl::Rule::RULE_LEFT_SIDE ) {
					if (self.nodeContext[boost::source(*ei,self.g2fill)] == ggl::Rule::RULE_LEFT_SIDE
							|| self.nodeContext[boost::target(*ei,self.g2fill)] == ggl::Rule::RULE_LEFT_SIDE )
					{
						throw Rule_GML_error("edge in 'non-left' but has 'left' source/target");
					}
				} else {
					  // check left edges if they have non-right source/target
					if (self.nodeContext[boost::source(*ei,self.g2fill)] == ggl::Rule::RULE_RIGHT_SIDE
							|| self.nodeContext[boost::target(*ei,self.g2fill)] == ggl::Rule::RULE_RIGHT_SIDE )
					{
						throw Rule_GML_error("edge in 'left' but has 'right' source/target");
					}
				}
			}
		}

		  // update indices of rule constraints
		sgm::MC_Node *mc_node = NULL;
		sgm::MC_Edge *mc_edge = NULL;
		for (std::vector< sgm::Pattern_Interface::Match_Constraint* >::iterator curConstr = self.ruleConstraints.begin();
				curConstr != self.ruleConstraints.end(); ++curConstr)
		{
			  // check if wildcard was used among the constraints
			if (useWildcard && !foundWildcardLabel && (*curConstr)->isConstrainedLabel(self.wildcard)) {
				foundWildcardLabel = true;

				  // TODO check if label constraint, if so throw error
			}
			  // check if current constraint is a node constraint
			mc_node = dynamic_cast< sgm::MC_Node* >(*curConstr);
			if (mc_node != NULL) {
				  // get mapped node index
				nodeIndex1 = id2index.find(mc_node->constrainedNodeID);
				  // ensure that node id is known, otherwise constraint inconsistent
				if ( nodeIndex1 == id2index.end() ) {
					throw Rule_GML_error("constrained node ID '"
							+ boost::lexical_cast<std::string>(mc_node->constrainedNodeID)
							+ "' is unknown");
				}
				  // update node index
				mc_node->constrainedNodeID = nodeIndex1->second;
				  // proceed to next constraint
				continue;
			}
			  // check if current constraint is an edge constraint
			mc_edge = dynamic_cast< sgm::MC_Edge* >(*curConstr);
			if (mc_edge != NULL) {
				  // get mapped node index
				nodeIndex1 = id2index.find(mc_edge->constrainedFromID);
				  // ensure that node id is known, otherwise constraint inconsistent
				if ( nodeIndex1 == id2index.end() ) {
					throw Rule_GML_error("constrained source ID '"
							+ boost::lexical_cast<std::string>(mc_edge->constrainedFromID)
							+ "' is unknown");
				}
				  // update node index
				mc_edge->constrainedFromID = nodeIndex1->second;
				  // get mapped node index
				nodeIndex1 = id2index.find(mc_edge->constrainedToID);
				  // ensure that node id is known, otherwise constraint inconsistent
				if ( nodeIndex1 == id2index.end() ) {
					throw Rule_GML_error("constrained target ID '"
							+ boost::lexical_cast<std::string>(mc_edge->constrainedToID)
							+ "' is unknown");
				}
				  // update node index
				mc_edge->constrainedToID = nodeIndex1->second;

				  // check if MC_NoEdge constraint
				if (dynamic_cast< sgm::MC_NoEdge* >(mc_edge) != NULL) {

					// check if MC_NoEdge is violated by edge in pattern
					std::pair< Rule::CoreGraph::edge_descriptor, bool>
						edgeCheck = boost::edge(	boost::vertex( mc_edge->constrainedFromID, self.g2fill )
												, boost::vertex( mc_edge->constrainedToID, self.g2fill )
												, self.g2fill );
					  // edge exists.. check if only present in right side, i.e. inserted
					if (edgeCheck.second
						&& self.edgeContext[edgeCheck.first] != ggl::Rule::RULE_RIGHT_SIDE )
					{
						throw Rule_GML_error("constrained edge "
								+ boost::lexical_cast<std::string>(mc_edge->constrainedFromID)
								+ " -> "
								+ boost::lexical_cast<std::string>(mc_edge->constrainedToID)
								+ " is set NO-EDGE but present in pattern (left|context)");
					}
				}
				  // proceed to next constraint
				continue;
			}
		}

		  // update indices of copy-and-paste operations
		Rule::CopyAndPasteOperations mappedCopyAndPaste;
		for (Rule::CopyAndPasteOperations::iterator op=self.copyAndPaste.begin(); op!=self.copyAndPaste.end(); ++op)
		{
			for (Rule::CopyAndPasteOperations::mapped_type::const_iterator cnp = op->second.begin(); cnp != op->second.end(); ++cnp)
			{
				  // get optional mapped target index if set
				size_t targetID = cnp->target;
				if (targetID != (size_t)INT_MAX) {
					nodeIndex1 = id2index.find(targetID);
					if (nodeIndex1 == id2index.end()) {
						throw Rule_GML_error("copyAndPaste target ID '"
								+ boost::lexical_cast<std::string>(cnp->target)
								+ "' is unknown");
					}
					targetID = nodeIndex1->second;
				}

				  // get mapped copy-and-paste node indices
				nodeIndex1 = id2index.find(cnp->source);
				if ( nodeIndex1 == id2index.end() ) {
					throw Rule_GML_error("copyAndPaste source ID '"
							+ boost::lexical_cast<std::string>(cnp->source)
							+ "' is unknown");
				}
				nodeIndex2 = id2index.find(cnp->pasteID);
				if ( nodeIndex2 == id2index.end() ) {
					throw Rule_GML_error("copyAndPaste paste id '"
							+ boost::lexical_cast<std::string>(cnp->pasteID)
							+ "' is unknown");
				}

				  // check if source is left-side-only node
				if (self.nodeContext[ boost::vertex(nodeIndex1->second, self.g2fill) ] == ggl::Rule::RULE_RIGHT_SIDE ) {
					throw Rule_GML_error("copyAndPaste source ID '"
							+ boost::lexical_cast<std::string>(nodeIndex1->second)
							+ "' is right-side-only node to be inserted");
				}
				  // check if target is no left-side-only node
				if (self.nodeContext[ boost::vertex(nodeIndex2->second, self.g2fill) ] == ggl::Rule::RULE_LEFT_SIDE ) {
					throw Rule_GML_error("copyAndPaste paste id '"
							+ boost::lexical_cast<std::string>(nodeIndex2->second)
							+ "' is a left-side-only node to be deleted");
				}
				  // store mapped copy-and-paste operation
				mappedCopyAndPaste[nodeIndex1->second].insert(Rule::RuleCnP( nodeIndex1->second, nodeIndex2->second, targetID, cnp->edgeLabels ));
			}
		}
		  // overwrite old operations
		self.copyAndPaste.clear();
		self.copyAndPaste = mappedCopyAndPaste;

		  // check if wildcard label was used
		if (useWildcard && !foundWildcardLabel) {
			throw Rule_GML_error("wildcard label '"
					+ self.wildcard
					+ "' specified but not present in rule");
		}
    }
    
//##############################################################################
    

	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
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
	Rule_GML_grammar
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
	Rule_GML_grammar
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
	Rule_GML_grammar
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
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NodeAdjacency_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "id")	{	tmp_MC_NodeAdjacency.constrainedNodeID = i; }
     	else if (k == "op") {
     		if ( s == "=" ) {	tmp_MC_NodeAdjacency.op = sgm::MC_NodeAdjacency::MC_EQ; } else
     		if ( s == "<" ) {	tmp_MC_NodeAdjacency.op = sgm::MC_NodeAdjacency::MC_L; } else
     		if ( s == ">" ) {	tmp_MC_NodeAdjacency.op = sgm::MC_NodeAdjacency::MC_G; }
     	}
     	else if (k == "count") {	tmp_MC_NodeAdjacency.count = i; }
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NodeLabel_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "id")	{	tmp_MC_NodeLabel.constrainedNodeID = i; }
		if      (k == "op")	{
			if ( s == "=" ) {
				tmp_MC_NodeLabel.compareType = sgm::MC_NodeLabel::ALLOWED;
			} else
			if ( s == "!" ) {
				tmp_MC_NodeLabel.compareType = sgm::MC_NodeLabel::FORBIDDEN;
			}
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_EdgeLabel_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "source")	{	tmp_MC_EdgeLabel.constrainedFromID = i; }
		if      (k == "target")	{	tmp_MC_EdgeLabel.constrainedToID = i; }
		if      (k == "op")	{
			if ( s == "=" ) {
				tmp_MC_EdgeLabel.compareType = sgm::MC_EdgeLabel::ALLOWED;
			} else
			if ( s == "!" ) {
				tmp_MC_EdgeLabel.compareType = sgm::MC_EdgeLabel::FORBIDDEN;
			}
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NoEdge_data(std::string k, std::string s, int i, double d)
    {
		if      (k == "source")	{	tmp_MC_NoEdge.constrainedFromID = i; }
		if      (k == "target")	{	tmp_MC_NoEdge.constrainedToID = i; }
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NodeAdjacencyNL_data(std::string k, std::string s, int i, double d)
    {
		if (k == "label") {
			tmp_MC_NodeAdjacency.nodeLabels.insert( trimQuotes(s) );
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NodeLabelNL_data(std::string k, std::string s, int i, double d)
    {
		if (k == "label") {
			tmp_MC_NodeLabel.nodeLabels.insert( trimQuotes(s) );
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_EdgeLabelEL_data(std::string k, std::string s, int i, double d)
    {
		if (k == "label") {
			tmp_MC_EdgeLabel.edgeLabels.insert( trimQuotes(s) );
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_MC_NodeAdjacencyEL_data(std::string k, std::string s, int i, double d)
    {
		if (k == "label") {
			tmp_MC_NodeAdjacency.edgeLabels.insert( trimQuotes(s) );
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::set_copyAndPaste_data(std::string k, std::string s, int i, double d)
    {
		if (k == "source") {
			assert( i>= 0 );
			tmp_copyAndPaste.source = (size_t) i;
		}
		if (k == "id") {
			assert( i>= 0 );
			tmp_copyAndPaste.pasteID = (size_t) i;
		}
		if (k == "target") {
			assert( i>= 0 );
			tmp_copyAndPaste.target = (size_t) i;
		}
    }

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
	::set_copyAndPaste_EL_data(std::string k, std::string s, int i, double d)
	{
		if (k == "label") {
			tmp_copyAndPaste.edgeLabels.insert( trimQuotes(s) );
		}
	}

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	Rule_GML_grammar
	::definition< ScannerT >
    ::keyValueAction(std::string k, std::string s, int i, double d)
    {
		if (k.compare("ruleID") == 0) {
			  // set ruleID without quotes if any
			tmp_ruleID = trimQuotes( s );
		}
		if (k.compare("wildcard") == 0) {
			  // set wildcard without quotes if any
			tmp_wildcard = trimQuotes( s );
		}
      	if ( keystack.empty() ) {
      		return;
      	}
    	if (keystack[keystack.size()-1] != "|") {
    		/* key with list value type we want to remember */

    		if ( ! k.empty() ) {
    			/* dumpKeyValues(k, s, i, d) */
    	  
    			if (keystack[keystack.size()-1] == "node") {
    				set_node_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "edge") {
    				set_edge_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "constrainAdj") {
    				set_MC_NodeAdjacency_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "constrainNode") {
    				set_MC_NodeLabel_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "constrainNoEdge") {
    				set_MC_NoEdge_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "constrainEdge") {
    				set_MC_EdgeLabel_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "copyAndPaste") {
    				set_copyAndPaste_data(k, s, i, d);
    			} else if (keystack[keystack.size()-1] == "nodeLabels") {
    				if (keystack.size() >= 2 && keystack[keystack.size()-2] == "constrainAdj") {
    					set_MC_NodeAdjacencyNL_data(k, s, i, d);
    				} else if (keystack.size() >= 2 && keystack[keystack.size()-2] == "constrainNode") {
    					set_MC_NodeLabelNL_data(k, s, i, d);
    				}
    			} else if (keystack[keystack.size()-1] == "edgeLabels") {
    				if (keystack.size() >= 2 && keystack[keystack.size()-2] == "constrainAdj") {
						set_MC_NodeAdjacencyEL_data(k, s, i, d);
    				} else if (keystack.size() >= 2 && keystack[keystack.size()-2] == "constrainEdge") {
    					set_MC_EdgeLabelEL_data(k, s, i, d);
    				} else if (keystack.size() >= 2 && keystack[keystack.size()-2] == "copyAndPaste") {
    					set_copyAndPaste_EL_data(k, s, i, d);
    				}
    			}
    			/* dumpKeyValues(k, s, i, d) */
    		}
    	}
    }
    
//##############################################################################

} // namespace ggl

