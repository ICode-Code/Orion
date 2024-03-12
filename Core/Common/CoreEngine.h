#ifndef OE1_CORE_ENGINE_H_
#define OE1_CORE_ENGINE_H_

#include <ShlObj.h>
#include <Shlwapi.h> // For PathFileExists
#include <direct.h>

#include "../Core/ProjectManager/ProjectManager.h"

//#pragma comment(lib, "Shlwapi.lib")

#include "../Platform/Win/WindowManager.h"
// Renderer
#include "../Core/InfiniteVision/IVMasterRenderer.h"

#include "CoreSystem.h"
#include "SceneSystem.h"
#include "ShaderSystem.h"

#include <ShaderManager/ShaderManager.h>
#include <UniformBuffer/UniformBlockManager.h>

#include "../AssetManager/ResourceInitializer.h"

#include <IEvent/IEvent.h>
#include "../GUI/GUIBase.h"

#include "../Core/ThreadManager/ThreadManager.h"

#include "../Core/Command/ExeHandleManager/ExeHandleManager.h"

#include "../Core/CoreAnimation/AnimationManager/AnimationManager.h"



namespace OE1Core
{
	struct ThreadPackage
	{
		OE1Core::Window* EngineWindow;
		SDL_Window* SDLWindow;
		SDL_GLContext SharedContext;
	};
	class CoreEngine
	{
	public:
		CoreEngine(int argc, char** argv);
		~CoreEngine();

		void Run();
		void OnEvent(OECore::IEvent& e);


	private:
		inline static std::thread s_PureComputationThread;
		static void _exe_RunComputeThread();
		static int __exe_RunTimeCommandProcessingThread(void* _data);
		inline static bool __TerminateSharedThread = false;

	protected: // Event Handle
		bool HandleWindowCloseEvent(OECore::WindowCloseEvent& e);
		bool HandleWindowResizeEvent(OECore::WindowResizeEvent& e);
		bool HandleWindowMax(OECore::WindowMaximizedEvent& e);
		bool HandleWindowMin(OECore::WindowMinimizedEvent& e);
		bool HandleApplicationKeyInput(OECore::KeyPressedEvent& e);


	protected:
		inline static OE1Core::CoreSystem* s_CoreSystem = nullptr;
		inline static OE1Core::SceneSystem* s_SceneSystem = nullptr;
		inline static OE1Core::ShaderSystem* s_ShaderSystem = nullptr;

		inline static OE1Core::Window* s_Window = nullptr;
		inline static OE1Core::GUIBase* s_GuiBase = nullptr;
		inline static OE1Core::ShaderManager* s_ShaderManager = nullptr;
		inline static OE1Core::Memory::UniformBlockManager* s_MemeoryManager = nullptr;
		inline static OE1Core::ResourceInitializer* s_ResourceInitializer = nullptr;
		inline static OE1Core::ProjectManager* s_ProjectManager = nullptr;
		inline static OE1Core::CommandHnd::ExeHandleManager* s_CommandExecutionHandleManager = nullptr;
		inline static OE1Core::AnimationManager* s_AnimationManager = nullptr;
	};
}


#endif // !OE1_CORE_ENGINE_H_
