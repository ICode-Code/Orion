#ifndef OE1_COMMAND_H_
#define OE1_COMMAND_H_

#include <string>
#include <queue>
#include "Util/LoadArgs.h"
#include "CommandDefinitions.h"
#include "Util/DataBlock.h"
#include <functional>
#include <chrono>

using namespace std::chrono_literals;
namespace OE1Core
{
	namespace CommandHnd
	{
		class CommandContextHighFreqOperationHandle;
		class CommandContextOperationExeHandler;
		class CommandIgnitionExecutionHandle;
		class CommandMasterOperationExecutionHandle;
		class CommandSceneInitalization;
		class ExeHandleManager;
	}

	typedef std::function<void()> ContentBrowserLayerNotifyCallback;
	typedef std::function<void(bool)> ThreadInfoLayerNotifyCallback;

	/// <summary>
	///This command are invocked from the ui and need to queue them and execute them
	// after the UI call
	/// </summary>
	class Command
	{
		friend class ExecutionHandler;
		friend class CommandHnd::CommandContextHighFreqOperationHandle;
		friend class CommandHnd::CommandContextOperationExeHandler;
		friend class CommandHnd::CommandIgnitionExecutionHandle;
		friend class CommandHnd::CommandMasterOperationExecutionHandle;
		friend class CommandHnd::ExeHandleManager;
		friend class CommandHnd::CommandSceneInitalization;
	public:
		static void RegisterContentBrowserLayerNotifyCallback(const ContentBrowserLayerNotifyCallback& _callback);
		static void RegisterThreadInfoLayerNotifyCallback(const ThreadInfoLayerNotifyCallback& _callback);

	public:
		static void PushModelPreviewRenderCommand(CommandDef::ModelPreviewRenderCommandDef _command);
		static void PushDynamicMeshModelPreviewRenderCommand(CommandDef::DynamicMeshModelPreviewRenderCommandDef _command);
		static void PushMaterialCreationCommand(CommandDef::MaterialCreationCommandDef _command);
		static void PushMaterialSnapshotCommand(CommandDef::MaterialSnapShotCommandDefs _command);
		static void PushDynamicViewportPurgeCommand(CommandDef::PurgeDynamicViewportCommandDef _command);
		static void PushTextureLoadCommand(CommandDef::TextureLoadCommandDef _command);
		static void PushTextureLoadCommand(DataBlock::Image2D _data);
		static void PushAssetLoadCommand(Loader::LoadArgs _args);	
		static void PushEntitySelectionCommand(CommandDef::EntitySelectionCommandDef _command);
		static void PushMaterialTextureUpdateCommand(CommandDef::MaterialtextureUpdateCommandDef _command);
		static void PushMasterRendererMaterialRefresh(CommandDef::MasterRendererMaterialRefreshCommandDef _command);
		static void PushAnimationLoadCommand(CommandDef::AnimationLoadCommandDef _command);
		static void PushAnimationSwitchCommand(CommandDef::AnimationSwitchCommandDef _command);
		static void PushSceneDebugShapeCreateCommand(CommandDef::SceneDebugShapeCreateCommandDef _command);
		static void PushSceneDebugShapeUpdateCommand(CommandDef::SceneDebugShapeUpdateCommandDef _command);
		static void PushSceneInitiCommand(CommandDef::CreateSceneLightRoomCommandDef _command);
		static void PushShaderRecompileCommand(CommandDef::ShaderRecompileCommandDef _command);
		/// <summary>
		/// This Command processed at the end
		/// </summary>
		/// <param name="_command"></param>
		static void PushMaterialTextureExtractionCommand(CommandDef::MaterialTextureExtractionDef _command);
	private:
		inline static std::queue<CommandDef::MaterialCreationCommandDef> s_MaterialCreationCommands;
		inline static std::queue<Loader::LoadArgs> s_Load3DAssetCommands;
		inline static std::queue<CommandDef::EntitySelectionCommandDef> s_EntitySelectionCommands;
		inline static std::queue<CommandDef::MaterialTextureExtractionDef> s_MaterialTextureExtractionCommands;
		inline static std::queue<CommandDef::TextureLoadCommandDef> s_TextureLoadCommands;
		inline static std::queue<DataBlock::Image2D> s_TextureLoadRawDataCommands;
		inline static std::queue<CommandDef::MaterialtextureUpdateCommandDef> s_MaterialTextureUpdateCommands;
		inline static std::queue<CommandDef::MasterRendererMaterialRefreshCommandDef> s_MasterRendererMaterialRefreshCommands;
		inline static std::queue<CommandDef::PurgeDynamicViewportCommandDef> s_DyanmicViewportPurgeCommands;
		inline static std::queue<CommandDef::MaterialSnapShotCommandDefs> s_MaterialSnapshotCommands;
		inline static std::queue<CommandDef::ModelPreviewRenderCommandDef> s_ModelPreviewRenderCommands;
		inline static std::queue<CommandDef::DynamicMeshModelPreviewRenderCommandDef> s_DynamicMeshModelPreviewRenderCommands;
		inline static std::queue<CommandDef::AnimationLoadCommandDef> s_AnimationLoadCommands;
		inline static std::queue<CommandDef::AnimationSwitchCommandDef> s_AnimationSwitchCommands;
		inline static std::queue<CommandDef::SceneDebugShapeCreateCommandDef> s_SceneDebugShapeCreateCommands;
		inline static std::queue<CommandDef::SceneDebugShapeUpdateCommandDef> s_SceneDebugShapeUpdateCommands;
		inline static std::queue<CommandDef::CreateSceneLightRoomCommandDef> s_CreateSceneLightRoomCommands;
		inline static std::queue<CommandDef::ShaderRecompileCommandDef> s_ShaderRecompileCommands;
	private: // callbacks
		inline static ContentBrowserLayerNotifyCallback s_ContentBrowserLayerNotifyCallback;
		inline static ThreadInfoLayerNotifyCallback s_ThreadInfoLayerNotifyCallback;

		// Util
		template<typename T> static void LockCommand(std::queue<T>& _commands)
		{
			std::queue<T> _temp;
			while (!_commands.empty())
			{
				T mod_command = _commands.front();
				mod_command.Lock = true;
				_temp.push(mod_command);
				_commands.pop();
			}

			// re-populate
			while (!_temp.empty())
			{
				_commands.push(_temp.front());
				_temp.pop();
			}
		}
	};
}


#endif // !OE1_COMMAND_H_
