#ifndef OE1_GUI_BASE_H_
#define OE1_GUI_BASE_H_

#include "Gui.h"

#include "Layer/ILayer.h"
#include <vector>

namespace OE1Core
{
	class GUIBase
	{
	public:
		GUIBase(GLFWwindow* _window);
		~GUIBase();

		static void Update();
		static void Attach();
		static void Render();
		static void SetContext(GLFWwindow* _window);


	public:
		inline static std::vector<LayerBase*> s_Layers;

	protected:
		inline static GLFWwindow*  s_Window = nullptr;
		inline static OE1Core::Gui* s_GUI = nullptr;
	};
}

#endif // !OE1_GUI_BASE_H_
