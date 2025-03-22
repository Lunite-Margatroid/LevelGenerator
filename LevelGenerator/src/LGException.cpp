#include "LGException.h"

namespace LG
{

	LGException::LGException()
		:m_exceptInfo("LG Exception")
	{
	}

	LGException::LGException(const std::string& info)
		:m_exceptInfo(info)
	{
	}

	// exception
	const char* LGException::what() const noexcept
	{
		return m_exceptInfo.c_str();
	}
}