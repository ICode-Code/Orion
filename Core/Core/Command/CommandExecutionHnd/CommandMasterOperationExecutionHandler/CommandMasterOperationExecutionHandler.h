#ifndef OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_
#define OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_

#include "../ExeHandleBase/ExeHandleBase.h"
#include "../AssetManager/AssetParser/AssetParser.h"
#include "Geometry/GeometryLoader.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		class CommandMasterOperationExecutionHandle : public ExecutionHandleBase
		{
		public:
			CommandMasterOperationExecutionHandle(Scene* _scene);
			~CommandMasterOperationExecutionHandle();

			static void ProcessQueue();


		private:
			static void ProcessAssetLoadCommands();
			static void ProcessMaterialCreationCommands();

			static void ProcessPurgeDynamicViewportCommand();

		private: // Util
			static bool AssignMaterial(ModelPkg* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id);
		};
	}
}

#endif // !OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_
