#include "CoreEngine.h"

namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{

		///////////////////////// ORDER MATTER HERE SO DON'T FUCK IT UP ///////////////////////////
		
		s_ProjectManager = new ProjectManager();

		// Init Window System
		s_EngineWindow = OE1Core::WindowManager::GetEngineWindow();
		s_EngineWindow->EnableWin();

		// Register ImGui Event Callabck
		s_EngineWindow->RegisterImGuiSDLEventProcessorCallback(std::bind(ImGui_ImplSDL2_ProcessEvent, std::placeholders::_1));
		s_EngineWindow->RegisterFollowUpEventCallback(std::bind(&CoreEngine::OnEngineEvent, this, std::placeholders::_1));
		s_EngineWindow->SetCloseTrigger(&CloseWin::s_ShouldOpen);



		// Load compile all the Shader
		s_ShaderManager = new OE1Core::ShaderManager();

		// Init resource
		s_ResourceInitializer = new OE1Core::ResourceInitializer();

		// Init UI
		s_GuiBase = new OE1Core::GUIBase(s_EngineWindow->GetWin(), &s_EngineWindow->m_Args.MainContext);

		// Init System Interface
		// This guys will be imporatnt whe  we have dynamic lib who want to interact with the core
		s_CoreSystem = new OE1Core::CoreSystem();
		s_SceneSystem = new OE1Core::SceneSystem();
		s_ShaderSystem = new OE1Core::ShaderSystem(); 

		// Buffer Manger
		s_MemeoryManager = new Memory::UniformBlockManager(s_ShaderSystem);

		// Animation Manager
		s_AnimationManager = new AnimationManager();

		// Create Master Scene
		SceneManager::RegisterScene("MasterScene", new Scene(s_EngineWindow->GetWin(), &s_EngineWindow->m_Args.MainContext), true);
		// command processing
		s_CommandExecutionHandleManager = new OE1Core::CommandHnd::ExeHandleManager(SceneManager::GetActiveScene());

	}

	CoreEngine::~CoreEngine()
	{
		delete s_ProjectManager;
		delete s_GuiBase;
		delete s_CoreSystem;
		delete s_SceneSystem;
		delete s_ShaderSystem;
		delete s_ShaderManager;
		delete s_MemeoryManager;
		delete s_AnimationManager;
		delete s_ResourceInitializer;
		delete s_CommandExecutionHandleManager;
	}
	void CoreEngine::RunEngine()
	{

		// Prepare window
		s_EngineWindow->EnableWin();
		s_EngineWindow->RegisterImGuiSDLEventProcessorCallback(std::bind(ImGui_ImplSDL2_ProcessEvent, std::placeholders::_1));
		s_EngineWindow->RegisterFollowUpEventCallback(std::bind(&CoreEngine::OnEngineEvent, this, std::placeholders::_1));
		s_EngineWindow->ResetCallbacks();
		SceneManager::GetActiveScene()->SwitchContext(s_EngineWindow);
		SceneManager::GetActiveScene()->m_CameraManager->EngagePilotMode(SceneManager::GetActiveScene()->m_MasterSceneCamera->Camera->GetID());
		
		// Render Loop
		while (s_EngineWindow->m_Args.Running && !s_EngineWindow->m_Args.Playing)
		{
			// any queued command will be executed here
			CommandHnd::ExeHandleManager::ProcessContextCommandQueue();

			SceneManager::UpdateSceneInEngine(s_EngineWindow->m_Args.DeltaTime);

			SceneManager::RenderScenesInEngine();


			s_EngineWindow->PullEvent();
			s_GuiBase->Attach();
			s_GuiBase->Update();
			s_GuiBase->Render(s_EngineWindow->GetWin(), s_EngineWindow->m_Args.MainContext);

			s_EngineWindow->SwapBuffer();
		}
	}
	void CoreEngine::RunGenesis()
	{
		// Query current window ptr
		s_GenesisWindow = WindowManager::GetGenesisWindow();
		

		// Make Sure it is valid
		if (!s_GenesisWindow)
			return;

		// Prepare for the render loop
		s_GenesisWindow->EnableWin();
		s_GenesisWindow->RegisterFollowUpEventCallback(std::bind(&CoreEngine::OnGenesisEvent, this, std::placeholders::_1));
		s_GenesisWindow->RegisterFrameSizeUpdateCallback(std::bind(&CoreEngine::OnGenesisFrameSizeUpdate, this, std::placeholders::_1, std::placeholders::_2));
		s_GenesisWindow->ResetCallbacks(); 
		SceneManager::GetActiveScene()->SwitchContext(s_GenesisWindow);


		// Render Loop
		while (s_GenesisWindow->m_Args.Running && s_EngineWindow->m_Args.Playing)
		{
			s_GenesisWindow->PullEvent();


			// any queued command will be executed here
			CommandHnd::ExeHandleManager::ProcessContextCommandQueue();

			SceneManager::UpdateSceneInGame(s_GenesisWindow->m_Args.DeltaTime);


			SceneManager::RenderScenesInGame();

			s_GenesisWindow->SwapBuffer();
		}

		if (SceneManager::GetActiveScene()->GetProtagonist())
		{
			if (SceneManager::GetActiveScene()->GetProtagonist()->GetCamera())
			{
				SceneManager::GetActiveScene()->GetProtagonist()->GetCamera()->SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE::IDEL);
				SceneManager::GetActiveScene()->GetProtagonist()->GetCamera()->SetPowerState(CameraParameter::CAMERA_POWER_STATE::OFF);

			}
		}

		// On exist we destory the window 
		WindowManager::DestroyGenesisWindow();
	}
	void CoreEngine::Run()
	{

		THREAD_IGNITION();
		

		while (s_EngineWindow->m_Args.Running)
		{
			RunEngine();

			RunGenesis();
		}


		TERMINATE_SHARED_THREAD = !TERMINATE_SHARED_THREAD;
	}
	void CoreEngine::RUN_TIME_COMPUTATION_THREAD()
	{
		COMPUTATION_THREAD.detach();
		while (!TERMINATE_SHARED_THREAD)
		{
			if(!SceneManager::GetActiveScene()->ShouldUseRenderThreadForAnimationUpdate())
				SceneManager::GetActiveScene()->UpdateAnimationTransform();
		}
	}
	int CoreEngine::RUN_TIME_COMMAND_PROCESSING_THREAD(void* _data)
	{
		WindowArg* pkg = static_cast<WindowArg*>(_data);

		int __thread_share = SDL_GL_MakeCurrent(pkg->Win, pkg->SharedContext);
		if (__thread_share != 0)
		{
			LOG_ERROR("Unable to Share Context! Processing Low Frequency Command is not possible! aborting...");
			s_EngineWindow->Close();
			return 0;
		}

		while (!TERMINATE_SHARED_THREAD)
		{
			CommandHnd::ExeHandleManager::ProcessLowFrequencyCommands();
			std::this_thread::sleep_for(3.5s);
		}

		return 0;
	}
	void CoreEngine::THREAD_IGNITION()
	{
		SDL_Thread* COMMAND_PROCESSING_THREAD = SDL_CreateThread(RUN_TIME_COMMAND_PROCESSING_THREAD, "RunTimeCommand", &s_EngineWindow->m_Args);
		COMPUTATION_THREAD = std::thread(&CoreEngine::RUN_TIME_COMPUTATION_THREAD);
	}
	void CoreEngine::OnEngineEvent(OECore::IEvent& e)
	{
		s_GuiBase->OnEvent(e);
		if (!e.Handled())
			SceneManager::OnEvent(e);
	}
	void CoreEngine::OnGenesisEvent(OECore::IEvent& e)
	{
		SceneManager::OnEventGenesis(e);
	}
	void CoreEngine::OnGenesisFrameSizeUpdate(int _width, int _height)
	{
		SceneManager::GetActiveScene()->UpdateFrameRes_Genesis(_width, _height);
	}
}