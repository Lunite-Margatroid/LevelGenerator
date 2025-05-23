

#include "sgm/GM_vf2.hh"
#include "sgm/SGM_vf2.hh"

namespace ggl {
namespace chem {

//////////////////////////////////////////////////////////////////////////////


	inline
	EC_MoleculeDecomposition
	::EC_MoleculeDecomposition()
	 :	fullMatcher(new sgm::GM_vf2())
		, subMatcher(new sgm::SGM_vf2())
		, decompositionHandler( new MoleculeDecomposition(*fullMatcher, *subMatcher))
	{
	}

//////////////////////////////////////////////////////////////////////////////


	inline
	EC_MoleculeDecomposition
	::EC_MoleculeDecomposition( const EC_MoleculeDecomposition& toCopy)
	 :	fullMatcher(new sgm::GM_vf2())
		, subMatcher(new sgm::SGM_vf2())
		, decompositionHandler( new MoleculeDecomposition(*fullMatcher, *subMatcher))
	{
	}

//////////////////////////////////////////////////////////////////////////////


	inline
	EC_MoleculeDecomposition
	::~EC_MoleculeDecomposition()
	{
		delete decompositionHandler; decompositionHandler = NULL;
		delete subMatcher; subMatcher = NULL;
		delete fullMatcher; fullMatcher = NULL;
	}

//////////////////////////////////////////////////////////////////////////////


	inline
	EC_MoleculeDecomposition &
	EC_MoleculeDecomposition
	::operator = ( const EC_MoleculeDecomposition& toCopy)
	{
		// only the matchers/handler are to copy but this is obsolete ...
		  //! access to the (non)-changed instance
		return *this;
	}

//////////////////////////////////////////////////////////////////////////////


	inline
	double
	EC_MoleculeDecomposition
	::getEnergy( const Molecule & mol ) const
	{
		  // forward energy computation to the decomposition handler
		return decompositionHandler->getEnergy( mol );
	}

}  // namespace chem
} // namespace ggl
