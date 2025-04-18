#ifndef SGM_HASHMAP_HH_
#define SGM_HASHMAP_HH_

////////////////////////////////////////////////////////////////////////////////
// STANDARD UNORDERED MAP FLAG
// 1 - if the header <unordered_map> is available 
//     (e.g. for using std::unordered_map<int,int>)
// 0 - otherwise 
////////////////////////////////////////////////////////////////////////////////

#define HAVE_UNORDERED_MAP 1



////////////////////////////////////////////////////////////////////////////////
// STANDARD TEST RELEASE 1 UNORDERED MAP FLAG
// 1 - if the header <tr1/unordered_map> is available 
//     (e.g. for using std::tr1::unordered_map<int,int>)
// 0 - otherwise 
////////////////////////////////////////////////////////////////////////////////

#define HAVE_TR1_UNORDERED_MAP 0



////////////////////////////////////////////////////////////////////////////////
// GNU HASH MAP FLAG
// 1 - if the header <ext/hash_map> is available 
//     (e.g. for using __gnu_cxx::hash_map<int,int>)
// 0 - otherwise 
////////////////////////////////////////////////////////////////////////////////

#define HAVE_GNU_HASH_MAP 0



#if HAVE_GNU_HASH_MAP > 0

#include <string>
namespace sgm {

	/*! Daniel J. Bernstein's string hash function 
	 *  taken from http://www.cs.yorku.ca/~oz/hash.html.
	 */
	class hash_string {
	public:
	
		size_t operator()(const std::string& str) const
		{
			size_t hash = 5381;
	
			for (size_t i = 0; i < str.size(); i++) {
				// hash * 33 + str[i]
				hash = ((hash << 5) + hash) + (size_t)str[i]; 
			}
	
			return hash;
		}
		     
	};

} // namespace sgm

#endif

////////////////////////////////////////////////////////////////////////////////




#endif /*SGM_HASHMAP_HH_*/
