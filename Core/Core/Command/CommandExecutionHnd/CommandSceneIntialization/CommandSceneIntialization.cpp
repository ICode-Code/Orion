#include "CommandSceneIntialization.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		CommandSceneInitalization::CommandSceneInitalization(Scene* _scene)
			: ExecutionHandleBase{ _scene }
		{

		}
		CommandSceneInitalization::~CommandSceneInitalization()
		{

		}

		void CommandSceneInitalization::ProcessQueue()
		{
			ProcessIBLLoad();
			ProcessSkyBoxInitCommand();
		}
		void CommandSceneInitalization::ProcessSkyBoxInitCommand()
		{
			while (!Command::s_SkyBoxInitCommands.empty())
			{
				auto& commandX = Command::s_SkyBoxInitCommands.front();

				
				AssetManager::RegisterTextureCubeMap(commandX.Sources, commandX.Name);
				LOG_INFO("Sky-Dom '{0}' Loaded", commandX.Name);

				Command::s_SkyBoxInitCommands.pop();
			}
		}
		void CommandSceneInitalization::ProcessIBLLoad()
		{
			while (!Command::s_CreateSceneLightRoomCommands.empty())
			{
				auto& commandX = Command::s_CreateSceneLightRoomCommands.front();

				if (!m_Scene->m_LightRoomManager)
					m_Scene->SetLightRoomManager(new Renderer::IVLightRoomManager());


				m_Scene->m_LightRoomManager->RegisterEnvironmentMap(commandX.Path, commandX.Name);
				LOG_INFO("HDRI Light Map '{0}' Loaded", commandX.Name);
				

				m_Scene->SetLightRoom(
					m_Scene->m_LightRoomManager->GetDiffuseIrradiance()->GetIrradianceMap(commandX.Name),
					m_Scene->m_LightRoomManager->GetSpeculars()->GetPrefilteredReflectionMap(commandX.Name),
					m_Scene->m_LightRoomManager->GetSpeculars()->GetLUT());

				Command::s_CreateSceneLightRoomCommands.pop();
			}
		}
	}
}