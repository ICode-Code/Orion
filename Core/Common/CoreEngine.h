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
	class CoreEngine
	{
	public:
		CoreEngine(int argc, char** argv);
		~CoreEngine();

		void Run();

	private:
		void RunEngine();
		void RunGenesis();

		void OnEngineEvent(OECore::IEvent& e);

		void OnGenesisEvent(OECore::IEvent& e);
		void OnGenesisFrameSizeUpdate(int _width, int _height);

	private: // Thread managment
		static void THREAD_IGNITION();
		static void RUN_TIME_COMPUTATION_THREAD();
		static int RUN_TIME_COMMAND_PROCESSING_THREAD(void* _data);
		inline static std::thread COMPUTATION_THREAD;
		inline static bool TERMINATE_SHARED_THREAD = false;

	protected:
		inline static OE1Core::CoreSystem* s_CoreSystem = nullptr;
		inline static OE1Core::SceneSystem* s_SceneSystem = nullptr;
		inline static OE1Core::ShaderSystem* s_ShaderSystem = nullptr;
		inline static OE1Core::GUIBase* s_GuiBase = nullptr;
		inline static OE1Core::ShaderManager* s_ShaderManager = nullptr;
		inline static OE1Core::Memory::UniformBlockManager* s_MemeoryManager = nullptr;
		inline static OE1Core::ResourceInitializer* s_ResourceInitializer = nullptr;
		inline static OE1Core::ProjectManager* s_ProjectManager = nullptr;
		inline static OE1Core::CommandHnd::ExeHandleManager* s_CommandExecutionHandleManager = nullptr;
		inline static OE1Core::AnimationManager* s_AnimationManager = nullptr;

	protected: // Windows
		inline static OE1Core::EngineWindow* s_EngineWindow = nullptr;
		inline static OE1Core::GenesisWindow* s_GenesisWindow = nullptr;
	};
}


#endif // !OE1_CORE_ENGINE_H_
