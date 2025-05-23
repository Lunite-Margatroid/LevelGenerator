
namespace ggl {
 namespace chem {
 
//##############################################################################
 

	inline
	SMILESwriter
	::SMILESwriter()
	{
	}
	
//##############################################################################

	inline
	bool
	SMILESwriter
	::isWithBracketsInSMILES( const std::string& atom )
	{

		  // single letter atom label are without brackets
		if (organic_subset.find(atom) != organic_subset.end())
		{
			return false;
		}

		  // all other labels have to be enclosed in brackets
		return true;
	}


//##############################################################################

	inline
	std::string
	SMILESwriter
	::getSMILES( const Molecule& graph
				, const bool ignoreProtons
				, const bool allowWildcard )
	{
		return getSMILES( graph, NULL, ignoreProtons, allowWildcard );
	}

//##############################################################################

	inline
	std::string
	SMILESwriter
	::getSMILES( const Molecule& graph
				, const GroupMap & groups
				, const bool ignoreProtons
				, const bool allowWildcard )
	{
		  // compress groups within molecule
		Molecule mol(graph);
		MoleculeUtil::compressGroups( mol, groups );
		  // generate SMILES with groups
		return getSMILES( mol, &groups, ignoreProtons, allowWildcard );
	}


//##############################################################################

 		
 }  // namespace chem
}  // namespace ggl


