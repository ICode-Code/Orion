#ifndef OE1_COMMAND_CONTEXT_OPERATION_EXECUTION_HANDLER_H_
#define OE1_COMMAND_CONTEXT_OPERATION_EXECUTION_HANDLER_H_

#include "../ExeHandleBase/ExeHandleBase.h"
#include "../AssetManager/AssetParser/AssetParser.h"
#include "Loader/IVLoadedAsset.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		/// <summary>
		/// Any command that need explicit main thread 
		/// attention will queued here and processed when the time comes
		/// </summary>
		class CommandContextOperationExeHandler : public ExecutionHandleBase
		{
		public:
			CommandContextOperationExeHandler(Scene* _scene);
			~CommandContextOperationExeHandler();


			static void ProcessQueue();


		private:
			// Load Commands
			static void ProcessParseLoadedAssetCommand();
			static void ProcessParseLoadedDynamicMeshCommand();
			static void ProcessTextureLoadCommand();
			static void ProcessRawDataTextureLoadCommand();
		
			// Creation
			static void ProcessMaterialCreationCommand();

			// Update
			static void ProcessMasterMaterialUpdateCommand();
			static void ProcessMaterialReEvaluationCommand();
			static void ProcessMaterialTextureExtractionForPReviewCommand();

			// Fetch Commands
			static void ProcessOnViewportClickReadbackCommand();

			// Preview Render commands
			static void ProcessModelPreviewRenderCommand();
			static void ProcessDynamicMeshPreivewRendererCommand();
			static void ProcessMaterialPreviewRenderCommand();


		private: //Util
			static bool AssignMaterial(IVModel* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id);
			static Renderer::CheckMatPreviewTexture FilterMaterialTexture(MasterMaterial* _material);
		};
	}
}

#endif // !OE1_COMMAND_CONTEXT_OPERATION_EXECUTION_HANDLER_H_
