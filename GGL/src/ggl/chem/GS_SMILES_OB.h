
#include <boost/graph/connected_components.hpp>
#include <boost/graph/filtered_graph.hpp> 
#include <vector>
#include <cassert>

#include "ggl/chem/SMILESwriterOB.hh"


namespace ggl {
 namespace chem {

 
////////////////////////////////////////////////////////////////////////////////
///////////////////////   GS_SMILES_OB     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_TYPE
	::GS_SMILES_OB( STL_INSERTER insert_ )
	 :	insert( insert_ )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_TYPE
	::~GS_SMILES_OB()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_OB_TYPE
	::addMolecule( const Molecule & graph )
	{
		if (boost::num_vertices(graph) == 0)
			return;

		  // convert molecule to string representation
		std::string smiles = SMILESwriterOB::getSMILES( graph );

		size_t from = smiles.find_first_not_of(' ');
		 // check if string not empty
		if (from == smiles.npos) {
			break;
		}
		size_t to = smiles.find_first_of(' ',from);
		  // insert into storage
		*insert = smiles.substr(from, to-from);

	}

////////////////////////////////////////////////////////////////////////////////

 } // namespace chem
} //  namespace ggl
 

namespace ggl {
 namespace chem {


 ////////////////////////////////////////////////////////////////////////////////
 ////////////////////  GS_SMILES_OB_MOL::node_is_in_component  /////////////////////////
 ////////////////////////////////////////////////////////////////////////////////


 	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
 	inline
 	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
 	::node_is_in_component
 	::node_is_in_component()
 	 :	componentID(-1)
 	 	, componentVec(NULL)
 	 	, idxMap(NULL)
 	{
 		
 	}

 ////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
 	inline
 	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
 	::node_is_in_component
 	::node_is_in_component(	const int componentID_
 							, const ComponentIdVec& componentVec_
 							, const IndexMap& idxMap_)
 	 :	componentID(componentID_)
 	 	, componentVec(&componentVec_)
 	 	, idxMap(&idxMap_)
 	{ }
 	
 ////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
 	template <	typename VERTEX >
 	inline
 	bool
 	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
 	::node_is_in_component
 	::operator()( const VERTEX& node ) const 
 	{
 		return componentVec->at((size_t)boost::get(*idxMap,node)) == componentID;
 	}
  
////////////////////////////////////////////////////////////////////////////////
///////////////////////   GS_SMILES_OB_MOL     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
	::GS_SMILES_OB_MOL( SMILES_MOL_MAP& smiles2mol_ )
	 :	smiles2mol( &smiles2mol_ )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
	::~GS_SMILES_OB_MOL()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
	inline
	bool
	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
	::insert2map(const std::string & SMILES, const Molecule& graph )
	{
		  // check if already present
		if (smiles2mol->find(SMILES) == smiles2mol->end()) {
			smiles2mol->operator[](SMILES) = graph;
			return true;
		}
		return false;
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOL_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_OB_MOL_TYPE
	::addMolecule( const Molecule & graph )
	{
		if (boost::num_vertices(graph) == 0)
			return;

		// convert molecule to string representation
		std::string smiles = SMILESwriterOB::getSMILES( graph );

		  // insert into storage
		size_t from = smiles.find_first_not_of(' ');
		 // check if string not empty
		if (from == smiles.npos) {
			return;
		}
		size_t to = smiles.find_first_of(' ',from);
		  // insert into storage
		insert2map(smiles.substr(from, to-from), graph);
	}

////////////////////////////////////////////////////////////////////////////////

 } // namespace chem
} //  namespace ggl

#include <iostream>
namespace ggl {
 namespace chem {


 ////////////////////////////////////////////////////////////////////////////////
 ////////////////////  GS_SMILES_OB_MOLp::node_is_in_component  /////////////////////////
 ////////////////////////////////////////////////////////////////////////////////


 	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
 	inline
 	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
 	::node_is_in_component
 	::node_is_in_component()
 	 :	componentID(-1)
 	 	, componentVec(NULL)
 	 	, idxMap(NULL)
 	{
 		
 	}

 ////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
 	inline
 	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
 	::node_is_in_component
 	::node_is_in_component(	const int componentID_
 							, const ComponentIdVec& componentVec_
 							, const IndexMap& idxMap_)
 	 :	componentID(componentID_)
 	 	, componentVec(&componentVec_)
 	 	, idxMap(&idxMap_)
 	{ }
 	
 ////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
 	template <	typename VERTEX >
 	inline
 	bool
 	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
 	::node_is_in_component
 	::operator()( const VERTEX& node ) const 
 	{
 		return componentVec->at((size_t)boost::get(*idxMap,node)) == componentID;
 	}
  
////////////////////////////////////////////////////////////////////////////////
///////////////////////   GS_SMILES_OB_MOLp     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
	::GS_SMILES_OB_MOLp( SMILES_MOL_MAP& smiles2mol_ )
	 :	smiles2mol( &smiles2mol_ ), reportedHits(0)
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
	::~GS_SMILES_OB_MOLp()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
	inline
	bool
	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
	::insert2map(const std::string & SMILES, const Molecule& graph )
	{
		  // check if already present
		if (smiles2mol->find(SMILES) == smiles2mol->end()) {
			smiles2mol->operator[](SMILES) = new Molecule(graph);
			return true;
		}
		return false;
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_OB_MOLp_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_OB_MOLp_TYPE
	::add( const Molecule & graph )
	{
		reportedHits++;
		if (boost::num_vertices(graph) == 0)
			return;

		  // convert molecule to string representation
		std::string smiles = SMILESwriterOB::getSMILES( graph );
								
		size_t from = smiles.find_first_not_of(' ');
		 // check if string not empty
		if (from == smiles.npos) {
			return;
		}
		size_t to = smiles.find_first_of(' ',from);
		  // insert into storage
		insert2map(smiles.substr(from, to-from), graph);

	}

////////////////////////////////////////////////////////////////////////////////

 } // namespace chem
} //  namespace ggl
