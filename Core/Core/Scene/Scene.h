#ifndef OE1_SCENE_H_
#define OE1_SCENE_H_


#include "../CameraPackage/CameraPackage.h"
#include "../Mesh/StaticMesh/StaticMesh.h"
#include "../Grid/Grid.h"

#include <Entt/entt.hpp>

#include <unordered_map>
#include <functional>

namespace OE1Core 
{
	namespace Renderer { class IVMasterRenderer; class IVRenderStack; }
	typedef std::function<void(int, int)> IVRendererUpdateCallback;
	class Entity;
	class Scene
	{
		friend Renderer::IVMasterRenderer;
	public:
		Scene(SDL_Window* _window);
		~Scene();

		Entity CreateEntity();
		Entity GetEntity(entt::entity _id);
		Entity GetEntity(uint32_t _id);

		StaticMesh* QueryStaticMesh(uint32_t _package_id);
		StaticMesh* RegisterStaticMesh(ModelPkg* _model_pkg);
		bool HasStaticMesh(uint32_t _package_id);
		void SetRendererCallBack(const IVRendererUpdateCallback& _renderer_update_callbacks) { m_RendererUpdateCallback = _renderer_update_callbacks; }
		void Update(int _width, int _height);
		void Update(float dt);
		void ResetPhysics();
		void OnEvent(OECore::IEvent& e);
		/// <summary>
		/// This include the physics
		/// </summary>
		void ResetScene();


	public:
		class Renderer::IVRenderStack* m_RenderStack = nullptr;
		Grid* m_Grid = nullptr;
		SDL_Window* m_Window;
		CameraPackage m_CameraPkg;
		entt::registry m_EntityRegistry;
		std::unordered_map<uint32_t, StaticMesh*> m_StaticMeshRegistry;

	protected:
		IVRendererUpdateCallback m_RendererUpdateCallback;
		
	};
}



#endif // !OE1_SCENE_H_
