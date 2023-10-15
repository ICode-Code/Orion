#ifndef OE1_NAME_HANDLE_H_
#define OE1_NAME_HANDLE_H_

#include <string>

namespace OE1Core
{
	namespace Loader
	{
		class NameHandle
		{
		public:
			NameHandle();
			~NameHandle();


			static std::string FilterFileName(std::string _path);
			static std::string FilterFileNameExt(std::string _path);
			static std::string FilterPath(std::string _path);

		protected:
			static bool PrimaryPathFilter(std::string _path);
			inline static char s_CheckChar;
		};
	}
}

#endif // !OE1_NAME_HANDLE_H_
