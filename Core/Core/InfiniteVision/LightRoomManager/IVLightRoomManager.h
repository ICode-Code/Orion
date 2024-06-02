#ifndef OE1_IV_LIGHT_ROOM_MANAGER_H_
#define OE1_IV_LIGHT_ROOM_MANAGER_H_


#include "../IBL/IVDiffuseIrradiance.h"
#include "../IBL/IVSpecular.h"
#include "../Core/Command/CoreCommand/Commnad.h"
#include <filesystem>

namespace OE1Core
{
	namespace Renderer
	{
		class IVLightRoomManager
		{
		public:
			IVLightRoomManager();
			~IVLightRoomManager();


			void RegisterEnvironmentMap(std::string _path, std::string _name);
			IVDiffuseIrradiance* GetDiffuseIrradiance();
			IVSpecular* GetSpeculars();

		private: // Buffers
			IVDiffuseIrradiance* m_DiffuseIrradiance = nullptr;
			IVSpecular* m_Specualr = nullptr;
		};
	}
}

#endif // !OE1_IV_LIGHT_ROOM_MANAGER_H_
