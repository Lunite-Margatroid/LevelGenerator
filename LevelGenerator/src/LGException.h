#pragma once
#include "LG_Common.h"

#define LG_ASSERT_INFO(bAssert, info) do{ if(!(bAssert)) throw LG::LGException(#info);}while(false)
#define LG_ASSERT(bAssert) do{if(!(bAssert)) throw LG::LGException();}while(false)

namespace LG
{
	// exception
	class LG_DLL_API LGException : std::exception
	{
		std::string m_exceptInfo;
	public:
		LGException();
		LGException(const std::string& info);
		const char* what() const noexcept override;
	};
}