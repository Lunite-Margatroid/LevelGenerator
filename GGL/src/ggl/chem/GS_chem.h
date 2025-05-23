
#include <vector>
#include <cassert>


namespace ggl {
 namespace chem {


////////////////////////////////////////////////////////////////////////////////
////////////////////  GS_chem::node_is_in_component  /////////////////////////
////////////////////////////////////////////////////////////////////////////////



	inline
	GS_chem
	::node_is_in_component
	::node_is_in_component()
	 :	componentID(-1)
	 	, componentVec(NULL)
	 	, idxMap(NULL)
	{

	}

////////////////////////////////////////////////////////////////////////////////


	inline
	GS_chem
	::node_is_in_component
	::node_is_in_component(	const int componentID_
							, const ComponentIdVec& componentVec_
							, const IndexMap* idxMap_)
	 :	componentID(componentID_)
	 	, componentVec(&componentVec_)
	 	, idxMap(idxMap_)
	{
//		std::cout <<" # NODE_CHECK : INIT ( "<<componentID <<", " <<componentVec->size() <<", " <<idxMap <<" )" <<std::endl;
//		for (size_t i=0; i<componentVec->size(); i++) {
//			std::cout <<" # NODE_CHECK : INIT : get(*idxMap,"<<i<<") = "; std::cout.flush();
//			std::cout <<boost::get(*idxMap,(Molecule::vertex_descriptor)i) <<std::endl;
//		}

	}

////////////////////////////////////////////////////////////////////////////////


	template <	typename VERTEX >
	inline
	bool
	GS_chem
	::node_is_in_component
	::operator()( const VERTEX& node ) const
	{
		assert(componentVec != NULL && componentVec->size() > 0);
		assert(idxMap != NULL);
//std::cout <<" # NODE_CHECK ( "<<componentID <<", " <<componentVec->size() <<", " <<idxMap <<" )" <<std::endl;
//std::cout <<" # NODE_CHECK : node = " <<node <<std::endl;
//std::cout <<" # NODE_CHECK : idx  = "; std::cout.flush();
//	std::cout <<boost::get(*idxMap,(Molecule::vertex_descriptor)node); std::cout.flush();
//	std::cout <<" of " <<componentVec->size() <<std::endl;
//std::cout <<" # NODE_CHECK : comp = "<<(componentVec->at((size_t)boost::get(*idxMap,node)) == componentID?"true":"false") <<std::endl;

		return componentVec->at((size_t)boost::get(*idxMap,node)) == componentID;
	}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////  GS_chem::edge_is_in_component  /////////////////////////
////////////////////////////////////////////////////////////////////////////////



	inline
	GS_chem
	::edge_is_in_component
	::edge_is_in_component()
	 :	componentID(-1)
		, componentVec(NULL)
		, idxMap(NULL)
		, m(NULL)
	{
	}

////////////////////////////////////////////////////////////////////////////////


	inline
	GS_chem
	::edge_is_in_component
	::edge_is_in_component(	const int componentID_
							, const ComponentIdVec& componentVec_
							, const IndexMap* idxMap_
							, const Molecule& m_)
		 :	componentID(componentID_)
		 	, componentVec(&componentVec_)
		 	, idxMap(idxMap_)
		 	, m(&m_)
	{
//		std::cout <<"## EDGE_CHECK : INIT ( "<<componentID <<", " <<componentVec->size() <<", " <<idxMap <<" )" <<std::endl;
	}

////////////////////////////////////////////////////////////////////////////////


	template <typename EDGE>
	inline
	bool
	GS_chem
	::edge_is_in_component
	::operator()(const EDGE& e) const {
		assert(componentVec != NULL && componentVec->size() > 0);
		assert(idxMap != NULL);
//std::cout <<"## EDGE_CHECK ( "<<componentID <<", " <<componentVec->size() <<", " <<idxMap <<" )" <<std::endl;
		Molecule::vertex_descriptor from = boost::source(e, *m);
//std::cout <<"## EDGE_CHECK : source = " <<from <<std::endl;
		if (componentVec->at((size_t)boost::get(*idxMap,from)) != componentID)
			return false;
		Molecule::vertex_descriptor to = boost::target(e, *m);
//std::cout <<"## EDGE_CHECK : target = " <<to <<std::endl;
		if (componentVec->at((size_t)boost::get(*idxMap,to)) != componentID)
			return false;
		return true;
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

 } // namespace chem
} //  namespace ggl
