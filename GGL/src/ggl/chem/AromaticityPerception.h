
#include <cassert>
#include <cmath>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <sstream>

#include <boost/graph/copy.hpp>

#include "ggl/chem/MoleculeUtil.hh"


namespace ggl {
namespace chem {


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


	inline
	AromaticityPerception::
	AromaticityPerception()
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	AromaticityPerception::
	AromaticityPerception( const AromaticityPerception & toCopy )
	 :	aromaticEdges(toCopy.aromaticEdges),
	  	allRings(toCopy.allRings.size(),NULL)
	{
		  // make deep copy of rings
		for (size_t i=0; i<allRings.size(); ++i) {
			  // remove old element if present
			if (allRings[i] != NULL) {
				delete allRings[i];
			}
			  // copy new one
			allRings[i] = new RingDescriptor(*(toCopy.allRings.at(i)));
		}
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	AromaticityPerception::
	~AromaticityPerception()
	{
		clearData();
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	void
	AromaticityPerception::
	clearData()
	{
		  // clear aromatic rings of last perception
		aromaticEdges.clear();
		for (size_t i=0; i<allRings.size(); ++i) {
			if (allRings[i] != NULL) {
				delete allRings[i];
			}
		}
		allRings.clear();
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	void
	AromaticityPerception::
	reportRing(	const sgm::Graph_Interface& graph
				, const RingList & ringList )
	{
		  // store description
		allRings.push_back( new RingDescriptor( ringList ) );
	}

////////////////////////////////////////////////////////////////////////////////

}} // namespaces
