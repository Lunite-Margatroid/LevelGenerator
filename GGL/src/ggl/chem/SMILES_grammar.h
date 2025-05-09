
#include <iostream>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

namespace ggl {
  namespace chem {
  
//##############################################################################


	inline
	SMILES_grammar
	::SMILES_grammar( Molecule& toFill )
	  : g2fill(toFill)
		, groups( NULL )
		, nodeLabel(boost::get( PropNodeLabel(), g2fill ))
		, edgeLabel(boost::get( PropEdgeLabel(), g2fill ))
	{
	}



//##############################################################################


	inline
	SMILES_grammar
	::SMILES_grammar( Molecule& toFill, const GroupMap & groups_ )
	  : g2fill(toFill)
		, groups( &groups_ )
		, nodeLabel(boost::get( PropNodeLabel(), g2fill ))
		, edgeLabel(boost::get( PropEdgeLabel(), g2fill ))
	{
	}

	
	
//##############################################################################
		


	inline
	std::pair< Molecule, int >
	SMILES_grammar
    ::parseSMILES( const std::string & SMILES_string )
	throw (std::invalid_argument)
    {
		 // the graph to fill
    	Molecule toFill;
	
		// create grammar object
    	SMILES_grammar smiles_grammar(toFill);

		// parse smiles string into graph 
		NS_BOOSTSPIRIT::parse_info<std::string::const_iterator>
			info = NS_BOOSTSPIRIT::parse( SMILES_string.begin()
										, SMILES_string.end()
										, smiles_grammar);
	
		// check if parsing was successful
		if (!info.full) {
			  // reset molecule graph
			toFill = Molecule();
			  // give parsing error 
			return std::pair<Molecule, int>(toFill
								, (int)(info.stop-SMILES_string.begin()));
		}

		// return filled molecule graph
		return std::pair<Molecule, int>(toFill, -1);
    }
	
//##############################################################################
		


	inline
	std::pair< Molecule, int >
	SMILES_grammar
    ::parseSMILES( const std::string & SMILES_string, const GroupMap& groups )
	throw (std::invalid_argument)
    {
		 // the graph to fill
    	Molecule toFill;

		// create grammar object
    	SMILES_grammar smiles_grammar(toFill, groups);

		// parse smiles string into graph
		NS_BOOSTSPIRIT::parse_info<std::string::const_iterator>
			info = NS_BOOSTSPIRIT::parse( SMILES_string.begin()
										, SMILES_string.end()
										, smiles_grammar);

		// check if parsing was successful
		if (!info.full) {
			  // reset molecule graph
			toFill = Molecule();
			  // give parsing error
			return std::pair<Molecule, int>(toFill
								, (int)(info.stop-SMILES_string.begin()));
		}

  		// replace all group ID nodes with according molecule group subgraphs
		ggl::chem::MoleculeUtil::insertGroups( toFill, groups );

		// return filled molecule graph
		return std::pair<Molecule, int>(toFill, -1);
    }

//##############################################################################



	inline
	void
	SMILES_grammar
	::addAtom( const std::string& label ) const
	{
		  // insert node
		Molecule::vertex_descriptor newVertex
						= boost::add_vertex( g2fill );
		  // set node label
		nodeLabel[newVertex] = label;
	}
	
//##############################################################################
		


	inline
	void
	SMILES_grammar
	::addBond( const int atom1, const int atom2, const std::string& label )const
  	{
	  	  // insert edge
	  	Molecule::edge_descriptor newEdge
	  		= boost::add_edge(	boost::vertex( atom1, g2fill )
	  							, boost::vertex( atom2, g2fill )
	  							, g2fill ).first;
	  	  // set edge label
	  	edgeLabel[newEdge] = label;
  	}
	

//##############################################################################


    template <	typename ScannerT >  // definition template arguments
	inline
	SMILES_grammar
	::definition< ScannerT >
	::definition( SMILES_grammar const& self_)
	  :	self(self_)
	{
		reset_data_structures();
		using namespace NS_BOOSTSPIRIT;
		using namespace phoenix;
				
       smiles
 	=  *(space_p) >> (
 			(chain
			>> *(chain | branch)
			)[phoenix::bind(&definition::add_explicit_hydrogens)(var(*this))]
			 [phoenix::bind(&definition::reset_data_structures)(var(*this))]
	    ) >> *(space_p)
 	;
       
       chain
 	=  (!(bond)
 	>> (simple_atom | complex_atom)
 	    [phoenix::bind(&definition::memorize_atom)
 	     (var(*this),chain.cnt,chain.alabel,chain.blabel)]
 	    [(chain.blabel=std::string(""))]
 	>> *(ringclosure
 			[phoenix::bind(&definition::memorize_rc)
 			 (var(*this),chain.rc,chain.cnt,chain.blabel)]
 			[(chain.blabel=std::string(""))]
 			 ))
 	;

       branch
 	=  ch_p('(')[phoenix::bind(&definition::open_branch)
 		     (var(*this),branch.cnt)]
 	>> chain
 	>> *(branch | chain)
 	>> ch_p(')')[phoenix::bind(&definition::close_branch)
 		     (var(*this))]
 	;
       
       ringclosure
 	=  (!(bond)
 		>> digit_p[(chain.rc = val(0)),(chain.rc = construct_<int>(arg1-'0'))])
 	| (!(bond)
		>> ch_p('%')
		>> digit_p[(chain.rc = val(0)),(chain.rc = val(10)*construct_<int>(arg1-'0'))]
		>> digit_p[chain.rc += construct_<int>(arg1-'0')])
 	;
       
       simple_atom
 	= simple_symbol[(chain.alabel = construct_<std::string>(arg1,arg2)),
 			(chain.cnt = ++var(atom_count))]
 	;
       
       chirality
 	=  ch_p('@')
 	>> !(ch_p('@'))
 	;

       hcount
	=  ch_p('H')[chain.hcnt = val(1)]
	 >> *(int_p)[chain.hcnt += (arg1-1)]
 	;

       name
 	=  ch_p(':')
 	>> +(int_p)
 	;

       charge
 	= (ch_p('+') >> *(+(ch_p('+')) | int_p))
 	| (ch_p('-') >> *(+(ch_p('-')) | int_p))
 	;

       isotope
 	= int_p
 	;
       
       complex_atom
	 =  ch_p('[') [chain.alabel = construct_<std::string>("")]
	 >> *(isotope)[phoenix::bind(&definition::parser_warning)
		       (var(*this),"[Complex Atom] isotope number is ignored !")]
	 >> (complex_symbol | group_symbol)[(chain.alabel += construct_<std::string>(arg1,arg2)),
 			  (chain.cnt = ++var(atom_count))]
	 >> !(chirality)[phoenix::bind(&definition::parser_warning)
		       (var(*this),"[Complex Atom] chirality information is ignored !")]
	 >> !(hcount)[phoenix::bind(&definition::memorize_explicit_H)
		      (var(*this),chain.cnt,chain.hcnt)]
	 >> !(charge)[(chain.alabel += construct_<std::string>(arg1,arg2))]
	 >> !(name)[(chain.alabel += construct_<std::string>(arg1,arg2))]
//	 >> !(name)[phoenix::bind(&definition::parser_warning)
//		   (var(*this),"[Complex Atom] class/name information is ignored !")]
	 >> ch_p(']') // [chain.alabel += construct_<std::string>("]")]
	 ;
       
       bond
 	= bond_symbol[chain.blabel = construct_<std::string>(arg1,arg2)]
 	;
       
       bond_symbol
 	= bond_p
 	;
       
       simple_symbol
 	=
	str_p("Br")
	| str_p("Cl")
 	| simpleSymbol_p
 	;
       
       // Order is reverse alphabetical to ensure longest match
       complex_symbol =
		( alpha_p[assign_a(atom2_firstChar)] >> atom2_parser(&atom2_firstChar) )
		| atom1_p
		;

	      group_symbol
		= (confix_p('{', (+anychar_p), '}'))
	      	;


 #ifdef _DEBUG_
     BOOST_SPIRIT_DEBUG_RULE(smiles);
     BOOST_SPIRIT_DEBUG_RULE(chain);
     BOOST_SPIRIT_DEBUG_RULE(branch);    
     BOOST_SPIRIT_DEBUG_RULE(bond);    
     BOOST_SPIRIT_DEBUG_RULE(simple_atom);
     BOOST_SPIRIT_DEBUG_RULE(complex_atom);
     BOOST_SPIRIT_DEBUG_RULE(ringclosure);
     BOOST_SPIRIT_DEBUG_RULE(simple_symbol);
     BOOST_SPIRIT_DEBUG_RULE(complex_symbol);
     BOOST_SPIRIT_DEBUG_RULE(bond_symbol);
     BOOST_SPIRIT_DEBUG_RULE(isotope);
     BOOST_SPIRIT_DEBUG_RULE(charge);
     BOOST_SPIRIT_DEBUG_RULE(chirality);
     BOOST_SPIRIT_DEBUG_RULE(hcount);
     BOOST_SPIRIT_DEBUG_RULE(name);
 #endif

	} // definition constructor


//##############################################################################
	

    template <	typename ScannerT >  // definition template arguments
	inline
	NS_BOOSTSPIRIT::rule<ScannerT> const&
	SMILES_grammar
	::definition< ScannerT >
	::start() const 
	{ 
		return smiles; 
	}


//##############################################################################

      // Semantic Actions

    template <	typename ScannerT >  // definition template arguments
  	inline
  	void
  	SMILES_grammar
  	::definition< ScannerT >
  	::memorize_atom(int atom1, std::string& alabel1, std::string& blabel)
  	  throw (std::invalid_argument)
  	{
		  // clean atom label, i.e. remove enclosing brackets if present
		std::string atomLabel = alabel1;
		if (	atomLabel.size()> 2
				&& atomLabel.at(0)=='['
				&& atomLabel.at(atomLabel.size()-1)==']')
		{
			  // remove enclosing brackets that are only needed within
			  // SMILES string encoding for label separation
			atomLabel = atomLabel.substr(1,atomLabel.size()-2);
		}
		  // check and replace occurences of "--" or "++"
		if (atomLabel.find("--") != std::string::npos) {
			atomLabel.replace(atomLabel.find("--"), 2, "-2");
		}
		else if (atomLabel.find("++") != std::string::npos) {
			atomLabel.replace(atomLabel.find("++"), 2, "+2");
		}

		  // get atom data
		const MoleculeUtil::AtomLabelData * atomData = MoleculeUtil::getAtomData(atomLabel);

  		  // check if atom label is known within MoleculeUtil
  		if (atomData == NULL) {
			// check if group
			// if group : get atom aromaticity from according proxy node of the group
			// else : throw error
  			if (	self.groups != NULL
  					&& MoleculeUtil::isGroupLabel(atomLabel)
  					&& self.groups->find( MoleculeUtil::getGroupLabel(atomLabel) ) != self.groups->end() )
  			{
  				  // get proxy node label
  				const MoleculeComponent & group = (self.groups->find(MoleculeUtil::getGroupLabel(atomLabel)))->second;
  				const std::string & proxyLabel = get( ggl::PropNodeLabel(), group.pattern) [boost::vertex( *(group.compIDs.begin()), group.pattern)];
  				  // get atom data of proxy node
  				atomData = MoleculeUtil::getAtomData( proxyLabel );
  			}

  			if (atomData == NULL) {
  				  // neither atom nor group label -> throw exception
				throw std::invalid_argument("SMILES_grammar : atom label '"
						+ atomLabel + "' is currently not supported. Check"
						" MoleculeUtil::AtomLabelData and available molecule groups.");
  			}
  		}

  		 // test if aromatic node
  		const bool isAromatic = atomData->isAromatic == 1;

  		atoms.push_back(AtomInfo(atomLabel,atom1,isAromatic));
  		// write atom to molecule graph
  		self.addAtom( atomLabel );

  		// std::cerr << atomLabel << " " << atom1 << std::endl;
  		if (stack.empty()) {
  			stack.push_back(atom1);
  		} else {
  			int atom2 = stack[stack.size()-1];
  			bond_t bond = std::make_pair(atom1,atom2);
			  // get final bond label
			std::string finalBlabel = blabel;
			  // handle that no bond label was set at all
			if (blabel.empty()) {
				  // check if connecting two aromatic atoms
				if (atoms[atom1-1].isAromatic && atoms[atom2-1].isAromatic) {
					finalBlabel = ":";
				} else {
					finalBlabel = "-";
				}
			}
			  // store bond information
  			bonds.push_back(std::make_pair(bond,finalBlabel));

  			// write bond to molecule graph
  			self.addBond( atom1-1, atom2-1, finalBlabel );
  			stack[stack.size()-1] = atom1;
  		}
  	}

//##############################################################################


    template <	typename ScannerT >  // definition template arguments
  	inline
  	void
  	SMILES_grammar
  	::definition< ScannerT >
  	::memorize_explicit_H( int atom, int hcount)
  	{
	  explicitH.push_back(std::make_pair(atom,hcount));
  	}


//##############################################################################
  	


    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
	::definition< ScannerT >
	::memorize_rc(int rc, int atom1, std::string blabel)
	 throw (std::invalid_argument)
	{
	    // SMILES allows that the bond symbol for a ring closure is
		// attached to either or both bonded atoms.

    	// check if ring closure ID is known
		rcs_t::iterator pos = rc_to_atom.find(rc);

		  // check if first occurrence of ring closure
		if (pos == rc_to_atom.end()) {
			rc_to_atom[rc] = atom1;
			rc_to_bond[rc] = blabel;
		}
		else {
			  // second occurrence of ring closure (WE HAVE TO CLOSE!!!!)
			int atom2   = rc_to_atom[rc];
			bond_t bond = std::make_pair(atom1,atom2);

			std::string finalBlabel = "";
			  // check if bond not set in first occurrence
			if (	!rc_to_bond[rc].empty()
					&& !blabel.empty()
					&& rc_to_bond[rc].compare(blabel) != 0 )
			{
				throw std::invalid_argument("SMILES_grammar : ring closing bond"
						" of closure with ID "
						+boost::lexical_cast<std::string>(rc)
						+" is specified with two different bond labels. '"
						+ blabel + "' != '"
						+ rc_to_bond[rc] + "'");
			} else {
				  // get final bond label
				finalBlabel = blabel.empty() ? rc_to_bond[rc] : blabel;
				  // handle that no bond label was set at all
				if (finalBlabel.empty()) {
					if (atoms[atom1-1].isAromatic && atoms[atom2-1].isAromatic) {
						finalBlabel = ":";
					} else {
						finalBlabel = "-";
					}
				}
			}
			  // store final bond label
			bonds.push_back(std::make_pair(bond,finalBlabel));

			// write bond to molecule graph
			self.addBond(atom1-1, atom2-1, finalBlabel);

			  // remove ring closure ID from open ring data storage
			rc_to_atom.erase(rc);
			rc_to_bond.erase(rc);
		}
	}
	
//##############################################################################
	


    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
    ::definition< ScannerT >
    ::open_branch(int atom)
    {
    	stack.push_back(stack[stack.size()-1]);
    }

//##############################################################################

	

    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
	::definition< ScannerT >
	::close_branch(void)
	{
		stack.pop_back();
	}

//##############################################################################

	

    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
	::definition< ScannerT >
	::reset_data_structures(void)
	{
		atom_count = 0;
		atoms = atoms_t();
		bonds = bonds_t();
		stack = stack_t();
		rc_to_atom = rcs_t();
		rc_to_bond = rcb_t();
		explicitH = hcount_t();
	}
      
//##############################################################################

	

    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
	::definition< ScannerT >
	::parser_warning(std::string msg)
	{
	  std::cerr << "Warning: SmilesParser: "
	            << msg
		    << std::endl;
	}

//##############################################################################

	

    template <	typename ScannerT >  // definition template arguments
	inline
	void
	SMILES_grammar
	::definition< ScannerT >
	::add_explicit_hydrogens(void)
	{
	  for (hcount_t::iterator i = explicitH.begin();
	       i != explicitH.end(); ++i ) {
	    for (int j = 1; j <= i->second; ++j) {
	      self.addAtom( "H" );
	      self.addBond( i->first-1, atom_count++, "-" );
	    }
	  }
	}
      
//##############################################################################
  
  }
}
