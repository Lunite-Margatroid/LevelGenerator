#ifndef UTILPRINTRULE_ICC_
#define UTILPRINTRULE_ICC_
	

#include <iostream>
#include <iomanip>

#include "ggl/Rule.hh"
#include "ggl/RuleGraph.hh"

#include "utilPrintGraph_Interface.h"

	void
	printRule ( const ggl::Rule& r ) {
		
		std::cout <<"\n Rule ID  : '" <<r.getID() <<"'" <<std::endl;
		
		std::cout <<"\n LeftSide :\nnodes = ";
		std::copy(	r.getLeftSide().nodes.begin(), 
					r.getLeftSide().nodes.end(), 
					std::ostream_iterator<size_t>(std::cout, ", "));
		std::cout <<std::endl;
//		for (	ggl::edgeMap::const_iterator i = r.getLeftSide().outEdges.begin();
//				i != r.getLeftSide().outEdges.end(); i++) {
//			std::cout <<" " <<i->first <<" : ";
//			std::copy(	i->second.begin(),
//						i->second.end(),
//						std::ostream_iterator<size_t>(std::cout, ", "));
//			std::cout <<std::endl;
//		}
		
		std::cout <<"\n Context :\nnodes = ";
		std::copy(	r.getContext().nodes.begin(), 
					r.getContext().nodes.end(), 
					std::ostream_iterator<size_t>(std::cout, ", "));
		std::cout <<std::endl;
//		for (	ggl::edgeMap::const_iterator i = r.getContext().outEdges.begin();
//				i != r.getContext().outEdges.end(); i++) {
//			std::cout <<" " <<i->first <<" : ";
//			std::copy(	i->second.begin(),
//						i->second.end(),
//						std::ostream_iterator<size_t>(std::cout, ", "));
//			std::cout <<std::endl;
//		}
		
		std::cout <<"\n RightSide :\nnodes = ";
		std::copy(	r.getRightSide().nodes.begin(), 
					r.getRightSide().nodes.end(), 
					std::ostream_iterator<size_t>(std::cout, ", "));
		std::cout <<std::endl;
//		for (	ggl::edgeMap::const_iterator i = r.getRightSide().outEdges.begin();
//				i != r.getRightSide().outEdges.end(); i++) {
//			std::cout <<" " <<i->first <<" : ";
//			std::copy(	i->second.begin(),
//						i->second.end(),
//						std::ostream_iterator<size_t>(std::cout, ", "));
//			std::cout <<std::endl;
//		}
	}
	
	void
	printLeftSidePattern ( const ggl::Rule& r ) {
		
		std::cout <<"\n == LEFT_SIDE_PATTERN ==\n" <<std::endl;
		ggl::LeftSidePattern ls(r);
		
		print( ls ); std::cout.flush();
		
		std::cout	<<"\n symmetry breaking rules = " 
					<<ls.getGraphAutomorphism()
					<<std::endl;
		
	}
	
	void
	printRightSidePattern ( const ggl::Rule& r ) {
		
		std::cout <<"\n == RIGHT_SIDE_PATTERN ==\n" <<std::endl;
		ggl::RightSidePattern rs(r);
		
		print( rs ); std::cout.flush();
		
	}


#endif /*UTILPRINTRULE_ICC_*/
