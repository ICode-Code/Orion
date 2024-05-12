#ifndef OE1_RENDER_CONTROLLER_H_
#define OE1_RENDER_CONTROLLER_H_




namespace OE1Core
{
	/// <summary>
	/// This class is reposible for interacting with the master renderer
	/// </summary>
	class RenderController
	{
	public:
		RenderController(class Scene* _scene);
		~RenderController();


		/// <summary>
		/// Master Camera/ The Editor Camera
		/// </summary>
		void RenderMasterCameraScene();
		/// <summary>
		/// Any Camera Created during level design,
		/// Rememebr Client Camera Draw only mesh NOT dev option like grid, billboard
		/// </summary>
		void RenderClientCameraScene();

		/// <summary>
		/// Must be called after all draw calles
		/// </summary>
		void FlushRenderCommand();

	private:
		class Scene* m_Scene = nullptr;
	};
}

#endif // !OE1_RENDER_CONTROLLER_H_
