#ifndef OE1_SCENE_H_
#define OE1_SCENE_H_


#include "SceneCameraManager/SceneCameraManager.h"

#include "../Mesh/StaticMesh/StaticMesh.h"
#include "../Mesh/DynamicMesh/DynamicMesh.h"
#include "../Mesh/DebugMesh/DebugMesh.h"

#include "../Grid/Grid.h"

#include "../InfiniteVision/IVMasterRenderer.h"
#include "../Ray/Ray.h"
#include "../CoreAnimation/Animator/SkeletonAnimator.h"
#include <Entt/entt.hpp>
#include "SceneRenderMode.h"

#include "../DS/TurboOT/TurboOT.h"
#include "SceneQuickCull/SceneQuickCull.h"

// Action Controller
#include "InputController/InputController.h"
#include "RenderController/RenderController.h"
#include "GenesisController/GenesisController.h"

#include <unordered_map>
#include <functional>

namespace OE1Core 
{
	namespace Renderer { class IVMasterRenderer; class IVRenderStack; }
	class Entity;
	class Scene
	{
		friend Renderer::IVMasterRenderer;
		friend class InputController;
		friend class RenderController;
		friend class GenesisController;
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
		
		// STATIC MESH

		bool  PurgeStaticMesh(uint32_t _package_id);
		StaticMesh* QueryStaticMesh(uint32_t _package_id);
		StaticMesh* RegisterStaticMesh(IVModel* _model_pkg);
		bool HasStaticMesh(uint32_t _package_id);

		// DYNAMIC MESH

		bool  PurgeDynamicMesh(uint32_t _package_id);
		DynamicMesh* QueryDynamicMesh(uint32_t _package_id);
		DynamicMesh* RegisterDynamicMesh(IVModel* _model_pkg);
		bool HasDynamicMesh(uint32_t _package_id);


		// DEBUG MESH

		bool  PurgeDebugMesh(uint32_t _package_id);
		DebugMesh* QueryDebugMesh(uint32_t _package_id);
		DebugMesh* RegisterDebugMesh(IVModel* _model_pkg);
		bool HasDebugMesh(uint32_t _package_id);



		class ActiveEntity* GetActiveEntity(); 
		void Update(int _width, int _height);
		void ResetPhysics();
		void OnEvent(OECore::IEvent& e);
		Ray* GetRay();
		/// <summary>
		/// This include the physics
		/// </summary>
		void ResetScene();

		void UpdateAnimationComponents();
		void UpdateAnimationTransform();

		void SwitchContext(BaseWindow* _window);


		// Scene Renderer stuff
		SceneCameraManager* GetCameraManager() const;
		Renderer::IVMasterRenderer* GetRenderer();
		DS::TurboOT* GetTurboOT();

		void OnSelectionFlushOperation(std::vector<Entity>& _entitys);

		Entity* GetActivePlayerEntity();
		void SetActivePlayerEntity(Entity _entity);
		
		/// <summary>
		/// This function can be used in d/t senario for now we gone use it to add items into the 
		/// OT data structure or the local cull buffer list based on the scene configuration
		/// </summary>
		/// <param name="_entity"></param>
		void RegisterLoadedEntity(Entity _entity);
		void PurgeLoadedEntity(Entity _entity);

		bool IsParsableIntoOTEntDiscriptor(Entity _entity);
		/// <summary>
		/// make sure the entity is parsable before trying this or you it will return invalid data
		/// </summary>
		/// <param name="_entity"></param>
		/// <returns></returns>
		DS::OTEntDiscriptor ParseIntoOTEntDiscriptor(Entity _entity);

		void InputUpdate(float _dt);
		void BufferUpdate(float _dt);
		void InitRender();

		void InputUpdate_Genesis(float _dt);
		void BufferUpdate_Genesis(float _dt);
		void OnEvent_Genesis(OECore::IEvent& e);
		void InitRender_Genesis();
		void UpdateFrameRes_Genesis(int _width, int _height);


	public:
		class Renderer::IVRenderStack* m_RenderStack = nullptr;
		Grid* m_Grid = nullptr;
		SDL_Window* m_Window;
		bool m_UtilizeSpecialDataStructureForFrusumCull = false;

		SceneCameraManager* m_CameraManager = nullptr;
		MasterSceneEditorCamera* m_MasterSceneCamera = nullptr;

		entt::registry m_EntityRegistry;

		std::unordered_map<uint32_t, DebugMesh*> m_DebugMeshRegistry;
		std::unordered_map<uint32_t, DynamicMesh*> m_DynamicMeshRegistry;
		std::unordered_map<uint32_t, StaticMesh*> m_StaticMeshRegistry;
		std::unordered_map<ViewportIconBillboardType, ViewportBillboardIcon*> m_SceneBillboardIcon;

	protected:
		Component::ActorComponent* m_Protagonist = nullptr;
		GenesisController* m_GenesisController = nullptr;
		RenderController* m_RenderController = nullptr;
		InputController* m_InputController = nullptr;
		SceneQuickCull* m_QuickCull = nullptr;
		DS::TurboOT* m_TurboOctree = nullptr;
		Renderer::IVMasterRenderer* m_MyRenderer;
		class ActiveEntity* m_SceneActiveSelection;
		RenderMode m_RenderMode;
		Ray* m_SceneRay = nullptr;
		float m_LastDelta = 0.0f;
		Entity* m_ActivePlayerEntity = nullptr;



	private:
		void HotComponentUpdate();
		void UpdateCulledBuffer();
		void UpdateCulledBuffer(Component::CameraComponent* _camera);
		void UpdateInistanceGLBuffer(std::unordered_map<uint32_t, std::vector<DS::OTEntDiscriptor>>& _buffer);
	};
}



#endif // !OE1_SCENE_H_
