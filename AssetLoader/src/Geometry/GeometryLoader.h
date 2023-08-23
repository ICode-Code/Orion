#ifndef OE1_GEOMETRY_LOADER_H_
#define OE1_GEOMETRY_LOADER_H_

#include "../Util/LoadArgs.h"
#include "StaticGeometryLoader.h"
#include "DynamicGeometryLoader.h"

namespace OE1Core
{
	namespace Loader
	{
		class GeometryLoader
		{
		public:
			// This will pharse the load args
			void LoadGeometry(LoadArgs _load_args);
		};
	}
}

#endif // !OE1_GEOMETRY_LOADER_H_
