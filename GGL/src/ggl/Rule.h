
#include <algorithm>
#include <boost/graph/copy.hpp>
#include <cassert>

namespace ggl {


////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::Rule ( const Rule::CoreGraph & core_
			, const std::string& id_
			, const std::string* wildcardToUse )
	 :	core(core_),
	 	id(id_),
	 	wildcard( wildcardToUse==NULL ? NULL : new std::string(*wildcardToUse)),
	 	LeftSide(	Rule::getRuleSideNodes(core,RULE_LEFT_SIDE)),
	 	RightSide(	Rule::getRuleSideNodes(core,RULE_RIGHT_SIDE)),
	 	Context(	Rule::getRuleSideNodes(core,RULE_CONTEXT)),
	 	copyAndPaste()
 	{
		assert( boost::is_undirected(core) /*Currently ONLY UNDIRECTED rule core graph supported !*/ );
 	}
	


////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::Rule ( const Rule::CoreGraph & core_
			, const std::string& id_
			, const Rule::MatchConstraintVec & matchConstraints
			, const std::string* wildcardToUse )
	 :	core(core_),
	 	id(id_),
	 	wildcard( wildcardToUse==NULL ? NULL : new std::string(*wildcardToUse)),
	 	LeftSide(	Rule::getRuleSideNodes(core,RULE_LEFT_SIDE),
	 				&matchConstraints),
	 	RightSide(	Rule::getRuleSideNodes(core,RULE_RIGHT_SIDE)),
	 	Context(	Rule::getRuleSideNodes(core,RULE_CONTEXT)),
	 	copyAndPaste()
 	{
		assert( boost::is_undirected(core) /*Currently ONLY UNDIRECTED rule core graph supported !*/ );
 	}



////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::Rule ( const Rule::CoreGraph & core_
			, const std::string& id_
			, const Rule::MatchConstraintVec & matchConstraints
			, const Rule::CopyAndPasteOperations & copyAndPaste_
			, const std::string* wildcardToUse )
	 :	core(core_),
	 	id(id_),
	 	wildcard( wildcardToUse==NULL ? NULL : new std::string(*wildcardToUse)),
	 	LeftSide(	Rule::getRuleSideNodes(core,RULE_LEFT_SIDE),
	 				&matchConstraints),
	 	RightSide(	Rule::getRuleSideNodes(core,RULE_RIGHT_SIDE)),
	 	Context(	Rule::getRuleSideNodes(core,RULE_CONTEXT)),
	 	copyAndPaste( copyAndPaste_ )
 	{
		assert( boost::is_undirected(core) /*Currently ONLY UNDIRECTED rule core graph supported !*/ );
 	}



////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::~Rule ( )
 	{
	 	if (wildcard!=NULL)
	 		delete wildcard;
 	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::Rule ( const Rule & toCopy )
	 :	core(),
	 	id(toCopy.id),
	 	wildcard( toCopy.wildcard == NULL ? NULL : new std::string(*(toCopy.wildcard))),
	 	LeftSide(	toCopy.LeftSide ),
	 	RightSide(	toCopy.RightSide ),
	 	Context(	toCopy.Context ),
	 	copyAndPaste(	toCopy.copyAndPaste )
 	{
		  // copy core graph
		boost::copy_graph<CoreGraph,CoreGraph>(toCopy.core, core);
 	}
	
	
////////////////////////////////////////////////////////////////////////////////


	inline
	Rule &
	Rule
	::operator =( const Rule & toCopy )
	{
		  // copy core graph
		boost::copy_graph<CoreGraph,CoreGraph>(toCopy.core, core);
		  // copy identifier
		id = toCopy.id;
		  // copy wildcard
		if (wildcard != NULL) delete wildcard;
		wildcard = (toCopy.wildcard==NULL) ? NULL : new std::string(*(toCopy.wildcard));
		  // copy context information
	 	LeftSide = toCopy.LeftSide;
	 	RightSide = toCopy.RightSide;
	 	Context = toCopy.Context;
	 	  // copy copy-and-paste information
	 	copyAndPaste = toCopy.copyAndPaste;
	 	  // return *this access
		return *this;
	}

	
////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleSide
	::RuleSide(	const Rule::NodeVec& nodes_
				, const Rule::MatchConstraintVec * const constraintsGlobID )
	 :	nodes(nodes_), constraints()
	{
		  // check if constraints to rewrite and store
		if (constraintsGlobID != NULL) {
			NodeMap r2l;
			for (size_t i=0; i<nodes.size(); ++i ) {
				r2l[nodes[i]] = i;
			}

			sgm::MC_Node * mc_node = NULL, *mc_node_copy = NULL;
			sgm::MC_Edge * mc_edge = NULL, *mc_edge_copy = NULL;

			  // rewrite all constraints and store
			for (Rule::MatchConstraintVec::const_iterator rC = constraintsGlobID->begin();
					rC != constraintsGlobID->end(); ++rC)
			{
				  // check if current constraint is a node constraint
				mc_node = dynamic_cast< sgm::MC_Node* >(*rC);
				if (mc_node != NULL) {
					  // check if the constraint is part of the left side
					if (r2l.find( mc_node->constrainedNodeID)!=r2l.end()) {
						  // create a copy
						mc_node_copy = mc_node->clone();
						  // update node ID of newly inserted constraint (remapped)
						mc_node_copy->constrainedNodeID = r2l[mc_node->constrainedNodeID];
						  // store the altered copy
						constraints.push_back(mc_node_copy);
	//				} else {
	//					assert( false /* SOURCE NOT PART OF LEFT SIDE */);
					}
					  // this constraint is handled --> proceed to next
					continue;
				}
				  // check if current constraint is an edge constraint
				mc_edge = dynamic_cast< sgm::MC_Edge* >(*rC);
				if (mc_edge != NULL) {
					  // check if the constraint is part of the left side
					if (	r2l.find( mc_edge->constrainedFromID)!=r2l.end()
							&& r2l.find( mc_edge->constrainedToID)!=r2l.end() )
					{
						  // make a copy
						mc_edge_copy = mc_edge->clone();
						  // update source ID of newly inserted constraint (remapped)
						mc_edge_copy->constrainedFromID = r2l[mc_edge->constrainedFromID];
						  // update target ID of newly inserted constraint (remapped)
						mc_edge_copy->constrainedToID = r2l[mc_edge->constrainedToID];
						  // store the altered copy
						constraints.push_back(mc_edge_copy);
	//				} else {
	//					assert( false /* SOURCE NOT PART OF LEFT SIDE */);
					}
					  // this constraint is handled --> proceed to next
					continue;
				}
				  // rC is neither an MC_Node nor an MC_Edge constraint that has
				  // to be remapped .. lets hope it is not based on index
				  // information
				  // --> just clone
				constraints.push_back((*rC)->clone());
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleSide
	::RuleSide( const RuleSide & toCopy )
	 :	nodes(toCopy.nodes)
		, constraints(sgm::Pattern::copyConstraintVec(toCopy.constraints))
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule::RuleSide&
	Rule
	::RuleSide
	::operator=( const RuleSide & toCopy )
	{
		  // flat copy data
		this->nodes = toCopy.nodes;

		  // deep copy of constraint data
		for (size_t i = 0; i < constraints.size(); ++i ) {
			delete constraints[i];
		}
		constraints.clear();
		  // copy all constraints maintained for this rule side
		constraints = sgm::Pattern::copyConstraintVec(toCopy.constraints);
		  // access to the changed *this object
		return *this;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleSide
	::~RuleSide()
	{
		for (Rule::MatchConstraintVec::iterator rC = constraints.begin();
				rC != constraints.end(); ++rC)
		{
			delete (*rC);
		}
		constraints.clear();
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleCnP
	::RuleCnP()
		:	source((size_t)INT_MAX)
			, pasteID((size_t)INT_MAX)
			, target((size_t)INT_MAX)
			, edgeLabels()
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleCnP
	::RuleCnP( const size_t source, const size_t pasteID )
		:	source(source)
			, pasteID(pasteID)
			, target((size_t)INT_MAX)
			, edgeLabels()
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleCnP
	::RuleCnP( const size_t source, const size_t pasteID, const size_t target )
		:	source(source)
			, pasteID(pasteID)
			, target(target)
			, edgeLabels()
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleCnP
	::RuleCnP( const size_t source, const size_t pasteID
			, const Rule::RuleCnP::LabelSet & edgelabels )
		:	source(source)
			, pasteID(pasteID)
			, target((size_t)INT_MAX)
			, edgeLabels(edgelabels)
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	Rule
	::RuleCnP
	::RuleCnP( const size_t source, const size_t pasteID
			, const size_t target
			, const Rule::RuleCnP::LabelSet & edgelabels )
		:	source(source)
			, pasteID(pasteID)
			, target(target)
			, edgeLabels(edgelabels)
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	bool
	Rule
	::RuleCnP
	::operator<( const Rule::RuleCnP& larger ) const
	{
		return (this->source < larger.source)
				|| (this->source == larger.source && this->target < larger.target)
				|| (this->source == larger.source && this->target == larger.target
						&& this->pasteID < larger.pasteID)
				|| (this->source == larger.source && this->target == larger.target
						&& this->pasteID == larger.pasteID
						&& this->edgeLabels < larger.edgeLabels);
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::CoreGraph&
	Rule
	::getCore(void) const
	{
		return core;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::RuleSide&
	Rule
	::getLeftSide(void) const
	{
		return LeftSide; 
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::RuleSide&
	Rule
	::getRightSide(void) const
	{
		return RightSide; 
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::RuleSide&
	Rule
	::getContext(void) const
	{
		return Context; 
	}


////////////////////////////////////////////////////////////////////////////////


	inline
	const std::string&
	Rule
	::getID(void) const
	{
		return id; 
	}
			
			
////////////////////////////////////////////////////////////////////////////////


	inline
	void 
	Rule
	::setID( const std::string& newID)
	{
		id = newID; 
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const std::string*
	Rule
	::getUsedWildcard(void) const
	{
		return wildcard;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	void
	Rule
	::setUsedWildcard( const std::string* const wildcardToUse )
	{
		  // remove old wildcard
		if (wildcard != NULL)
			delete wildcard;
		  // set new wildcard
		wildcard = wildcardToUse == NULL ? NULL : new std::string(*wildcardToUse);
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::MatchConstraintVec &
	Rule
	::getMatchConstraints( void ) const
	{
		return LeftSide.constraints;
	}


////////////////////////////////////////////////////////////////////////////////


	inline
	const Rule::CopyAndPasteOperations &
	Rule
	::getCopyAndPasteOperations( void ) const
	{
		return copyAndPaste;
	}


////////////////////////////////////////////////////////////////////////////////


	inline
	Rule::NodeVec
	Rule
	::getRuleSideNodes(	const Rule::CoreGraph &graph,
							const Rule::RuleContext &level )
	{
		  // return container
		NodeVec nodes;

		  // get level property class
		boost::property_map<CoreGraph, NodeContextProperty>::const_type
			levelMap = boost::get( NodeContextProperty(), graph );

		  // get index property class
		boost::property_map<CoreGraph, NodeIndexProperty>::const_type
			indexMap = boost::get( NodeIndexProperty(), graph );
		
		  // iterators for graph descriptor access
		CoreGraph::vertex_iterator vi, v_end;

		  // get access to vertex descriptors
		boost::tie(vi, v_end) = boost::vertices(graph);
		
		for (; vi != v_end; ++vi) {
			  // get grammar level of current node
			size_t cur_lvl = levelMap[*vi];
			  // check if current node is part of the requested subgraph
			if ( cur_lvl % level == 0) {
				  // add index to container
				nodes.push_back(indexMap[*vi]);
			}
		}
		
		  // sort data
		std::sort(nodes.begin(), nodes.end());
		
		return nodes;
	}



////////////////////////////////////////////////////////////////////////////////


	inline
	size_t
	Rule
	:: isConsistent( void ) const
	{
		  // assume all checks are ok
		size_t retCode = C_Consistent;

		  // check if rule ID is set
		if (getID().compare("")==0) {
			retCode *= C_NoID;
		}
		  // check if edge context usage is ok
		if ( ! checkEdgeContext(core) ) {
			retCode *= C_WrongEdgeContext;
		}

		  // return final consistency status
		return retCode;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	bool
	Rule
	:: decodeConsistencyStatus(	const size_t consistencyCode
								, std::ostream& errorStream
								, const bool completeCheck )
	{
		if (consistencyCode == C_Consistent) {
			return true;
		}
		  // temporary error code handling
		size_t errorCode = consistencyCode;
		errorStream	<<"The rule is not consistent because :\n";

		if (errorCode % C_NoID == 0) {
			errorStream <<" + contains no ruleID information \n";
			errorCode /= C_NoID;
		}
		if (errorCode % C_WrongEdgeContext == 0) {
			errorStream <<" + contains edges with wrong context usage \n";
			errorCode /= C_WrongEdgeContext;
		}
		if (completeCheck && errorCode != 1) {
			errorStream <<" + undescribed error code "<<errorCode<<" \n";
		}

		return false;
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	bool
	Rule
	:: checkEdgeContext( const Rule::CoreGraph & coreGraph )
	{

		  // get level property class
		boost::property_map<CoreGraph, NodeContextProperty>::const_type
			nodeContext = boost::get( NodeContextProperty(), coreGraph );
		boost::property_map<CoreGraph, EdgeContextProperty>::const_type
			edgeContext = boost::get( EdgeContextProperty(), coreGraph );

		  // will hold the context of the source and target node of each edge
		RuleContext sourceContext, targetContext;

		  // iterate over all edges within the core graph
		CoreGraph::edge_iterator edge, edge_end;
		boost::tie(edge, edge_end) = boost::edges( coreGraph );
		for(; edge != edge_end; ++edge ) {
			  // get context of source and target node of this edge
			sourceContext = nodeContext[boost::source(*edge,coreGraph)];
			targetContext = nodeContext[boost::target(*edge,coreGraph)];
			  // check for allowed edge/node context pairs
			switch (edgeContext[*edge]) {
				case RULE_CONTEXT:
					if (sourceContext != RULE_CONTEXT && sourceContext != RULE_LABEL_CHANGE)
						{return false;}
					if (targetContext != RULE_CONTEXT && targetContext != RULE_LABEL_CHANGE)
						{return false;}
					break;
				case RULE_LEFT_SIDE:
					if (sourceContext == RULE_RIGHT_SIDE)
						{return false;}
					if (targetContext == RULE_RIGHT_SIDE)
						{return false;}
					break;
				case RULE_RIGHT_SIDE:
					if (sourceContext == RULE_LEFT_SIDE)
						{return false;}
					if (targetContext == RULE_LEFT_SIDE)
						{return false;}
					break;
				case RULE_LABEL_CHANGE:
					  // label change context not allowed for edges
					return false;
					break;
				default:
					break;
			}
		}

		return true;
	}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////


} // namespace ggl

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

