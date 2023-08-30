#ifndef OE1_CORE_ENGINE_H_
#define OE1_CORE_ENGINE_H_

#include "../Platform/Win/WindowManager.h"
#include "../Event/IEvent.h"
#include "../GUI/GUIBase.h"
#include "../Core/Command/ExecutionHandler.h"

#include "CoreSystem.h"

// Renderer
#include "IVRender.h"

namespace OE1Core
{
	class CoreEngine
	{
	public:
		CoreEngine(int argc, char** argv);
		~CoreEngine();

		void Run();
		void OnEvent(Event& e);


	protected:
		bool HandleWindowCloseEvent(WindowCloseEvent& e);
		bool HandleWindowResizeEvent(WindowResizeEvent& e);

	protected:
		inline static OE1Core::CoreSystem* s_CoreSystem = nullptr;
		inline static OE1Core::Window* s_Window = nullptr;
		inline static OE1Core::GUIBase* s_GuiBase = nullptr;
		inline static OE1Core::Renderer::IVRender* s_MainSceneRenderer = nullptr;
	};
}


#endif // !OE1_CORE_ENGINE_H_
