#ifndef OE1_GENESIS_CONTROLLER_H_
#define OE1_GENESIS_CONTROLLER_H_

#include <IEvent/IEvent.h>

namespace OE1Core
{
	class GenesisController
	{
	public:
		GenesisController(class Scene* _scene);
		~GenesisController();

		void InputUpdate(float _dt);
		void UpdateBuffer(float _dt);
		void InitRender();
		void OnEvent(OECore::IEvent& e);
		void UpdateFrameRes(int _width, int _height);

	protected:
		class Scene* m_Scene = nullptr;
	};
}

#endif // !OE1_GENESIS_CONTROLLER_H_
