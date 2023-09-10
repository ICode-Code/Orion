#ifndef OE1_LOAD_ARGS_H_
#define OE1_LOAD_ARGS_H_

#include <string>

namespace OE1Core
{
	class Asset3DLoaderWin;
	namespace Loader
	{
		struct LoadArgs
		{
			friend class Asset3DLoaderWin;
			bool HasAnimation = false;
			// load all texture in a way that makes sense
			bool CreateMaterial = true;
			bool GenerateDynamicLOD = false;

			std::string DestinationPath = "";
			std::string SourcePath = "";

		private:
			void Reset()
			{
				HasAnimation = false;
				CreateMaterial = true;
				GenerateDynamicLOD = false;
				DestinationPath = "";
				SourcePath = "";
			}
			
		};
	}
}


#endif // !OE1_LOAD_ARGS_H_
