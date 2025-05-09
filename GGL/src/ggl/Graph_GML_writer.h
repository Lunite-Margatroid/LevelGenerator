
#include "sgm/HashMap.hh"

#if HAVE_UNORDERED_MAP > 0
	#include <unordered_map>
#elif HAVE_TR1_UNORDERED_MAP > 0
	#include <tr1/unordered_map>
#elif HAVE_GNU_HASH_MAP > 0
	#include <ext/hash_map>
#else
	#include <map>
#endif

namespace ggl
{

////////////////////////////////////////////////////////////////////////////////


inline
Graph_GML_writer
::Graph_GML_writer()
{
}

////////////////////////////////////////////////////////////////////////////////


inline
Graph_GML_writer
::~Graph_GML_writer()
{
}

////////////////////////////////////////////////////////////////////////////////


} // namespace ggl
