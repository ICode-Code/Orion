#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"

namespace OE1Core
{


	void Scene::UpdateGameFrame(int _width, int _height)
	{
		if (!m_ActivePlayerEntity)
			return;

		m_ActivePlayerEntity->GetComponent<Component::ThirdPersonCharacterControllerComponent>().GetCameraComponent()->UpdateRenderFrameSize(_width, _height);
	}
}