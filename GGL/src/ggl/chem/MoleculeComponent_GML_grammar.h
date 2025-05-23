
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <limits>

#include <boost/lexical_cast.hpp>

#include "ggl/chem/MoleculeUtil.hh"

namespace ggl {
namespace chem {


//##############################################################################


	inline
	MoleculeComponent_GML_grammar
	::MoleculeComponent_GML_grammar( MoleculeComponent& toFill )
	  : toFill(toFill)
	{
	}

	
//##############################################################################
		


	inline
	std::pair< MoleculeComponent, int >
	MoleculeComponent_GML_grammar
    ::parseGML( const std::string & GML_string ) throw (std::invalid_argument)
    {
		 // the object to fill
    	MoleculeComponent toFill;
    	
		// create grammar object
		MoleculeComponent_GML_grammar gml_grammar(toFill);
		
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

			  // reset to empty object
			toFill = MoleculeComponent();
			  // give parsing error 
			return std::pair<MoleculeComponent, int>(toFill
								, (int)(info.stop-GML_string.begin()));
		}
		
		// return filled graph
		return std::pair<MoleculeComponent, int>(toFill, -1);
    }
		
	
//##############################################################################
	

	template <	typename ScannerT >  // definition template arguments
	inline
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::definition(const MoleculeComponent_GML_grammar & self)
	  :	toFill(self.toFill)
		, nodeLabel(boost::get( PropNodeLabel(), toFill.pattern ))
		, edgeLabel(boost::get( PropEdgeLabel(), toFill.pattern ))
	{
		using namespace NS_BOOSTSPIRIT;
		using namespace phoenix;
		

		molcomp
		=	(str_p("molcomp")[phoenix::bind(&definition::clear_toFill)(var(*this))]
		 	>> ch_p('[')
			>> +(content)
			>>ch_p(']'))[phoenix::bind(&definition::final_checks)(var(*this))]
		  ;

		content
		=	("description" >> confix_p('"', (*~ch_p('"'))[assign_a(toFill.description)], '"') )
		|	("priority" >> uint_p[assign_a(toFill.priority)])
		|	("energy" >> real_p[assign_a(toFill.freeEnergy)])
		|	(node)
		|	(edge)
		|	(compIDs)
		|	(constrainAdjacency)
		|	(constrainLabel)
		|	(ringFragment)
			;

		node
		=	(str_p("node") >>ch_p('[')
			>>str_p("id") >>int_p[assign_a(curNodeID)]
			>>str_p("label") >>confix_p('"', (*~ch_p('"'))[assign_a(curNodeLabel)], '"')
			>>ch_p(']'))[phoenix::bind(&definition::store_node)(var(*this))]
			;

		edge
		=	(str_p("edge") >>ch_p('[')
			>>str_p("source") >> int_p[assign_a(curEdgeFromID)]
			>>str_p("target") >> int_p[assign_a(curEdgeToID)]
			>>str_p("label") >> confix_p('"', (*~ch_p('"'))[assign_a(curEdgeLabel)], '"')
			>>ch_p(']'))[phoenix::bind(&definition::store_edge)(var(*this))]
			;

		compIDs
		=	str_p("compIDs") >>ch_p('[')
				>> +(str_p("id") >>int_p[assign_a(curNodeID)])
					[phoenix::bind(&definition::insert_to_list)(var(*this),Fill_compIDs)]
			>>ch_p(']')
			;

		ringFragment
		=	str_p("ringFragment") >>ch_p('[')
				>> +(str_p("id") >>int_p[push_back_a(curRingFragmentList)])
				>> str_p("type")
						>>( str_p("aromaticHydrocarbon")[assign_a(curRingFragmentTypeString)]
							|| str_p("heteroaromatic")[assign_a(curRingFragmentTypeString)]
							|| str_p("nonaromatic")[assign_a(curRingFragmentTypeString)])
			>>ch_p(']')[phoenix::bind(&definition::insert_to_list)(var(*this),Fill_ringFragments)]
			;

		constrainAdjacency
		=	(str_p("constrainAdj") >>ch_p('[')
			>>str_p("id") >> int_p[assign_a(constrAdj.constrainedNodeID)]
			>>str_p("op") >>(ch_p('=')[assign_a(constrAdjOp)] || ch_p('<')[assign_a(constrAdjOp)] || ch_p('>')[assign_a(constrAdjOp)])
			>>str_p("count") >> uint_p[assign_a(constrAdj.count)]
			>> *(str_p("nodeLabels") >>ch_p('[')
					>> *(str_p("label") >> confix_p('"', (*~ch_p('"'))[assign_a(curNodeLabel)], '"'))
						[phoenix::bind(&definition::insert_to_list)(var(*this),Fill_constrAdj_NL)]
				>>ch_p(']'))
			>> *(str_p("edgeLabels") >>ch_p('[')
					>> *(str_p("label") >> confix_p('"', (*~ch_p('"'))[assign_a(curEdgeLabel)], '"'))
						[phoenix::bind(&definition::insert_to_list)(var(*this),Fill_constrAdj_EL)]
				>>ch_p(']'))
			>>ch_p(']'))[phoenix::bind(&definition::store_constrAdj)(var(*this))]
			;


		constrainLabel
		=	(str_p("constrainNode") >>ch_p('[')
			>>str_p("id") >> int_p[assign_a(constrLabel.constrainedNodeID)]
			>>*(str_p("op") >>(ch_p('=')[assign_a(constrLabelOp)] || ch_p('!')[assign_a(constrLabelOp)]))
			>> str_p("nodeLabels") >>ch_p('[')
				>> +(str_p("label") >> confix_p('"', (*~ch_p('"'))[assign_a(curNodeLabel)], '"'))
					[phoenix::bind(&definition::insert_to_list)(var(*this),Fill_constrLabel_NL)]
			>>ch_p(']')
			>>ch_p(']'))[phoenix::bind(&definition::store_constrLabel)(var(*this))]
			;

	}
	
//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	NS_BOOSTSPIRIT::rule<ScannerT> const&
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::start() const 
	{ 
		return molcomp;
	}
	

//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::clear_toFill(void)
	{
		  // reset data to undefined states
		toFill.description = std::string("");
		toFill.priority = std::numeric_limits<size_t>::signaling_NaN();
		toFill.freeEnergy = std::numeric_limits<double>::signaling_NaN();
		toFill.compIDs.clear();
		if ( ! toFill.constraints.empty() ) {
			for ( MoleculeComponent::ConstraintVec::iterator c = toFill.constraints.begin();
					c != toFill.constraints.end(); ++c)
			{
				delete (*c);
			}
			toFill.constraints.clear();
		}
		if ( boost::num_vertices( toFill.pattern ) != 0 ) {
			toFill.pattern = MoleculeComponent::PatternGraph();
		}
	}


//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::final_checks(void) throw (std::invalid_argument)
	{
		  // check if each mandatory member was filled
		if ( toFill.description.empty() ) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"no description given or empty string");
		}
		if ( toFill.compIDs.empty() ) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"no compIDs given");
		} else {
			 // update compID ids due to new node mapping
			MoleculeComponent::NodeSet mappedCompIDs;
			for (MoleculeComponent::NodeSet::const_iterator id = toFill.compIDs.begin(); id != toFill.compIDs.end(); ++id) {
				  // check if id was present in the pattern graph
				if (nodeMapping.find(*id) == nodeMapping.end()) {
					throw std::invalid_argument("MoleculeComponent_GML_grammar : "
							"compID " + boost::lexical_cast<std::string>(*id) +
							" is not among the indices");
				}
				  // add mapped node id
				mappedCompIDs.insert(nodeMapping.find(*id)->second);
			}
			  // set final compID data
			toFill.compIDs = mappedCompIDs;
		}
		if ( boost::num_vertices( toFill.pattern ) == 0 ) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"no pattern graph given");
		}
		if (!toFill.ringFragments.empty()) {
			  // update ring fragment ids according to new node mapping
			for (size_t frag = 0; frag < toFill.ringFragments.size(); ++frag) {
				MoleculeComponent::RingFragmentList newRingFrag(toFill.ringFragments.at(frag).fragment.size(),0);
				for (size_t i = 0; i < newRingFrag.size(); ++i ) {
					  // check if id was present in the pattern graph
					if (nodeMapping.find(toFill.ringFragments.at(frag).fragment.at(i)) == nodeMapping.end()) {
						throw std::invalid_argument("MoleculeComponent_GML_grammar : "
								"compID " + boost::lexical_cast<std::string>(toFill.ringFragments.at(frag).fragment.at(i)) +
								" is not among the indices");
					}
					  // set mapped id
					newRingFrag[i] = nodeMapping.find(toFill.ringFragments.at(frag).fragment.at(i))->second;
				}
				  // store final ring fragment data
				toFill.ringFragments[frag].fragment = newRingFrag;
			}
		}

	}


//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::store_node(void) throw (std::invalid_argument)
	{
			  // check if node ID is unique
		if (nodeMapping.find(curNodeID) != nodeMapping.end()) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"nodeID " + boost::lexical_cast<std::string>(curNodeID) +
					" is not unique");
		}
		  // check if atom label is ok
		if ( ! MoleculeUtil::isValidAtomLabel( curNodeLabel ) ) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"node with ID " + boost::lexical_cast<std::string>(curNodeID) +
					" shows non-supported atom label '"
					+ curNodeLabel +"'");
		}
		  // check if atom label contains implicit protons
		if ( MoleculeUtil::getAtom(curNodeLabel).compare("H") != 0
				&& MoleculeUtil::getProtons( curNodeLabel ) > 0 )
		{
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"node with ID " + boost::lexical_cast<std::string>(curNodeID) +
					" shows implicit protons within atom label, currently not supported");
		}
		  // store node index mapping
		const size_t newID = nodeMapping.size();
		nodeMapping[curNodeID] = newID;
		  // add new vertex
		MoleculeComponent::PatternGraph::vertex_descriptor newVertex
			= boost::add_vertex( toFill.pattern );
		  // store label information
		nodeLabel[newVertex] = curNodeLabel;
	}


//##############################################################################


	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::store_edge(void) throw (std::invalid_argument)
	{
		  // check if node ID is already known
		if (nodeMapping.find(curEdgeFromID) == nodeMapping.end()) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"edge source ID " + boost::lexical_cast<std::string>(curEdgeFromID) +
					" is not known so far");
		}
		  // check if node ID is already known
		if (nodeMapping.find(curEdgeToID) == nodeMapping.end()) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"edge target ID " + boost::lexical_cast<std::string>(curEdgeToID) +
					" is not known so far");
		}
		  // check if bond label is ok
		if ( ! MoleculeUtil::isValidBondLabel( curEdgeLabel )
			&& MoleculeUtil::AtomLabelWildcard.compare(curEdgeLabel) != 0 )
		{
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"edge from " + boost::lexical_cast<std::string>(curEdgeFromID) +
					"to " + boost::lexical_cast<std::string>(curEdgeToID) +
					" shows non-supported edge label '"
					+ curEdgeLabel +"'");
		}
		  // try to access edge to check if already existing
		std::pair< MoleculeComponent::PatternGraph::edge_descriptor, bool>
			newEdge = boost::edge(	boost::vertex( nodeMapping[curEdgeFromID], toFill.pattern )
									, boost::vertex( nodeMapping[curEdgeToID], toFill.pattern )
									, toFill.pattern );
		  // check if new edge exists already
		if ( newEdge.second ) {
			throw std::invalid_argument("MoleculeComponent_GML_grammar : "
					"edge from " + boost::lexical_cast<std::string>(curEdgeFromID) +
					"to " + boost::lexical_cast<std::string>(curEdgeToID) +
					" is not unique");
		} else {
			  // add new edge
	  		newEdge = boost::add_edge(	boost::vertex( nodeMapping[curEdgeFromID], toFill.pattern )
										, boost::vertex( nodeMapping[curEdgeToID], toFill.pattern )
										, toFill.pattern );
	  		  // store label information
	  		edgeLabel[newEdge.first] = curEdgeLabel;
		}

	}


//##############################################################################



	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::store_constrAdj(void)
	{
		  // set the operator accordingly
		switch (constrAdjOp) {
			case '=': constrAdj.op = MC_MC_NodeAdjacency::MC_EQ; break;
			case '<': constrAdj.op = MC_MC_NodeAdjacency::MC_L; break;
			case '>': constrAdj.op = MC_MC_NodeAdjacency::MC_G; break;
			default:
				break;
		}
		  // copy adjacency constraint to constraint storage
		toFill.constraints.push_back(constrAdj.clone());

		  // clear data structure for next filling
		constrAdj.nodeLabels.clear();
		constrAdj.edgeLabels.clear();
	}


//##############################################################################



	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::store_constrLabel(void)
	{
		  // set the operator accordingly
		switch (constrLabelOp) {
			case '=': constrLabel.compareType = MC_MC_NodeLabel::ALLOWED; break;
			case '!': constrLabel.compareType = MC_MC_NodeLabel::FORBIDDEN; break;
			default:
				break;
		}
		  // copy adjacency constraint to constraint storage
		toFill.constraints.push_back(constrLabel.clone());

		  // clear data structure for next filling
		constrLabel.nodeLabels.clear();
		constrLabel.constrainedNodeID = UINT_MAX;
		constrLabel.compareType = MC_MC_NodeLabel::ALLOWED;
	}


//##############################################################################



	template <	typename ScannerT >  // definition template arguments
	inline
	void
	MoleculeComponent_GML_grammar
	::definition< ScannerT >
	::insert_to_list( WhatList list )
	{
		  // add to choosen list
		switch (list) {
			case Fill_constrAdj_NL:
				constrAdj.nodeLabels.insert(curNodeLabel);
				break;
			case Fill_constrAdj_EL:
				constrAdj.edgeLabels.insert(curEdgeLabel);
				break;
			case Fill_constrLabel_NL:
				constrLabel.nodeLabels.insert(curNodeLabel);
				break;
			case Fill_compIDs:
				toFill.compIDs.insert(curNodeID);
				break;
			case Fill_ringFragments: {
				  // setup ring type
				MoleculeComponent::RingFragmentType curRingFragmentType = MoleculeComponent::RF_undefined;
				if (curRingFragmentTypeString.compare("aromaticHydrocarbon")==0)
					curRingFragmentType = MoleculeComponent::RF_aromaticHydrocarbon;
				else if (curRingFragmentTypeString.compare("heteroaromatic")==0)
					curRingFragmentType = MoleculeComponent::RF_heteroaromatic;
				else if (curRingFragmentTypeString.compare("nonaromatic")==0)
					curRingFragmentType = MoleculeComponent::RF_nonaromatic;
				assert(curRingFragmentType != MoleculeComponent::RF_undefined);
				  // store ring fragment
				toFill.ringFragments.push_back(MoleculeComponent::RingFragment(curRingFragmentType,curRingFragmentList));
				  // clear fragement information
				curRingFragmentList.clear();
				curRingFragmentTypeString = "";
				break;}
			default:
				break;
		}
	}


//##############################################################################

} // namespace chem
} // namespace ggl

