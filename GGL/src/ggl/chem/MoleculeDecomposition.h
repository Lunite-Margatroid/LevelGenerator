
#include <stdexcept>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include "sgm/Pattern.hh"
#include "sgm/Graph_boost.hh"
#include "sgm/MR_SymmBreak.hh"
#include "sgm/MR_Counting.hh"
#include "sgm/PA_OrderCheck.hh"
#include "sgm/RP_Hanser96.hh"

#include "ggl/chem/MoleculeUtil.hh"

namespace ggl {
 namespace chem {

//////////////////////////////////////////////////////////////////////////////

inline
MoleculeDecomposition
:: MoleculeDecomposition( sgm::GraphMatching & fullMatcher
							, sgm::SubGraphMatching & matcher )
 :	energy(0.0)
	, curComponent(NULL)
	, curMatchedIDs()
	, curMolRingNodes()
	, curMolRings()
	, reporter(NULL)
	, fullMatcher(&fullMatcher)
	, matcher(&matcher)
{
}


//////////////////////////////////////////////////////////////////////////////

inline
MoleculeDecomposition
:: MoleculeDecomposition(
						 sgm::GraphMatching & fullMatcher
						, sgm::SubGraphMatching & matcher
						, MoleculeDecomposition::DecompositionReporter & reporter )
 :	energy(0.0)
	, curComponent(NULL)
	, curMatchedIDs()
	, curMolRingNodes()
	, curMolRings()
	, reporter(&reporter)
	, fullMatcher(&fullMatcher)
	, matcher(&matcher)
{
}


//////////////////////////////////////////////////////////////////////////////


inline
MoleculeDecomposition
:: ~MoleculeDecomposition()
{
}

//////////////////////////////////////////////////////////////////////////////

 } // namespace chem
} // namespace ggl
