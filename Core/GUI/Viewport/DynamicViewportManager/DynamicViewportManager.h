#ifndef OE1_DYNAMIC_VIEWPORT_MANAGER_H_
#define OE1_DYNAMIC_VIEWPORT_MANAGER_H_

#include "../DynamicViewport/DynamicViewport.h"

#include <unordered_map>

namespace OE1Core
{
	class DynamicViewportManager
	{
		friend class GUIBase;
	public:
		DynamicViewportManager();
		~DynamicViewportManager();

		static DynamicViewport* RegisterDynamicViewport(std::string _name, CameraPackage* _camera);
		static DynamicViewport* GetViewport(std::string _name);
		static bool PurgeDynamicViewport(std::string _name);


	protected:
		inline static std::unordered_map<std::string, DynamicViewport*> s_DynamicViewport;

	};
}


#endif // !OE1_DYNAMIC_VIEWPORT_MANAGER_H_
