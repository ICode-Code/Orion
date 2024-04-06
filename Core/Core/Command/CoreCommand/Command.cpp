#include "Commnad.h"



namespace OE1Core
{

	void Command::RegisterContentBrowserLayerNotifyCallback(const ContentBrowserLayerNotifyCallback& _callback)
	{
		s_ContentBrowserLayerNotifyCallback = _callback;
	}
	void Command::RegisterThreadInfoLayerNotifyCallback(const ThreadInfoLayerNotifyCallback& _callback)
	{
		s_ThreadInfoLayerNotifyCallback = _callback;
	}

	void Command::PushAssetLoadCommand(Loader::LoadArgs _args)
	{
		s_Load3DAssetCommands.push(_args);
	}

	void Command::PushEntitySelectionCommand(CommandDef::EntitySelectionCommandDef _command) 
	{
		s_EntitySelectionCommands.push(_command);
	}
	void Command::PushMaterialTextureUpdateCommand(CommandDef::MaterialtextureUpdateCommandDef _command) 
	{
		s_MaterialTextureUpdateCommands.push(_command);
	}
	void Command::PushMasterRendererMaterialRefresh(CommandDef::MasterRendererMaterialRefreshCommandDef _command)
	{
		s_MasterRendererMaterialRefreshCommands.push(_command);
	}
	void Command::PushMaterialTextureExtractionCommand(CommandDef::MaterialTextureExtractionDef _command)
	{
		s_MaterialTextureExtractionCommands.push(_command);
	}
	void Command::PushTextureLoadCommand(CommandDef::TextureLoadCommandDef _command)
	{
		s_TextureLoadCommands.push(_command);
	}
	void Command::PushTextureLoadCommand(DataBlock::Image2D _data)
	{
		s_TextureLoadRawDataCommands.push(_data);
	}
	void Command::PushDynamicViewportPurgeCommand(CommandDef::PurgeDynamicViewportCommandDef _command)
	{
		s_DyanmicViewportPurgeCommands.push(_command);
	}
	void Command::PushMaterialSnapshotCommand(CommandDef::MaterialSnapShotCommandDefs _command)
	{
		s_MaterialSnapshotCommands.push(_command);
	}
	void Command::PushMaterialCreationCommand(CommandDef::MaterialCreationCommandDef _command)
	{
		s_MaterialCreationCommands.push(_command);
	}
	void Command::PushModelPreviewRenderCommand(CommandDef::ModelPreviewRenderCommandDef _command)
	{
		s_ModelPreviewRenderCommands.push(_command);
	}
	void Command::PushDynamicMeshModelPreviewRenderCommand(CommandDef::DynamicMeshModelPreviewRenderCommandDef _command)
	{
		s_DynamicMeshModelPreviewRenderCommands.push(_command);
	}
	void Command::PushAnimationLoadCommand(CommandDef::AnimationLoadCommandDef _command)
	{
		s_AnimationLoadCommands.push(_command);
	}
	void Command::PushAnimationSwitchCommand(CommandDef::AnimationSwitchCommandDef _command)
	{
		s_AnimationSwitchCommands.push(_command);
	}
	void Command::PushSceneDebugShapeCreateCommand(CommandDef::SceneDebugShapeCreateCommandDef _command)
	{
		s_SceneDebugShapeCreateCommands.push(_command);
	}
	void Command::PushSceneDebugShapeUpdateCommand(CommandDef::SceneDebugShapeUpdateCommandDef _command)
	{
		s_SceneDebugShapeUpdateCommands.push(_command);
	}
}