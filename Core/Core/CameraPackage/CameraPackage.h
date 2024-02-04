#ifndef OE1_CAMERA_PACKAGE_H_
#define OE1_CAMERA_PACKAGE_H_

#include "../Component/CameraControllerComponent/FreeLookCameraControllerComponent/FreeLookCameraControllerComponent.h"
#include "../../Common/Shared/UniformBlocks.h"
#include "../InfiniteVision/DisplayCanavs/IVForwardMainPassFramebuffer.h"
#include "CameraState.h"

namespace OE1Core
{
	class CameraPackage
	{
		friend class ActionButtonUtilityGroup;
	public:
		CameraPackage(SDL_Window* _window);
		~CameraPackage();

		Component::CameraComponent* GetCamera();
		Component::FreeLookCameraControllerComponent* GetController();
		void Update(int _width, int _height);
		void Update(float _dt);
		void OnEvent(OECore::IEvent& e);
		Memory::SceneTransfrom& GetSceneTransform();

		Renderer::IVForwardMainPassFramebuffer* GetMainPassFramebuffer();
		GLuint GetRenderedScene();
		void PowerOn();
		void PowerOff();
		bool IsPowerOn();
		CameraState::Power GetPowerState();


		/// <summary>
		/// Return true if it is a valid offset and applyed correctly
		/// </summary>
		/// <param name="_offset"></param>
		/// <returns></returns>
		bool UpdateBufferOffset(GLintptr _offset);

		void AttachFramebuffer(bool _clean_buffer = true, GLenum _usnage = GL_FRAMEBUFFER);
		void DetachFramebuffer();

	protected:
		Memory::SceneTransfrom m_SceneTransform;
		Component::CameraComponent* m_Camera = nullptr;
		Component::FreeLookCameraControllerComponent* m_Controller;

		CameraState::Power m_PowerState = CameraState::Power::OFF;
		GLintptr m_BufferOffset = -1;
		uint32_t m_CameraID = 0;

	private:
		Renderer::IVForwardMainPassFramebuffer* m_MainPassFramebuffer = nullptr;
	};

	struct CameraParameters
	{
		int32_t Offset = -1;
		int32_t ID = -1;
		CameraPackage* Camera = nullptr;
	};
}

#endif // !OE1_CAMERA_PACKAGE_H_
