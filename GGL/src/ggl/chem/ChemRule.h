
#include <map>
#include <algorithm>
#include <boost/graph/copy.hpp>
#include <cassert>
#include <sstream>

#include "ggl/chem/MoleculeUtil.hh"  // for atom label validation

#include "sgm/MC_Edge.hh"

namespace ggl {
 namespace chem {



////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::ChemRule ( const ChemRule::CoreGraph & core_
			, const std::string& id_ )
	 :	SuperClass( core_, id_ )
	 	, transitionState(NULL)
 	{
 		  // adds no edge constraints for all edges that are right side context
 		  // only, to avoid the appearance of parallel edges within molecule
 		  // graphs
 		addImplicitNoEdgeConstraints( *this );
 	}


////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::ChemRule ( const ChemRule::CoreGraph & core_
			, const std::string& id_
			, const std::vector< sgm::Pattern_Interface::Match_Constraint* > & constraints )
	 :	SuperClass( core_, id_, constraints )
	 	, transitionState(NULL)
 	{
 		  // adds no edge constraints for all edges that are right side context
 		  // only, to avoid the appearance of parallel edges within molecule
 		  // graphs
 		addImplicitNoEdgeConstraints( *this );
 	}
	

////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::ChemRule ( const ChemRule::CoreGraph & core_
			, const std::string& id_
			, const std::vector< sgm::Pattern_Interface::Match_Constraint* > & constraints
			, const CopyAndPasteOperations & copyAndPaste )
	 :	SuperClass( core_, id_, constraints, copyAndPaste )
	 	, transitionState(NULL)
 	{
 		  // adds no edge constraints for all edges that are right side context
 		  // only, to avoid the appearance of parallel edges within molecule
 		  // graphs
 		addImplicitNoEdgeConstraints( *this );
 	}


////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::~ChemRule ( )
 	{
		  // remove transition state if present
		if (transitionState != NULL)
			delete transitionState;
 	}

////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::ChemRule ( const ChemRule & toCopy )
	 :	SuperClass( toCopy )
	 	, transitionState( (toCopy.transitionState == NULL) 
 							? NULL 
 							: new TransitionState(*(toCopy.transitionState)))
 	{
 	}
	
	
////////////////////////////////////////////////////////////////////////////////


	inline
	ChemRule
	::ChemRule ( const ggl::Rule & toCopy )
	 :	SuperClass( toCopy )
	 	, transitionState( NULL )
 	{
		  // adds no edge constraints for all edges that are right side context
		  // only, to avoid the appearance of parallel edges within molecule
		  // graphs
		addImplicitNoEdgeConstraints( *this );
 	}


////////////////////////////////////////////////////////////////////////////////

	

	inline
	const ChemRule::TransitionState&
	ChemRule
	::getTransitionState() const
	{
		if (transitionState == NULL) {
			transitionState = new TransitionState(*this);
		}
		return *transitionState;
	}

////////////////////////////////////////////////////////////////////////////////


  } // namespace chem
} // namespace ggl

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#include "ggl/chem/SMILESwriter.hh"

#include <sstream>


namespace ggl {
  namespace chem {

//##############################################################################



	inline
	ChemRule
	::TransitionState
	::TransitionState( void )
	 :	tState()
	 	, tStateSMILES("")
	{
	}

//##############################################################################



	inline
	ChemRule
	::TransitionState
	::TransitionState( const ChemRule& rule )
	 :	tState()
	 	, tStateSMILES("")
	{
		assert( rule.isConsistent() == ChemRule_Constants::C_Consistent /*cannot work with inconsistent graph grammar rule*/ );
		
		initializeTransitionState( rule.getCore() );
	}

//##############################################################################



	inline
	ChemRule
	::TransitionState
	::TransitionState( const TransitionState& toCopy )
	 :	tState()
	 	, tStateSMILES(toCopy.tStateSMILES)
	{
		  // copy the whole transition state graph
		boost::copy_graph( toCopy.tState, tState );
	}
		
	
//##############################################################################

	

	inline
	ChemRule
	::TransitionState
	::~TransitionState()
	{
	}

	
//##############################################################################

	

	inline
	void
	ChemRule
	::TransitionState
	::initializeTransitionState( const CoreGraph& rule )
	{
		
		  // copy the whole rule core graph
		CoreGraph tmp;
		boost::copy_graph( rule, tmp );
		
		  // iterators for edges
		ChemRule::CoreGraph::edge_iterator eIt, eItEnd;
		ChemRule::CoreGraph::vertex_descriptor curNode;
		  // get node index property map
		boost::property_map<	ChemRule::CoreGraph,
										ChemRule::NodeIndexProperty >::const_type
			nodeIndex = boost::get( ChemRule::NodeIndexProperty(), tmp );
		  // get edge level property map
		boost::property_map<	ChemRule::CoreGraph,
										ChemRule::EdgeContextProperty >::type
			levelMap = boost::get( ChemRule::EdgeContextProperty(), tmp );
		  // get edge label property maps
		boost::property_map<	ChemRule::CoreGraph,
										ChemRule::EdgeLabelProperty >::type
			labelMap = boost::get( ChemRule::EdgeLabelProperty(), tmp );

		ValChangeMap valInc;
		
		  // the valence of the left side edges (to be removed)
		std::map< std::pair<size_t,size_t>, size_t > leftSideValence;

		  // remove all left side edges
		bool edgeRemoved = false;
		do {
			edgeRemoved = false;
			  // check all edges and remove left side edges
			for (boost::tie(eIt,eItEnd) = boost::edges(tmp); !edgeRemoved && eIt != eItEnd; ++eIt) {
				if ( levelMap[*eIt] == RULE_LEFT_SIDE ) {
					  // check if edge unknown
					size_t from = nodeIndex[ boost::source(*eIt,tmp) ];
					size_t to = nodeIndex[ boost::target(*eIt,tmp) ];
					  // order check
					if (to < from) {
						from = to;
						to = nodeIndex[ boost::source(*eIt,tmp) ];
					}
					  // check if edge is unknown so far
					assert( leftSideValence.find(std::make_pair(from,to)) == leftSideValence.end() /* otherwise do we have two left side edges between these two nodes */);
					  // gather valence information
					assert ( MoleculeUtil::getBondData(labelMap[*eIt]) != NULL /*otherwise bond not known */);
					// TODO aromatic edges not correctly handled
					size_t valence = MoleculeUtil::getBondData(labelMap[*eIt])->valence;
//					switch ( labelMap[*eIt].at(0) ) {
//					case '-' : valence += 1; break;
//					case '=' : valence += 2; break;
//					case '#' : valence += 3; break;
//					default : assert( false /* current edge label is none of '-', '=', or '#' */);
//					}
					  // store valence information
					leftSideValence[std::make_pair(from,to)] = valence;
					  // remove edge
					boost::remove_edge( *eIt, tmp );
					  // restart iteration since edge iterators might be
					  // inconsistent due to edge removal
					edgeRemoved = true;
				}
			}
		} while(edgeRemoved);

		  // check and update all right side edges
		for (boost::tie(eIt,eItEnd) = boost::edges(tmp); eIt != eItEnd; ++eIt) {
			switch (levelMap[*eIt]) {
			case RULE_CONTEXT : break; // nothing to do for edges in rule context
			case RULE_LEFT_SIDE : // should not occure anymore
				assert(false);
				break;
			case RULE_RIGHT_SIDE : // count valence increase
			{
				  // get valence change
				assert ( MoleculeUtil::getBondData(labelMap[*eIt]) != NULL /*otherwise bond not known */);
				// TODO aromatic edges not correctly handled
				size_t valChange = MoleculeUtil::getBondData(labelMap[*eIt])->valence;
//				switch ( labelMap[*eIt].at(0) ) {
//				case '-' : valChange += 1; break;
//				case '=' : valChange += 2; break;
//				case '#' : valChange += 3; break;
//				default : assert( false /* current edge label is none of '-', '=', or '#' */);
//				}
				  // check if replacement of left side edge (already removed)
				size_t from = nodeIndex[ boost::source(*eIt,tmp) ];
				size_t to = nodeIndex[ boost::target(*eIt,tmp) ];
				  // order check
				if (to < from) {
					from = to;
					to = nodeIndex[ boost::source(*eIt,tmp) ];
				}
				  // check if edge is known
				if( leftSideValence.find(std::make_pair(from,to)) != leftSideValence.end()) {
					size_t leftValence = leftSideValence.find(std::make_pair(from,to))->second;
					if (leftValence > valChange) {
						  // --> valence decrease
						  // set label to left label
						switch( leftValence ) {
						// TODO aromatic edges not correctly handled
						case 1 : labelMap[*eIt] = "-"; break;
						case 2 : labelMap[*eIt] = "="; break;
						case 3 : labelMap[*eIt] = "#"; break;
						default: assert( false /* edge valence not supported */);
						}
					} else {
						  // update connected nodes --> valence increase
						curNode = boost::source( *eIt, tmp );
						updateMap( curNode, valChange-leftValence, valInc );
						curNode = boost::target( *eIt, tmp );
						updateMap( curNode, valChange-leftValence, valInc );
					}
				} else {
					  // -> right side only edge
					  // update connected nodes --> valence increase
					curNode = boost::source( *eIt, tmp );
					updateMap( curNode, valChange, valInc );
					curNode = boost::target( *eIt, tmp );
					updateMap( curNode, valChange, valInc );
				}
				  // set to context edge
				levelMap[*eIt] = RULE_CONTEXT;
				break;
			}
			default : // should never happen
				assert( false /* unhandled RuleContext value */ );
			}
			
		}
		
		  // get node label property map
		boost::property_map<	ChemRule::CoreGraph,
										ChemRule::NodeLabelProperty >::type
			nodeLabel = boost::get( ChemRule::NodeLabelProperty(), tmp );

		  // update node labels
		for (ValChangeMap::const_iterator i=valInc.begin(); i!=valInc.end(); ++i ) {
			  // get current label
			std::string name = nodeLabel[i->first];
			assert( name.size() > 0 /* node label is empty */ );
			  // compile new node label
			std::stringstream sstr;
			sstr <<name;
			  // check if class identifier already present
			if (name.find(':') == std::string::npos) {
				  // if not, add new class identifier
				sstr <<':';
			}
			  // add valence increase information
			  // (leading "000" needed to preserve and distinguish from already present class information)
			sstr <<"000" << i->second;

			  // overwrite old label
			nodeLabel[i->first] = sstr.str();
		}
		
		  // copy updated rule graph into final transition state graph
		copyRuleToMol( tmp, tState );
	}

	
//##############################################################################

	

	inline
	const ggl::chem::Molecule&
	ChemRule
	::TransitionState
	::getGraph( void ) const
	{
		  // allow access to tState graph
		return tState;
	}

	
//##############################################################################

	

	inline
	const std::string&
	ChemRule
	::TransitionState
	::getSMILES( void ) const
	{
		  // check if already calculated
		if ( tStateSMILES.empty() ) {
			try {
				  // calculate SMILES of tmp
				tStateSMILES = ggl::chem::SMILESwriter::getSMILES( tState, false, true );
			} catch ( std::runtime_error & ex ) {
				tStateSMILES = "???";
			}
		}
		  // allow access to tState SMILES
		return tStateSMILES;
	}

	
//##############################################################################


	inline
	void
	ChemRule
	::TransitionState
	::updateMap(	const ChemRule::CoreGraph::vertex_descriptor& curNode
					, const size_t valChange
					, ValChangeMap & toUpdate )
	{
		  // get entry in according valence change map
		ValChangeMap::iterator valIt = toUpdate.find(curNode);
		if ( valIt == toUpdate.end() ) {
			  // insert new entry if necessary
			valIt = toUpdate.insert(
						ValChangeMap::value_type(curNode,0)).first;
		}
		  // update entry
		valIt->second += valChange;
	}

	
//##############################################################################

	

	inline
	void
	ChemRule
	::TransitionState
	::copyRuleToMol( const CoreGraph & rule
					, ggl::chem::Molecule & mol )
	{
		typedef ChemRule::CoreGraph::vertex_descriptor RVD;
		typedef ChemRule::CoreGraph::vertex_iterator RVI;
		typedef ChemRule::CoreGraph::edge_iterator REI;
		
		boost::property_map<	ChemRule::CoreGraph
										, ChemRule::NodeLabelProperty >::const_type
			rNodeLabel = boost::get( ChemRule::NodeLabelProperty(), rule );
		boost::property_map<	ChemRule::CoreGraph
										, ChemRule::EdgeLabelProperty >::const_type
			rEdgeLabel = boost::get( ChemRule::EdgeLabelProperty(), rule );

		typedef ggl::chem::Molecule::vertex_descriptor MVD;
//		typedef ggl::chem::Molecule::vertex_iterator MVi;
		typedef ggl::chem::Molecule::edge_descriptor MED;
//		typedef ggl::chem::Molecule::edge_iterator MEI;
		
		boost::property_map<	ggl::chem::Molecule
										, ggl::PropNodeLabel >::type 
			mNodeLabel = boost::get( ggl::PropNodeLabel(), mol );
		boost::property_map<	ggl::chem::Molecule
										, ggl::PropEdgeLabel >::type 
			mEdgeLabel = boost::get( ggl::PropEdgeLabel(), mol );
		
		std::map< RVD, MVD > nodeR2M;
		
		
		RVI rvi, rviEnd;
		MVD mvd;
		  // copy all nodes
		for (boost::tie(rvi,rviEnd)=boost::vertices(rule); rvi!=rviEnd; ++rvi) {
			  // insert node
			mvd = boost::add_vertex( mol );
			  // copy label
			mNodeLabel[mvd] = rNodeLabel[*rvi];
			  // store mapping
			nodeR2M[*rvi] = mvd;
		}
		  // copy all edges
		REI rei, reiEnd;
		MED med;
		for (boost::tie(rei,reiEnd)=boost::edges(rule); rei!=reiEnd; ++rei) {
			  // insert edge
			med = boost::add_edge(	  nodeR2M[ boost::source(*rei,rule) ]
									, nodeR2M[ boost::target(*rei,rule) ]
									, mol ).first;
			  // copy label
			mEdgeLabel[med] = rEdgeLabel[*rei];
		}
		
	}
	
	
//##############################################################################



	inline
	void
	ChemRule
	::addImplicitNoEdgeConstraints( ChemRule & toUpdate )
	{
		  // get the set of all already present NoEdge constraints
		typedef std::pair<size_t,size_t> Edge;
		std::set<Edge> constrained;
		  // check all present constraints if they are NoEdge constraints
		std::vector< sgm::Pattern_Interface::Match_Constraint* >::const_iterator constraint;
		sgm::MC_NoEdge* noEdgeConstraint = NULL;
		for (constraint = toUpdate.LeftSide.constraints.begin(); constraint != toUpdate.LeftSide.constraints.end(); ++constraint) {
			  // check if MC_NoEdge constraint
			noEdgeConstraint = dynamic_cast< sgm::MC_NoEdge* >(*constraint);
			if ( noEdgeConstraint != NULL) {
				  // store information (in source less target order)
				constrained.insert( Edge( std::min(noEdgeConstraint->constrainedFromID, noEdgeConstraint->constrainedToID )
										, std::max(noEdgeConstraint->constrainedFromID, noEdgeConstraint->constrainedToID )) );
			}
		}

		// get reverse node index mapping for left side nodes
		std::map<size_t,size_t> all2left;
		for (size_t i = 0; i< toUpdate.LeftSide.nodes.size(); ++i) {
			all2left[toUpdate.LeftSide.nodes.at(i)] = i;
		}

		  // identify all right side only edges
		std::set<Edge> rightEdges, leftEdges;
		const boost::property_map<CoreGraph, EdgeContextProperty>::type
			edgeContext = boost::get( EdgeContextProperty(), toUpdate.core );
		const boost::property_map<CoreGraph, NodeIndexProperty>::type
			nodeIndex = boost::get( NodeIndexProperty(), toUpdate.core );

		  // will hold the context of the source and target node of each edge
		size_t sourceID, targetID;

		  // iterate over all edges within the core graph
		CoreGraph::edge_iterator edge, edge_end;
		boost::tie(edge, edge_end) = boost::edges( toUpdate.core );
		for(; edge != edge_end; ++edge ) {
			  // check if non-context edge
			if (edgeContext[*edge] != RULE_CONTEXT) {
				  // get context of source and target node of this edge
				sourceID = nodeIndex[boost::source(*edge,toUpdate.core)];
				targetID = nodeIndex[boost::target(*edge,toUpdate.core)];
				  // abort the handling of this edges if not both source and
				  // target are part of left side pattern
				if ( all2left.find(sourceID) == all2left.end() || all2left.find(targetID) == all2left.end() ) {
					continue;
				}
				  // update node index information for left side pattern indexing
				sourceID = all2left[sourceID];
				targetID = all2left[targetID];
				Edge curEdge(std::min(sourceID,targetID),std::max(sourceID,targetID));
				  // check if there exists already a NoEdge constraint
				if ( constrained.find(curEdge) == constrained.end()) {
					  // store edge information in according container
					if (edgeContext[*edge] == RULE_RIGHT_SIDE) {
						rightEdges.insert(curEdge);
					} else {
						  // context should be RULE_LEFT_SIDE
						leftEdges.insert(curEdge);
					}
				}
			}
		}

		  // derive set of right-only edges
//		std::set_difference( rightEdges.begin(), rightEdges.end()
//							, leftEdges.begin(), leftEdges.end()
//							, std::inserter(rightOnlyEdges, rightOnlyEdges.end()) );
		for (std::set<Edge>::const_iterator toInsert = rightEdges.begin(); toInsert != rightEdges.end(); ++toInsert) {
			  // check if right edge if only in right context
			if (leftEdges.find(*toInsert) != leftEdges.end()) {
				continue;
			}
			  // add according NoEdge constraint
			toUpdate.LeftSide.constraints.push_back( new sgm::MC_NoEdge(toInsert->first,toInsert->second) );
		}


	}
//##############################################################################

	inline
	const std::string*
	ChemRule::
	getUsedWildcard(void) const
	{
		return &MoleculeUtil::AtomLabelWildcard;
	}

	inline
	void
	ChemRule::
	setUsedWildcard( const std::string* const wildcardToUse )
	{
		// do nothing since chemical wildcard is fixed to AtomLabelWildcard
	}

//##############################################################################

  } // namespace chem
} // namespace ggl
