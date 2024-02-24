#ifndef OE1_LOADER_H_
#define OE1_LOADER_H_



#include "../Geometry/CoreGeometryLoader.h"
#include "IVLoadedAsset.h"

namespace OE1Core
{
	namespace Loader
	{
		class IVLoader
		{
		public:
			IVLoader() = delete;
			~IVLoader() = delete;

			static void Import(LoadArgs _load_args);
		};
	}
}

#endif // !OE1_LOADER_H_
