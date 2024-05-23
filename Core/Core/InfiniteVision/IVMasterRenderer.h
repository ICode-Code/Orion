#ifndef OE1_IV_MASTER_RENDERER_H_
#define OE1_IV_MASTER_RENDERER_H_

#include "DisplayCanavs/FrameSize.h"
#include "DisplayCanavs/IVForwardMainPassFramebuffer.h"

#include "../Scene/SceneCameraManager/SceneCameraManager.h"

#include "Renderers/GridRenderer/IVGridRenderer.h"
#include "Renderers/ModelPreviewRenderer/IVModelPreviewRenderer.h"
#include "Renderers/MeshRenderer/IVMeshRenderer.h"
#include "Renderers/OutlineRenderer/IVOutlineRenderer.h"
#include "Renderers/MaterialPreviewRenderer/IVMaterialPreviewRenderer.h"
#include "Renderers/SceneDebugShapeRenderer/IVSceneDebugShapeRenderer.h"
#include "Renderers/FullScreenQuadRenderer/IVFullScreenQuadRenderer.h"

// Render Stack
#include "RenderStack/RenderStack.h"
#include "../Mesh/StaticMesh/StaticMesh.h"
#include "../Mesh/DynamicMesh/DynamicMesh.h"


namespace OE1Core
{
	namespace Renderer
	{
		class IVMasterRenderer 
		{
		public:
			IVMasterRenderer(SDL_Window* _window, class OE1Core::Scene* _scene);
			~IVMasterRenderer();

			/// <summary>
			/// This function is called when ever there is a material update,
			/// Since the master renderer structure it's mesh based on the material for efficent rendering
			/// updating the material require the MasterRenderer update/restrusturing also
			/// for example all the transparent mesh rendered after the opaqe mesh, so if we
			/// made the material type transparent or vice versa at the middel of rendering process 
			/// the renderer need to re-evaluate all the mesh that uses this material and render them after the mesh that uses
			/// opaque material
			/// </summary>
			/// <param name="_prev_mat_type">What was the material type before it get updated, Until this moment the renderer know the original type, even though the material value is chnaged</param>
			/// <param name="_new_material">and Pointer to the material</param>
			void ReEvaluateRenderStackMaterial(MasterMaterial* _new_material);
			
			void PushToRenderStack(StaticMesh* _mesh);
			void PurgeFromRenderStack(StaticMesh* _mesh);

			void PushToRenderStack(DynamicMesh* _mesh);
			void PurgeFromRenderStack(DynamicMesh* _mesh);

			void ClientCameraPass(Component::CameraComponent* _clinet_camera);
			void MasterCameraPass(Component::CameraComponent* _camera);

			/// <summary>
			/// Must be called after all render command
			/// </summary>
			void FlushRenderCommand();
			inline IVGridRenderer& GetGridRenderer() { return m_GridRenderer; }; 
		protected: // Renderer
			IVGridRenderer m_GridRenderer;
			IVModelPreviewRenderer* m_ModelPreviewRenderer = nullptr;
			IVMeshRenderer* m_MeshRenderer = nullptr;
			IVOutlineRenderer* m_OutlineRenderer = nullptr;
			IVViewportBillboardIconRenderer* m_ViewportBillboardRenderer = nullptr;
			IVMaterialPreviewRenderer* m_MaterialPreviewRenderer = nullptr;
			IVFullScreenQuadRenderer* m_FullScreenQuadRenderer = nullptr;

			// Debug
			IVDebugShapeRenderer* m_DebugShapeRenderer = nullptr;
			IVSceneDebugShapeRenderer* m_SceneDebugShapeRenderer = nullptr;

		protected:
			class OE1Core::Scene* m_Scene = nullptr;


		public:
			void DefferedLightPass(Component::CameraComponent* _camera);
			/// <summary>
			/// This function will take the camera and render the rendered scene into the default frambuffer
			/// with screen full quad, REMEMBER this will clone rendered camera resolution and everything
			/// it will try to render attachment 0 by default, you can pass secode argument to spacify attachment index
			/// </summary>
			/// <param name="_camera">Target Camera</param>
			/// <param name="_attachment_idx">Which Framebuffer Attachment to render. Color, Depth, Stecil if you have any</param>
			void RenderFullScreenQuadToDefaultFramebuffer(Component::CameraComponent* _camera, int _attachment_idx = 0);
		};
	}
}

#endif // !OE1_IV_MASTER_RENDERER_H_
