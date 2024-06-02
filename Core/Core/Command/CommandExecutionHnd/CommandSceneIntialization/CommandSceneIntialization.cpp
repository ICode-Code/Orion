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
		}
		void CommandSceneInitalization::ProcessIBLLoad()
		{
			while (!Command::s_CreateSceneLightRoomCommands.empty())
			{
				auto& commandX = Command::s_CreateSceneLightRoomCommands.front();

				if (!m_Scene->m_LightRoomManager)
					m_Scene->SetLightRoomManager(new Renderer::IVLightRoomManager());


				m_Scene->m_LightRoomManager->RegisterEnvironmentMap(commandX.Path, commandX.Name);
				LOG_INFO("'{0}' Light Map Loaded", commandX.Name);
				

				m_Scene->SetLightRoom(
					m_Scene->m_LightRoomManager->GetDiffuseIrradiance()->GetIrradianceMap(commandX.Name),
					m_Scene->m_LightRoomManager->GetSpeculars()->GetPrefilteredReflectionMap(commandX.Name),
					m_Scene->m_LightRoomManager->GetSpeculars()->GetLUT());

				Command::s_CreateSceneLightRoomCommands.pop();
			}
		}
	}
}