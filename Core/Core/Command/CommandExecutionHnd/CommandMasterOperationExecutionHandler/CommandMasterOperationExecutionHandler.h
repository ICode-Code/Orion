#ifndef OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_
#define OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_

#include "../ExeHandleBase/ExeHandleBase.h"
#include "../AssetManager/AssetParser/AssetParser.h"
#include "Loader/IVLoader.h"

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
			static void ProcessMaterialCreationCommand();

			static void ProcessPurgeDynamicViewportCommand();

		private: // Util
			static bool AssignMaterial(IVModel* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id);
			static Renderer::CheckMatPreviewTexture FilterMaterialTexture(MasterMaterial* _material);
		};
	}
}

#endif // !OE1_COMMAND_MASTER_OPERATION_EXECUTION_HANDLER_H_
