
#include <boost/graph/connected_components.hpp>
#include <boost/graph/filtered_graph.hpp> 
#include <vector>
#include <cassert>


namespace ggl {
 namespace chem {


////////////////////////////////////////////////////////////////////////////////
///////////////////////   GS_SMILES     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_TYPE
	::GS_SMILES( STL_INSERTER insert_ )
	 :	insert( insert_ )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_TYPE
	::~GS_SMILES()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_TYPE
	::addMolecule( const Molecule & graph )
	{
		if (boost::num_vertices(graph) == 0)
			return;

		  // convert molecule to string representation
		  // NOTE: protons are ignored !
		std::string smiles = ggl::chem::SMILESwriter::getSMILES( graph, true );

		size_t from = smiles.find_first_not_of(' ');
		 // check if string not empty
		if (from == smiles.npos) {
			return;
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
///////////////////////   GS_SMILES_MOL     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_MOL_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOL_TYPE
	::GS_SMILES_MOL( SMILES_MOL_MAP& smiles2mol_ )
	 :	smiles2mol( &smiles2mol_ )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOL_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOL_TYPE
	::~GS_SMILES_MOL()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOL_TEMPLATE
	inline
	bool
	GGL_CHEM_GS_SMILES_MOL_TYPE
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

	GGL_CHEM_GS_SMILES_MOL_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_MOL_TYPE
	::addMolecule( const Molecule & graph )
	{
		if (boost::num_vertices(graph) == 0)
			return;

		  // convert molecule to string representation
		  // NOTE: protons are ignored !
		std::string smiles = ggl::chem::SMILESwriter::getSMILES( graph, true );
								
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
///////////////////////   GS_SMILES_MOLp     ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::GS_SMILES_MOLp( SMILES_MOL_MAP& smiles2mol_ )
	 :	smiles2mol( &smiles2mol_ )
	 	, smiles2molCheckOnly1(NULL)
	 	, smiles2molCheckOnly2(NULL)
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::GS_SMILES_MOLp( SMILES_MOL_MAP& smiles2mol_
						, const SMILES_MOL_MAP & smiles2molCheckOnly_  )
	 :	smiles2mol( &smiles2mol_ )
	 	, smiles2molCheckOnly1( &smiles2molCheckOnly_ )
	 	, smiles2molCheckOnly2( NULL )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::GS_SMILES_MOLp( SMILES_MOL_MAP& smiles2mol_
						, const SMILES_MOL_MAP & smiles2molCheckOnly1_ 
						, const SMILES_MOL_MAP & smiles2molCheckOnly2_  )
	 :	smiles2mol( &smiles2mol_ )
	 	, smiles2molCheckOnly1( &smiles2molCheckOnly1_ )
	 	, smiles2molCheckOnly2( &smiles2molCheckOnly2_ )
	{
	}



////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::~GS_SMILES_MOLp()
	{
	}


////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	bool
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::insert2map(const std::string & SMILES, const Molecule& graph )
	{
		bool notPresent = true;
		  // check if the current SMILES is present among the known SMILES
		if (smiles2molCheckOnly1 != NULL) {
			notPresent = smiles2molCheckOnly1->find(SMILES) == smiles2molCheckOnly1->end();
		}
		if (notPresent && smiles2molCheckOnly2 != NULL) {
			notPresent = smiles2molCheckOnly2->find(SMILES) == smiles2molCheckOnly2->end();
		}
		  // check if already present in
		if (notPresent && smiles2mol->find(SMILES) == smiles2mol->end()) {
			smiles2mol->operator[](SMILES) = new Molecule(graph);
			return true;
		}
		return false;
	}

////////////////////////////////////////////////////////////////////////////////

	GGL_CHEM_GS_SMILES_MOLp_TEMPLATE
	inline
	void
	GGL_CHEM_GS_SMILES_MOLp_TYPE
	::addMolecule( const Molecule & graph )
	{
		if (boost::num_vertices(graph) == 0)
			return;

		  // convert molecule to string representation
		  // NOTE: protons are ignored !
		std::string smiles = ggl::chem::SMILESwriter::getSMILES( graph, true );

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
