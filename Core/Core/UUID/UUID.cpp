#include "UUID.h"

namespace OE1Core
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID()
		: m_UniversallyUniqueIdentifier(s_UniformDistribution(s_engine))
	{
	}
	UUID::UUID(uint64_t _id)
		: m_UniversallyUniqueIdentifier(_id)
	{
	}
}