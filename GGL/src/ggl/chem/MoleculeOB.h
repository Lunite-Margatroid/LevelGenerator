

#include <openbabel/babelconfig.h>
#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/forcefield.h>


#include <sstream>
#include <iostream>
#include <limits>
#include <exception>
#include <stdexcept>

#include "ggl/chem/Molecule.hh"
#include "ggl/chem/MoleculeUtil.hh"


namespace ggl {
namespace chem {

	/////////////////////////////////////////////////////////////////////////

	inline
	MoleculeOB::
	MoleculeOB( const ggl::chem::Molecule & mol )
	  : curMol(convert(mol))
	{}

	/////////////////////////////////////////////////////////////////////////

	inline
	double
	MoleculeOB::
	getMolWeight( const bool implicitH ) {

		return curMol.GetMolWt(implicitH);
	}

	/////////////////////////////////////////////////////////////////////////

	inline
	double
	MoleculeOB::
	getMolEnergy() {
		// request according force field
		OpenBabel::OBForceField* pFF = OpenBabel::OBForceField::FindForceField("MMFF94");
		// ensure force field loading was successful
		if ( pFF == NULL )
			return std::numeric_limits<double>::signaling_NaN();

		// run force field setup
		const bool setupOK = pFF->Setup(curMol);
		assert( setupOK /*ensure setup is working*/);

		// final settings
		pFF->ConjugateGradients(10000);

		// calculate energy
		double energy = pFF->Energy(false);

		// calculate appropriate unit scaling
		std::string unit = pFF->GetUnit();
		if (unit == "kcal/mol")
			return energy * 4.184;  // convert kcal -> kJ
		else
			return energy;
	}

	/////////////////////////////////////////////////////////////////////////

	inline
	OpenBabel::OBMol
	MoleculeOB::
	convert( const Molecule & mol ) {

//		  // remove protons
//		Molecule m;
//		MoleculeUtil::copy(mol, m);
//		MoleculeUtil::removeProtons(m);

		  // get CML representation of the molecule
		std::stringstream molCML;
//		MoleculeUtil::convertCML( m, molCML );
		MoleculeUtil::convertCML( mol, molCML );

		  // set up converter
		OpenBabel::OBConversion conv(NULL,NULL);

		OpenBabel::OBMol curMol;
		  // setup conversion formats
		if(conv.SetInAndOutFormats("CML","CML"))
		{
			  // fill internal OBMol object
			conv.Read( &curMol, &molCML );
		}
		assert(curMol.NumAtoms()>0);

		return curMol;
	}

	/////////////////////////////////////////////////////////////////////////

	inline
	Molecule
	MoleculeOB::
	convert( const OpenBabel::OBMol & mol ) {

		Molecule ret;
		Molecule::vertex_descriptor node;
		boost::property_map<	Molecule, PropNodeLabel >::type
			nodeLabel = boost::get( PropNodeLabel(), ret );


	   const std::string aSymb[121] = {"0",
		    "H" ,"He","Li","Be","B" ,"C" ,"N" ,"O" ,"F" ,"Ne",
		    "Na","Mg","Al","Si","P" ,"S" ,"Cl","Ar","K" ,"Ca",
		    "Sc","Ti","V" ,"Cr","Mn","Fe","Co","Ni","Cu","Zn",
		    "Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y" ,"Zr",
		    "Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn",
		    "Sb","Te","I" ,"Xe","Cs","Ba","La","Ce","Pr","Nd",
		    "Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb",
		    "Lu","Hf","Ta","W" ,"Re","Os","Ir","Pt","Au","Hg",
		    "Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th",
		    "Pa","U" ,"Np","Pu","Am","Cm","Bk","Cf","Es","Fm",
		    "Md","No","Lr","D" ,""  ,"G" ,"0" ,"Xx",""  ,""  ,
		    "M" ,"X" ,"A" ,"Q" ,""  ,""  ,""  ,""  ,""  ,""};

		  // create atoms and set label
		for (size_t i=0; i<mol.NumAtoms(); ++i) {
			  // get atom data
			OpenBabel::OBAtom * atom = mol.GetAtom(i+1);
			assert( atom != NULL );
			assert( atom->GetAtomicNum() < 121 );
			  // check for unknown atom label
			if (atom->GetAtomicNum() == 0
					|| aSymb[atom->GetAtomicNum()] == "0"
					|| aSymb[atom->GetAtomicNum()] == "" )
			{
				throw std::runtime_error(" ERROR : MoleculeOB::convert(OBMol) : atom label is unknown");
			}
			  // create new node and set node label
			node = boost::add_vertex(ret);
			nodeLabel[node] = MoleculeUtil::getComplexAtomLabel( aSymb[atom->GetAtomicNum()], 0, atom->GetFormalCharge() );
		}

		Molecule::edge_descriptor edge;
		boost::property_map<	Molecule, PropEdgeLabel >::type
			edgeLabel = boost::get( PropEdgeLabel(), ret );
		const MoleculeUtil::BondDataMap& bondData = MoleculeUtil::getBondData();
		MoleculeUtil::BondDataMap::const_iterator bData;

		  // create all bonds
		for (size_t i = 0; i<mol.NumBonds(); ++i) {
			  // get bond data
			const OpenBabel::OBBond * b = mol.GetBond(i);
			assert(b != NULL);
			  // create edge
			assert(b->GetBeginAtomIdx() <= boost::num_vertices(ret));
			assert(b->GetBeginAtomIdx() > 0);
			assert(b->GetEndAtomIdx() <= boost::num_vertices(ret));
			assert(b->GetEndAtomIdx() > 0);
			edge = boost::add_edge( boost::vertex(b->GetBeginAtomIdx()-1, ret)
								, boost::vertex(b->GetEndAtomIdx()-1, ret)
								, ret ).first;
			  // set bond label
			bool isAromatic = b->IsAromatic();
			MoleculeUtil::OneByte order = MoleculeUtil::OneByte(b->GetBondOrder());
			bData = bondData.begin();
			while( bData != bondData.end()) {
				if (	(isAromatic && bData->second.isAromatic == 1)
					|| (!isAromatic && bData->second.valence == order) )
				{
					  // set edge label
					edgeLabel[edge] = bData->first;
					  // break bond data iteration
					break;
				}
				++bData;
			}
			if (bData == bondData.end()) {
				throw std::runtime_error(" ERROR : MoleculeOB::convert(OBMol) : bond order-aromaticity combination is unknown");
			}
		}

		return ret;
	}

	/////////////////////////////////////////////////////////////////////////


} // namespace chem
} // namespace ggl


