
namespace ggl {
namespace chem {

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////



	inline
	GS_MolCheck::
	GS_MolCheck( GS_chem & gs
				, const AromaticityPerception & aromaticityPerception
				, const bool ignoreExceptions )
	 : nextGS(&gs), aromaticityPerception(aromaticityPerception.clone())
		, ignoreExceptions(ignoreExceptions)
	{}

////////////////////////////////////////////////////////////////////////////


	inline
	GS_MolCheck::
	GS_MolCheck( const GS_MolCheck & toCopy)
	 : nextGS( toCopy.nextGS )
		, aromaticityPerception(toCopy.aromaticityPerception->clone())
		, ignoreExceptions(toCopy.ignoreExceptions)
	{
	}

////////////////////////////////////////////////////////////////////////////


	inline
	GS_MolCheck::
	~GS_MolCheck()
	{
		  // garbage collection
		delete aromaticityPerception;
	}

////////////////////////////////////////////////////////////////////////////

}} //namespace
