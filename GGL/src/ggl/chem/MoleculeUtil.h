
#include <cmath>
#include <climits>
#include <cstdlib>
#include <sstream>

#include <boost/graph/copy.hpp>
#include <boost/graph/connected_components.hpp>

namespace ggl {
	namespace chem {
	


//##############################################################################
		 

	
	inline
	MoleculeUtil
	::MoleculeUtil()
	{
	}
	
//##############################################################################
		 
	
	
	inline
	MoleculeUtil
	::~MoleculeUtil()
	{
	}

//##############################################################################
	 

	
	inline
	bool
	MoleculeUtil
	::isValidBondLabel( const std::string & label )
	{
		 // only check if label is within supported list
		return getBondData(label) != NULL;
	}
	
	
//##############################################################################



	inline
	bool
	MoleculeUtil
	::checkNonConnected
	( const Molecule & mol )
	{
		std::vector<int> component( boost::num_vertices(mol) );
		  // get number of connected components (and coloring)
		int numC = boost::connected_components(mol, &component[0]);
		  // check if only one component
		return numC == 1;
	}


//##############################################################################
 
	inline
	void
	MoleculeUtil
	::copy( const Molecule& m, Molecule & graph)
	{
		assert(boost::num_vertices(graph)==0 /*graph to fill is non-empty*/);
		// copy m into graph
		boost::copy_graph(m, graph);
	}
	

//##############################################################################

	inline
	std::string
	MoleculeUtil
	::convertCML( const Molecule& m )
	{
		  // convert via call redirection
		std::stringstream cml;
		convertCML(m, cml);
		  // return string CML representation
		return cml.str();
	}


//##############################################################################

  } //namespace chem
} // namespace ggl
