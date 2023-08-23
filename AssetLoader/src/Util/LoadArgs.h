#ifndef OE1_LOAD_ARGS_H_
#define OE1_LOAD_ARGS_H_

#include <string>

namespace OE1Core
{
	namespace Loader
	{
		struct LoadArgs
		{
			bool HasAnimation = false;
			// load all texture in a way that makes sense
			bool CreateMaterial = true;
			bool GenerateDynamicLOD = false;

			std::string DestinationPath = "";
			std::string SourcePath = "";
			
		};
	}
}


#endif // !OE1_LOAD_ARGS_H_
