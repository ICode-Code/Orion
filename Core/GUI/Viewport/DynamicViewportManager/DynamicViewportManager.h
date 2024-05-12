#ifndef OE1_DYNAMIC_VIEWPORT_MANAGER_H_
#define OE1_DYNAMIC_VIEWPORT_MANAGER_H_

#include "../DynamicViewport/DynamicViewport.h"

#include <unordered_map>
#include <functional>

namespace OE1Core
{
	class DynamicViewportManager
	{
		friend class GUIBase;
	public:
		DynamicViewportManager();
		~DynamicViewportManager();

		static DynamicViewport* RegisterDynamicViewport(std::string _name, Component::CameraComponent* _camera);
		static DynamicViewport* GetViewport(std::string _name);
		static bool PurgeDynamicViewport(std::string _name);
		static bool HasViewport(std::string _name);


	protected:
		inline static std::unordered_map<std::string, DynamicViewport*> m_DynamicViewport;

	};
}


#endif // !OE1_DYNAMIC_VIEWPORT_MANAGER_H_
