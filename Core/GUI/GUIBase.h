#ifndef OE1_GUI_BASE_H_
#define OE1_GUI_BASE_H_

#include "Layer/ILayer.h"
#include "Viewport/IViewport.h"
#include "MiniWindow/IMiniWin.h"

#include <vector>
#include <unordered_map>

namespace OE1Core
{
	class GUIBase
	{
	public:
		GUIBase(SDL_Window* _window, SDL_GLContext* _context);
		~GUIBase();

		static void OnEvent(OECore::IEvent& e);
		static void Update();
		static void Attach();
		static void Render(SDL_Window* _window, SDL_GLContext& _context);


	public:
		inline static std::vector<LayerBase*> s_Layers;
		inline static std::vector<BaseViewport*> s_Viewports;
		inline static std::vector<BaseMiniWindow*> s_MiniWins;

	protected:
		inline static OE1Core::Gui* s_GUI = nullptr;
	};
}

#endif // !OE1_GUI_BASE_H_
