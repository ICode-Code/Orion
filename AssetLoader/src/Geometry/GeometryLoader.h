#ifndef OE1_GEOMETRY_LOADER_H_
#define OE1_GEOMETRY_LOADER_H_

#include "../Util/LoadArgs.h"
#include "StaticGeometryLoader.h"
#include "DynamicGeometryLoader.h"

#include <queue>

namespace OE1Core
{
	namespace Loader
	{
		class GeometryLoader
		{
		public:
			~GeometryLoader() = default;
			// This will pharse the load args
			static void LoadGeometry(LoadArgs _load_args, bool& _is_running);
			inline static std::queue<StaticGeometryLoader::MeshSet> s_MeshSets;
			inline static bool s_Working = false;
		};
	}
}

#endif // !OE1_GEOMETRY_LOADER_H_
