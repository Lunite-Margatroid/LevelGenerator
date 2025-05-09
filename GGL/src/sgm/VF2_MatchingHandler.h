

#include <vf2/match.h>

namespace sgm {

////////////////////////////////////////////////////////////////////////////////


	template < class VF2STATE, class NODECOMPARE, class EDGECOMPARE >
	inline
	size_t
	VF2_MatchingHandler
	::findMatches (	const PatternVec & patterns,
					const Graph_Interface & target,
					ReporterVec & output,
					const size_t maxHits )
	{
		assert( patterns.size() == output.size() /*different number of patterns and output objects*/);
		const size_t targetNodeNumber = target.getNodeNumber();

		  // graph size check
		if ( patterns.size() == 0 || target.getNodeNumber() == 0 ) {
			return 0;
		}

		  // container for all labels in use
		PatternMap labels;

		////////////////////////////////////////////////////////////////////////
		 // create target graph data structure
		////////////////////////////////////////////////////////////////////////
		vf2::ARGEdit targetLoader;
		NodeDataVec targetNodes;
		EdgeLabelVec targetEdges;

		fillLoader( target, targetLoader, labels, targetNodes, targetEdges, true);

		vf2::ARGraph<NodeData, EdgeLabel> targetGraph(&targetLoader);

		size_t numOfMatches = 0;
		size_t remainingHitsToFind = maxHits;

		  // pattern data structures
		NodeDataVec patternNodes;
		EdgeLabelVec patternEdges;

		  // match each pattern
		for (size_t i=0; remainingHitsToFind > 0 && i<patterns.size(); ++i) {

			  // skip incomplete data
			if (patterns.at(i) == NULL || output.at(i) == NULL ) {
				continue;
			}

			  // check if pattern is larger than target -> if so, ignore this pattern
			if (patterns.at(i)->getPatternGraph().getNodeNumber() > targetNodeNumber) {
				continue;
			}

			////////////////////////////////////////////////////////////////////////
			 // create pattern graph data structure
			////////////////////////////////////////////////////////////////////////

			  // store wildcard pointer for fast access
			Label pWildcard = 0;
			if (patterns.at(i)->getUsedWildcard() != NULL ) {
				if(labels.find(*(patterns.at(i)->getUsedWildcard()))==labels.end()) {
					  // create new label pointer
					pWildcard = -1;
					labels.insert(PatternMap::value_type(*(patterns.at(i)->getUsedWildcard()), pWildcard));
				} else {
					  // set to known label pointer
					pWildcard = labels.find(*(patterns.at(i)->getUsedWildcard()))->second;
				}
			}

			  // create VF2 pattern data structures
			vf2::ARGEdit patternLoader;

			fillLoader( patterns.at(i)->getPatternGraph(), patternLoader, labels, patternNodes, patternEdges, true);

			////////////////////////////////////////////////////////////////////////
			 // perform matching
			////////////////////////////////////////////////////////////////////////

			  // check if the pattern node degree distribution is compatible to the target
			if (areDegreeCompatible( patternNodes, targetNodes )) {

				  // setup hander for match report forwarding
				VF2_match_handler matchHandler( *(output.at(i)), *(patterns.at(i)), target, remainingHitsToFind );

				vf2::ARGraph<NodeData, EdgeLabel> patternGraph(&patternLoader);
				patternGraph.SetNodeComparator(new NODECOMPARE(pWildcard, *(patterns.at(i)), target));
				patternGraph.SetEdgeComparator(new EDGECOMPARE(pWildcard));

				  // create search state
				VF2STATE vf2_state(&patternGraph, &targetGraph);
				  // perform matching
				vf2::match(&vf2_state, VF2_match_handler::report_matches, &matchHandler);

				  // store matches for this matching run
				numOfMatches += matchHandler.numOfMatches;
				remainingHitsToFind -= matchHandler.numOfMatches;

			}

		} // for all patterns

		  // clear memory
		for(EdgeLabelVec::iterator it = patternEdges.begin(); it != patternEdges.end(); ++it) {
			delete *it;
		}
		patternEdges.clear();
		for(EdgeLabelVec::iterator it = targetEdges.begin(); it != targetEdges.end(); ++it) {
			delete *it;
		}
		targetEdges.clear();

		return numOfMatches;
	}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}
