#include "UniformBase.h"

namespace Render {
	UniformBase::UniformBase(std::string uniformName) : uniformName(uniformName)
	{
	}

	std::string UniformBase::GetUniformName()
	{
		return uniformName;
	}
}