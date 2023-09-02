#ifndef OE1_GRID_RENDERER_H_
#define OE1_GRID_RENDERER_H_

#include "../BaseRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) GridRenderer : public BaseRenderer
		{
		public:
			GridRenderer(SceneInterface* _scene_interface, CoreSystemInterface* _coreSystem_interface);
			~GridRenderer();

			void Update();
			void Render();

		private: 
			GLuint s_VAO;
			float s_ColorLight[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
			float s_ColorBold[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
			float s_Background[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
			float s_Scale = 1000.0f;

		};
	}
}

#endif // !OE1_GRID_RENDERER_H_
