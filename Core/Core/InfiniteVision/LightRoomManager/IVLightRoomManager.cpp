#include "IVLightRoomManager.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVLightRoomManager::IVLightRoomManager()
		{
			m_DiffuseIrradiance = new IVDiffuseIrradiance();
			m_Specualr = new IVSpecular();
		}
		IVLightRoomManager::~IVLightRoomManager()
		{
			delete m_DiffuseIrradiance;
			delete m_Specualr;
		}

		void IVLightRoomManager::RegisterEnvironmentMap(std::string _path, std::string _name)
		{
			m_DiffuseIrradiance->RegisterHDRI(_path, _name);
			m_Specualr->RegisterEnviromnetMap(m_DiffuseIrradiance->GetCubeMap(_name), _name);
		}
		IVDiffuseIrradiance* IVLightRoomManager::GetDiffuseIrradiance() { return m_DiffuseIrradiance; }
		IVSpecular* IVLightRoomManager::GetSpeculars() { return m_Specualr; }

	}
}