

#include <iostream>

#include "sgm/MR_stream.hh"
#include "sgm/Graph_boost.hh"

#include "dataSGMgraphs_1.h"

#include "utilPrintGraph_Interface.h"



int main(int argc, char** argv) {
	
	std::cout	<<"\n"
				<<"==============  BEGIN TEST  ==================\n" 
				<<"==============================================\n" 
				<<"              sgm::MR_stream  \n" 
				<<"==============================================\n" 
				<<std::endl;
	

	std::cout <<"--> create sgm::MR_stream(std::cout) mr\n" <<std::endl;
	sgm::MR_stream mr(std::cout);
	
	typedef sgm::Graph_boost<	MyGraph
								, boost::vertex_name_t
								, boost::edge_name_t
								, boost::vertex_index_t
							> GB;

	  // create graphs
	std::cout <<"--> create dummy graphs \n" <<std::endl;
	std::string patternString;
	std::string targetString;
						
	GB patternGraph (getPattern_1( patternString ));
	sgm::Pattern pattern( patternGraph );
	GB target (getTarget_1( targetString ));
	
	  // create dummy match:
	std::cout <<"--> create dummy match :\n" <<std::endl;
	sgm::Match match;
	match.push_back(4);
	match.push_back(3);
	match.push_back(2);
	match.push_back(5);
	for (size_t i=0; i<match.size(); i++) {
		std::cout <<" " <<match[i];
	}
	std::cout <<std::endl;
	
	std::cout <<"--> mr.reportHit(..)" <<std::endl;
	mr.reportHit(pattern, target, match);
	std::cout <<"--> mr.reportHit(..)" <<std::endl;
	mr.reportHit(pattern, target, match);

	std::cout <<"--> mr.resetHits(..)" <<std::endl;
	mr.resetHits();
	
	std::cout <<"--> mr.reportHit(..)" <<std::endl;
	mr.reportHit(pattern, target, match);
	

	std::cout	<<"\n"
				<<"===============  TEST END  ===================\n" 
				<<"==============================================\n"
				<<std::endl;
	
	return 0;
}

