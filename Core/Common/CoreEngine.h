#ifndef OE1_CORE_ENGINE_H_
#define OE1_CORE_ENGINE_H_

#include <ShlObj.h>
#include <Shlwapi.h> // For PathFileExists
#include <direct.h>

//#pragma comment(lib, "Shlwapi.lib")

#include "../Platform/Win/WindowManager.h"
// Renderer
#include "IVRender.h"

#include "CoreSystem.h"
#include "SceneSystem.h"
#include "ShaderSystem.h"

#include <ShaderManager/ShaderManager.h>
#include <UniformBuffer/UniformBlockManager.h>

#include "../AssetManager/ResourceInitializer.h"

#include "../Event/IEvent.h"
#include "../GUI/GUIBase.h"
#include "../Core/Command/ExecutionHandler.h"



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
		void CreateDefaultProjectDir();

	protected: // Event Handle
		bool HandleWindowCloseEvent(WindowCloseEvent& e);
		bool HandleWindowResizeEvent(WindowResizeEvent& e);
		void CleanVirtualAsset(std::string _dir);
		void InitializeDirectoryHierarchy(std::string _root);

	protected:
		inline static OE1Core::CoreSystem* s_CoreSystem = nullptr;
		inline static OE1Core::SceneSystem* s_SceneSystem = nullptr;
		inline static OE1Core::ShaderSystem* s_ShaderSystem = nullptr;

		inline static OE1Core::Window* s_Window = nullptr;
		inline static OE1Core::GUIBase* s_GuiBase = nullptr;
		inline static OE1Core::ShaderManager* s_ShaderManager = nullptr;
		inline static OE1Core::Memory::UniformBlockManager* s_MemeoryManager = nullptr;
		inline static OE1Core::Renderer::IVRender* s_MainSceneRenderer = nullptr;
		inline static OE1Core::ResourceInitializer* s_ResourceInitializer = nullptr;
		
	};
}


#endif // !OE1_CORE_ENGINE_H_
