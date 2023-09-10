#include "GeometryLoader.h"


namespace OE1Core
{
	namespace Loader
	{
		using namespace std::chrono_literals;
		void GeometryLoader::LoadGeometry(LoadArgs _load_args, bool& _is_running)
		{
			// Flag used to tell this thred is running
			_is_running = true;

			// _is_running: is specific to this function so if we need some global info
			s_Working = _is_running;

			// Create Local data
			StaticGeometryLoader::MeshSet mesh_set;

			// heavy process
			StaticGeometryLoader::OELoadStaticGeometry(_load_args.SourcePath, mesh_set);

			// to the list
			s_MeshSets.push(std::make_pair(_load_args, mesh_set));

			// update info
			StaticGeometryLoader::PROGRESS_INFO = "Establishing Orion asset..";

			// For proper sync 
			std::this_thread::sleep_for(1s);


			// update flags
			_is_running = false;
		}
	}
}