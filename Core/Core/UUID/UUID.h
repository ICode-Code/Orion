#ifndef OE1_UUID_H_
#define OE1_UUID_H_


#include <xhash>
#include <random>


namespace OE1Core
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t _id);
		UUID(const UUID&) = default;
		operator uint64_t() const { return m_UniversallyUniqueIdentifier; }

	private:
		uint64_t m_UniversallyUniqueIdentifier;
	};
}

namespace std
{
	template<> struct hash<OE1Core::UUID>
	{
		std::size_t operator()(const OE1Core::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}


#endif // !OE1_UUID_H_
