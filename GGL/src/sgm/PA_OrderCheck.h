

namespace sgm {

	
	inline
	PA_OrderCheck::
	PA_OrderCheck(	const sgm::Pattern_Interface& pattern_
					, const CheckList& checkList_ )
	 :	pattern(&pattern_)
	 	, checkList(checkList_)
	{
	#ifndef NDEBUG
		for (CheckList::const_iterator c=checkList.begin(); c!=checkList.end(); ++c) {
			assert(c->first < pattern->getPatternGraph().getNodeNumber());
			assert(c->second < pattern->getPatternGraph().getNodeNumber());
		}
	#endif
	}
	
	inline
	PA_OrderCheck::
	PA_OrderCheck(	const PA_OrderCheck& toCopy )
	 :	pattern( toCopy.pattern )
	 	, checkList( toCopy.checkList )
	{
	}

	inline
	PA_OrderCheck::
	~PA_OrderCheck()
	{}
	
	 /*
	  * Checks whether or not the given match is symmetric to another match
	  * that is possible based on a list of order checks on the match.
	  * 
	  * @param graph the graph the match belongs to
	  * @param match the match of the graph that has to be checked
	  * @return true if the match is a symmetric one, false otherwise
	  */
	inline
	bool
	PA_OrderCheck::
	isSymmetryMatch(	const Pattern_Interface& graph
						, const Match& match ) const
	{
		assert( graph == *pattern /* the given graph differs from the source graph of this automorphism check */);
		
		for (CheckList::const_iterator c=checkList.begin(); c!=checkList.end(); ++c) {
			if (match.at(c->first) > match.at(c->second)) {
				return true;
			}
		}		
		  // all order checks were ok --> is a non-symmetric Match
		return false;
	}
	
	inline
	PA_OrderCheck *
	PA_OrderCheck::
	clone( void ) const
	{
		return new PA_OrderCheck(*this);
	}

	inline
	const PA_OrderCheck::CheckList&
	PA_OrderCheck::
	getCheckList(void) const 
	{
		return this->checkList;
	}
	
	inline
	const sgm::Pattern_Interface&
	PA_OrderCheck::
	getPattern(void) const
	{
		return *(this->pattern);
	}
	
	inline
	PA_OrderCheck
	PA_OrderCheck::
	getGraphAutomorphism( const sgm::Pattern_Interface& graph )
	{
		  // call template version with default parameters
		return getGraphAutomorphismT< sgm::GM_vf2 >(graph);
	}

	template< class GRAPHMATCHER >
	inline
	PA_OrderCheck
	PA_OrderCheck::
	getGraphAutomorphismT( const sgm::Pattern_Interface& graph )
	{
		  // list of pairs to check that we will fill
		CheckList toCheck;
		
		  // check if the pattern contains constraints for matching
		if ( ! graph.getConstraints().empty() ) {
			  // --> ORDER CHECK IDENTIFICATION IS INCOMPATIBLE TO CONSTRAINTS
			  // --> ABORT CHECK GENERATION
			return PA_OrderCheck( graph, toCheck );
		}

		  // calculate all symmetric matches of the graph on itself
		typedef std::set< Match > Mvec;
		Mvec matches;
		sgm::MR_StoringInsert mr(matches);
		GRAPHMATCHER gm;
		
		gm.findMatches( graph, graph.getPatternGraph(), mr, UINT_MAX );

		  // remove identity Match
		const size_t nodeNum = graph.getPatternGraph().getNodeNumber();
		Match identity( nodeNum, 0 );
		for (size_t i=0; i<identity.size(); ++i)
			identity[i] = i;
		for (Mvec::iterator it=matches.begin(); it!=matches.end(); ++it) {
			if (std::equal(identity.begin(), identity.end(), it->begin())) {
				matches.erase(it);
				break;
			}
		}
		
		  // find order checks to break all symmetric matches
		while ( !matches.empty() ) {
			bool notBroken = true;
			for (size_t i=0; notBroken && i<nodeNum; ++i) {
				for (size_t j=i+1; notBroken && j<nodeNum; ++j) {
					  // check if this order check breaks the leading match
					if (matches.begin()->at(i) > matches.begin()->at(j)) {
						  // add the new order check
						toCheck.push_back( CheckList::value_type(i,j) );
						  // remove all matches that are broken by this order check
						bool oneRemoved = false;
						do {
							oneRemoved = false;
							for (Mvec::iterator it=matches.begin(); it!=matches.end(); ++it) {
								if (it->at(i) > it->at(j)) {
									matches.erase( it );
									oneRemoved = true;
									break;
								}
							}
						} while (oneRemoved);
						notBroken = false;
					}
				}
			}
		}
		  // sort order checks (to make a CheckList unique)
		std::sort<PA_OrderCheck::CheckList::iterator>( toCheck.begin(), toCheck.end() );
		
		  // return new PA_OrderCheck object
		return PA_OrderCheck( graph, toCheck );
	}
	
	


} // namespace sgm


inline
std::ostream&
operator <<( std::ostream& out, const sgm::PA_OrderCheck& ga )
{
	  // print all order checks to stream
	for (sgm::PA_OrderCheck::CheckList::const_iterator it=ga.getCheckList().begin();
			it!=ga.getCheckList().end(); ++it)
	{
		out <<"(" <<it->first <<"<" <<it->second <<")";
	}
	  // return changed stream
	return out;
}

