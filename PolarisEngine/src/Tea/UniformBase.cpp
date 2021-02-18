#include "UniformBase.h"

namespace TEA {
	UniformBase::UniformBase(std::string uniformName) : uniformName(uniformName)
	{
	}

	std::string UniformBase::GetUniformName()
	{
		return uniformName;
	}
}