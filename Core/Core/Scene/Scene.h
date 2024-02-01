#ifndef OE1_SCENE_H_
#define OE1_SCENE_H_


#include "../CameraPackage/CameraPackage.h"
#include "../Mesh/StaticMesh/StaticMesh.h"
#include "../Grid/Grid.h"

#include "../InfiniteVision/IVMasterRenderer.h"
#include "../Ray/Ray.h"

#include <Entt/entt.hpp>
#include "SceneRenderMode.h"

#include <unordered_map>
#include <functional>

namespace OE1Core 
{
	namespace Renderer { class IVMasterRenderer; class IVRenderStack; }
	class Entity;
	class Scene
	{
		friend Renderer::IVMasterRenderer;
	public:
		Scene(SDL_Window* _window);
		~Scene();

		Entity CreateEntity();
		Entity GetEntity(entt::entity _id);
		Entity GetEntity(uint32_t _id, bool _suppress_warning = false);

		/// <summary>
		/// This dude might return nullptrs
		/// </summary>
		/// <param name="_type"></param>
		/// <returns></returns>
		ViewportBillboardIcon* GetBillboardIcon(ViewportIconBillboardType _type);
		bool HasBillboardType(ViewportIconBillboardType _type);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="_type">The Type</param>
		/// <param name="_texture_name">Texture name form Texture AssetManager</param>
		void RegisterBillboardIcon(ViewportIconBillboardType _type, std::string _texture_name);
		/// <summary>
		/// If the instance count is 0 or incase you want to remove all
		/// instance at one which is not recommended at all, like don't do that
		/// Call this Only when the instance count reach 0
		/// </summary>
		/// <param name="_type"></param>
		/// <returns></returns>
		bool PurgeBillboardIcon(ViewportIconBillboardType _type);

		RenderMode& GetRenderMode();
		bool  PurgeStaticMesh(uint32_t _package_id);
		StaticMesh* QueryStaticMesh(uint32_t _package_id);
		StaticMesh* RegisterStaticMesh(ModelPkg* _model_pkg);
		class ActiveEntity* GetActiveEntity(); 
		bool HasStaticMesh(uint32_t _package_id);
		void Update(int _width, int _height);
		void Update(float dt);
		void ResetPhysics();
		void OnEvent(OECore::IEvent& e);
		Ray* GetRay();
		/// <summary>
		/// This include the physics
		/// </summary>
		void ResetScene();


		// Scene Renderer stuff
		void Render();
		Renderer::IVMasterRenderer* GetRenderer();


	public:
		class Renderer::IVRenderStack* m_RenderStack = nullptr;
		Grid* m_Grid = nullptr;
		SDL_Window* m_Window;
		CameraPackage m_CameraPkg;
		entt::registry m_EntityRegistry;
		std::unordered_map<uint32_t, StaticMesh*> m_StaticMeshRegistry;
		std::unordered_map<ViewportIconBillboardType, ViewportBillboardIcon*> m_SceneBillboardIcon;

	protected:
		Renderer::IVMasterRenderer* m_MyRenderer;
		class ActiveEntity* m_SceneActiveSelection;
		RenderMode m_RenderMode;
		Ray* m_SceneRay = nullptr;

	private:
		void HotComponentUpdate();
		
	};
}



#endif // !OE1_SCENE_H_
