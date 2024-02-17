#ifndef OE1_UTIL_FUNC_H_
#define OE1_UTIL_FUNC_H_

#include <string>
#include <functional>

namespace OE1Core
{
	namespace Util
	{
		class UtilFunc
		{
		public:
			UtilFunc() {};
			~UtilFunc() {};

			static std::string CheckNameCollision(std::string _name, std::function<bool(std::string)> _cmp);
		
		};
	}
}

#endif // !OE1_UTIL_FUNC_H_
