#include "TopMenuLayer.h"
#include "../Viewport/DynamicViewportManager/DynamicViewportManager.h"


namespace OE1Core
{
	TopMenuLayer::TopMenuLayer()
	{

	}
	TopMenuLayer::~TopMenuLayer() 
	{

	}

	void TopMenuLayer::Update()
	{

	}
	void TopMenuLayer::Render()
	{
		ImGui::BeginMainMenuBar();
		
		this->File();
		this->Edit();
		this->Tools();
		this->Import();
		this->Component();
		this->Debug();
		this->Window();
		this->Help();


		ImGui::EndMainMenuBar();

		//ImGui::Image((ImTextureID)SceneManager::GetActiveScene()->m_LightRoom->LUT, { 512, 512 }, { 0, 1 }, { 1, 0 });
	}

	void TopMenuLayer::File()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem(ICON_FA_FILE_MEDICAL"   New"))
			{
				ProjectCreatorWin::Open();
			}
			if (ImGui::BeginMenu(ICON_FA_MOUNTAIN_SUN"   Scene"))
			{
				if (ImGui::MenuItem("New Scene"))
				{

				}
				if (ImGui::BeginMenu("Template"))
				{
					if (ImGui::MenuItem("PBR Example"))
					{

					}
					if (ImGui::MenuItem("FPS Example"))
					{

					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN"   Open..."))
			{

			}
			if (ImGui::BeginMenu(ICON_FA_FOLDER_OPEN"   Open Recent"))
			{
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_PLUS"   Import 3D Asset..."))
			{
				/*std::string __path = OE1Core::FileDialog::OE1WindowNativeDialog::LoadFile("*.gltf\0*.gltf");
				if (!__path.empty())
				{
					UI::ImportantWindow::m_BeginDialog = true;
					UI::ImportantWindow::m_AssetDir = __path;
				}*/

				//std::string loaded_file = WindowFileDialog::LoadFile("GLTF Files (*.gltf;*.glb)\0*.gltf;*.glb\0FBX Files (*.fbx)\0*.fbx\0", WindowManager::GetWindow(ENGINE_MAIN_WINDOW)->GetWin());
				std::string loaded_file = WindowFileDialog::LoadFile("GLTF and FBX Files (*.gltf;*.glb;*.fbx)\0*.gltf;*.glb;*.fbx\0", WindowManager::GetEngineWindow()->GetWin(), "Load 3D Asset");
				if (!loaded_file.empty())
				{
					Asset3DLoaderWin::Open(loaded_file);
					//Command::PushLoadCommand(loaded_file);
				}
			}
			if (ImGui::MenuItem(ICON_FA_IMAGE"   Import Texture..."))
			{
				std::string file_path = WindowFileDialog::LoadFile("png and jpg Files (*.png;*.jpg;)\0*.png;*.jpg\0", WindowManager::GetEngineWindow()->GetWin(), "Load Textures");
				if (!file_path.empty())
				{
					CommandDef::TextureLoadCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
					command.Name = Loader::NameHandle::FilterFileName(file_path);
					command.Path = file_path;
					command.Destination = ORI_PROJECT_HOT_DIRECTORY;
					Command::PushTextureLoadCommand(command);
				}
			}
			if (ImGui::MenuItem(ICON_FA_FILE_CIRCLE_PLUS"   Import Audio..."))
			{
				std::string loaded_file = WindowFileDialog::LoadFile("Wav Files (*.wav;)\0*.wav\0", WindowManager::GetEngineWindow()->GetWin(), "Load Audio");
				if (!loaded_file.empty())
				{
					SceneManager::GetActiveScene()->GetAudioMaster()->LoadAudio(loaded_file, Loader::NameHandle::FilterFileName(loaded_file));
				}
			}
			if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK"   Save", "  Ctr + S"))
			{

			}
			if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK"   Save As..", " LShit + S"))
			{

			}
			if (ImGui::MenuItem(ICON_FA_ARROW_RIGHT_FROM_BRACKET"   Exit", "  Alt + F4"))
			{

			}

			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Edit()
	{
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::BeginDisabled(!SceneManager::QueryActiveEntity()->ValidSelection());

			if (ImGui::MenuItem(ICON_FA_SCISSORS"   Cut"))
			{

			}
			if (ImGui::MenuItem(ICON_FA_COPY"   Copy"))
			{

			}
			if (ImGui::MenuItem(ICON_FA_PASTE"   Past"))
			{

			}
			if (ImGui::MenuItem(ICON_FA_XMARK"   Delete"))
			{
				SceneManager::PurgActiveEntity();
			}
			if (ImGui::MenuItem(ICON_FA_I_CURSOR"	Rename"))
			{
				Entity active = SceneManager::QueryActiveEntity()->GetActive();

				if (active.HasComponent<Component::TagComponent>())
				{
					RenameWin::Open(
						active.GetComponent<Component::TagComponent>()
					);
				}
			}


			ImGui::EndDisabled();

			ImGui::Separator();

			if (ImGui::BeginMenu(ICON_FA_MOUNTAIN_SUN"	World Light (Quick Setting)"))
			{

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(ICON_FA_MOUNTAIN"	Landscape"))
			{
				


				ImGui::EndMenu();
			}

			if (ImGui::MenuItem(ICON_FA_GEAR"   Preferences"))
			{
				PreferenceWin::s_ShouldOpen = !PreferenceWin::s_ShouldOpen;
			}


			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Component()
	{
		if (ImGui::BeginMenu("Components"))
		{

			if (ImGui::BeginMenu(ICON_FA_MOUNTAIN_SUN"	Camera-Controller"))
			{
				if (ImGui::MenuItem(ICON_FA_CAMERA_ROTATE"    Third-Person Controller", "Camera movement behaviour controller"))
				{
					if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
					{
						SceneEntityFactory::AddThirdPersoneCameraController(
							SceneManager::GetActiveScene()->GetActiveEntity()->GetActive()
						);
					}
				}

				if (ImGui::MenuItem(ICON_FA_CAMERA_ROTATE"    Free-Look Controller", "Camera movement behaviour controller"))
				{
					if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
					{
						SceneEntityFactory::AddFreeLookCameraController(
							SceneManager::GetActiveScene()->GetActiveEntity()->GetActive()
						);
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu(ICON_FA_MOUNTAIN_SUN"	Character-Controller"))
			{
				if (ImGui::MenuItem(ICON_FA_STREET_VIEW"    Third-Person Controller", "Character movement controller"))
				{
					if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
					{
						SceneEntityFactory::AddThirdPersonCharacterControllerComponent(
							SceneManager::GetActiveScene()->GetActiveEntity()->GetActive()
						);
					}
				}

				if (ImGui::MenuItem(ICON_FA_STREET_VIEW"    FPS Controller", "Character movement controller"))
				{
					if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
					{

					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem(ICON_FA_CODE"    Script", "Lua Script"))
			{
				if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
				{
					SceneEntityFactory::AddScriptComponent(
						SceneManager::GetActiveScene()->GetActiveEntity()->GetActive()
					);
				}
			}
			
			

			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Window()
	{
		if (ImGui::BeginMenu("Window"))
		{

			if (ImGui::MenuItem("    Save Window Layout", "    ", false))
			{

			}
			if (ImGui::MenuItem("    Reset Window Layout", "    ", false))
			{

			}

			ImGui::Separator();

			if (ImGui::BeginMenu("Viewport"))
			{
				Scene* __scene = SceneManager::GetActiveScene();
				auto __camera_component_view = __scene->m_EntityRegistry.view<Component::CameraComponent>();
				for (auto ent : __camera_component_view)
				{
					Component::TagComponent& _tag = __scene->m_EntityRegistry.get<Component::TagComponent>(ent);
					

					std::string _name = ICON_FA_VIDEO"		" + _tag.m_Identifier;

					if (ImGui::MenuItem(_name.c_str(), "    "))
					{
						DynamicViewport* res = DynamicViewportManager::RegisterDynamicViewport(_tag.m_Identifier, &__camera_component_view.get<Component::CameraComponent>(ent));
						if (res)
							res->Open();

					}
				}

				ImGui::EndMenu();
			}


			ImGui::Separator();

			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Inspector", "    ");
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Scene Hierarchy", "    ");
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Content Browser", "    ");
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Log", "    ");
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Renderer Info", "    ");
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    Tool-Bar", "    ", true);
			ImGui::MenuItem(ICON_FA_WINDOW_RESTORE"    ImGUi Demo", "    ");



			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Tools()
	{
		if (ImGui::BeginMenu("Tools"))
		{
			//ImGui::BeginDisabled(mRenderLayer->m_ActiveScene->GetSceneState() == LandscapeTopologyEdit || mRenderLayer->m_ActiveScene->GetSceneState() == LandscapeMaterialEdit);
			
			if (ImGui::MenuItem(ICON_FA_MOUNTAIN"   Landscape Tool", "        GameObject        "))
			{

			}

			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Import()
	{
		if (ImGui::BeginMenu("Import"))
		{
			if (ImGui::BeginMenu("Scene Light"))
			{
				if (ImGui::MenuItem(ICON_FA_LIGHTBULB"   Point Light", "        GameObject        "))
				{
					if (!SceneEntityFactory::GetScene()->HasBillboardType(ViewportIconBillboardType::POINT_LIGHT))
						SceneEntityFactory::GetScene()->RegisterBillboardIcon(ViewportIconBillboardType::POINT_LIGHT, "PointLight");
					SceneManager::GetActiveScene()->GetActiveEntity()->Pick(SceneEntityFactory::CreatePointLight(), true);
				}
				if (ImGui::MenuItem(ICON_FA_LIGHTBULB"   Spot Light", "        GameObject        "))
				{
					if (!SceneEntityFactory::GetScene()->HasBillboardType(ViewportIconBillboardType::SPOT_LIGHT))
						SceneEntityFactory::GetScene()->RegisterBillboardIcon(ViewportIconBillboardType::SPOT_LIGHT, "SpotLight");
					SceneManager::GetActiveScene()->GetActiveEntity()->Pick(SceneEntityFactory::CreateSpotLight(), true);
				}
				if (ImGui::MenuItem(ICON_FA_LIGHTBULB"   Directional Light", "        GameObject        "))
				{
					if (!SceneEntityFactory::GetScene()->HasBillboardType(ViewportIconBillboardType::DIRECTIONAL_LIGHT))
						SceneEntityFactory::GetScene()->RegisterBillboardIcon(ViewportIconBillboardType::DIRECTIONAL_LIGHT, "Sun");
					SceneManager::GetActiveScene()->GetActiveEntity()->Pick(SceneEntityFactory::CreateDirectionalLight());
				}

				ImGui::EndMenu();
			}

			//if (ImGui::BeginMenu("Audio Source"))
			//{
			//	/*if (ImGui::MenuItem(ICON_FA_VOLUME_HIGH"   Global Ambient", "        GameObject        "))
			//	{
			//		if (!SceneEntityFactory::GetScene()->HasBillboardType(ViewportIconBillboardType::AUDIO_SOURCE))
			//			SceneEntityFactory::GetScene()->RegisterBillboardIcon(ViewportIconBillboardType::AUDIO_SOURCE, "AudioSource");
			//		
			//		SceneManager::GetActiveScene()->GetActiveEntity()->Pick(
			//			SceneEntityFactory::CreateGlobalAudioSource());
			//	}*/

			//	ImGui::EndMenu();
			//}
			
			if (ImGui::BeginMenu("Simple Mesh"))
			{
				if (ImGui::MenuItem(ICON_FA_CUBE"   Cube", "        GameObject        "))
				{

				}
				if (ImGui::MenuItem(ICON_FA_CUBE"   Plane", "        GameObject        "))
				{

				}
				if (ImGui::MenuItem(ICON_FA_CUBE"   Sphere", "        GameObject        "))
				{

				}
				if (ImGui::MenuItem(ICON_FA_CUBE"   Cylinder", "        GameObject        "))
				{

				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem(ICON_FA_BOX_OPEN"   Empty", "        GameObject        "))
			{

			}
			if (ImGui::MenuItem(ICON_FA_VIDEO"   Camera", "        GameObject        "))
			{
				if (!SceneEntityFactory::GetScene()->HasBillboardType(ViewportIconBillboardType::CAMERA))
					SceneEntityFactory::GetScene()->RegisterBillboardIcon(ViewportIconBillboardType::CAMERA, "Camera");

				SceneManager::GetActiveScene()->GetActiveEntity()->Pick(SceneEntityFactory::CreateSceneCamera());
			}

			if (ImGui::MenuItem(ICON_FA_FLAG_CHECKERED"   Actor", "        Player Template        "))
			{
				SceneEntityFactory::CreateActor();
			}

			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Debug()
	{
		if (ImGui::BeginMenu("Debug"))
		{
			if (ImGui::MenuItem(ICON_FA_PLAY"   Run / Debug", "        -        "))
			{
				if (!WindowManager::GetGenesisWindow())
				{
					WindowManager::IgniteGenesisWindow();

					if (SceneManager::GetActiveScene()->GetProtagonist())
						if (SceneManager::GetActiveScene()->GetProtagonist()->GetCamera())
							SceneManager::GetActiveScene()->m_CameraManager->EngagePilotMode(SceneManager::GetActiveScene()->GetProtagonist()->GetCamera()->GetID());
				}
			}

			if (ImGui::MenuItem(ICON_FA_PLAY"   Recompile Main Shader", "        -        "))
			{
				CommandDef::ShaderRecompileCommandDef commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
				commandX.ID = ShaderID::DEFFERED_LIGHT_PASS;

				Command::PushShaderRecompileCommand(commandX);
			}

			ImGui::EndMenu();
		}
	}
	void TopMenuLayer::Help()
	{
		if (ImGui::BeginMenu("Help"))
		{

			ImGui::EndMenu();
		}
	}
}