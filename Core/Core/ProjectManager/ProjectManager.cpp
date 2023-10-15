#include  "ProjectManager.h"


namespace OE1Core
{
	ProjectManager::ProjectManager()
	{
		QueryRootProjectPath();

		InitlizeMetaData();
		ReadProjectConfig();

		if (s_ProjectConfig.empty())
			CreateProject("Pilot");

		s_ActiveProject = s_ProjectConfig.at("Pilot");


		ORI_ACTIVE_PATH += s_ActiveProject.Name;
		CleanVirtualAsset(ORI_ACTIVE_PATH);

	}
	ProjectManager::~ProjectManager()
	{
		CleanVirtualAsset(ORI_ACTIVE_PATH);
	}

	void ProjectManager::Init()
	{

	}
	void ProjectManager::CreateProjectDirStrcture(std::wstring _project_root)
	{
		PWSTR my_documents_path = nullptr;
		if (SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &my_documents_path) == S_OK)
		{
			std::wstring project_folder_path = my_documents_path;
			CoTaskMemFree(my_documents_path);

			project_folder_path += _project_root;

			if (!PathFileExists(project_folder_path.c_str()))
			{
				if (!CreateDirectoryW(project_folder_path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
				{
					LOG_ERROR("Failed to create ROOT folder");
				}
			}

			// Create Project folder
			project_folder_path += L"\\" + std::wstring(s_ActiveProject.Name.begin(), s_ActiveProject.Name.end());
			if (!PathFileExists(project_folder_path.c_str()))
			{
				if (!CreateDirectoryW(project_folder_path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
				{
					LOG_ERROR("Failed to create PROJECT folder");
				}
			}
			ORI_ACTIVE_PATH = WideStrToNarrowStr(project_folder_path);
			InitializeDirectoryHierarchy(ORI_ACTIVE_PATH + "\\");
		}
	}
	void ProjectManager::CleanVirtualAsset(std::string _path)
	{
		for (auto iter : std::filesystem::directory_iterator(_path))
		{
			if (iter.is_directory())
				CleanVirtualAsset(_path + "\\" + iter.path().stem().string());

			std::filesystem::remove_all(iter.path());
		}


		InitializeDirectoryHierarchy(ORI_ACTIVE_PATH + "\\");
	}
	void ProjectManager::InitializeDirectoryHierarchy(std::string _root)
	{
		std::filesystem::create_directories(_root + "Assets");
		std::filesystem::create_directories(_root + "Assets\\Meshes");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Characters");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Environment");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Weapons");
		std::filesystem::create_directories(_root + "Assets\\Audio");
		std::filesystem::create_directories(_root + "Assets\\Audio\\Music");
		std::filesystem::create_directories(_root + "Assets\\Audio\\SoundFX");
		std::filesystem::create_directories(_root + "Assets\\Textures");
		std::filesystem::create_directories(_root + "Assets\\Textures\\Characters");
		std::filesystem::create_directories(_root + "Assets\\Textures\\Environment");
		std::filesystem::create_directories(_root + "Assets\\Textures\\UI");
		std::filesystem::create_directories(_root + "Assets\\Scripts");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\AI");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\Gameplay");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\UI");
		std::filesystem::create_directories(_root + "Assets\\Prefabs");
		std::filesystem::create_directories(_root + "Assets\\Materials");
		std::filesystem::create_directories(_root + "Assets\\Shaders");
		std::filesystem::create_directories(_root + "Scenes");
		std::filesystem::create_directories(_root + "Scripts");
		std::filesystem::create_directories(_root + "Plugins");
		std::filesystem::create_directories(_root + "Build");
	}
	void ProjectManager::InitlizeMetaData()
	{
		std::ifstream project_config(ORI_ENGEIN_METAL_FILE);

		if (project_config.is_open())
		{
			LOG_INFO("Project configuration loaded succesfully!");
			project_config.close();
		}
		else
		{
			std::ofstream meta_out(ORI_ENGEIN_METAL_FILE);
			if (meta_out.is_open())
			{
				LOG_INFO("Project configuration created succesfully!");
				Serilize(meta_out);
				meta_out.close();
			}
			else
			{
				LOG_ERROR("Failed to create configuration file!");
			}
		}
	}
	void ProjectManager::Serilize(std::ofstream& _file)
	{
		for (const auto& pair : s_ProjectConfig)
		{
			boost::archive::text_oarchive archive(_file);
			archive << pair.second;
		}
	}
	void ProjectManager::ReadProjectConfig()
	{
		std::ifstream project_config(ORI_ENGEIN_METAL_FILE);
		if (project_config.is_open())
		{
			ProjectConfig config_data;
			boost::archive::text_iarchive archive(project_config);

			archive >> config_data;

			s_ProjectConfig.insert(std::make_pair(config_data.Name, config_data));
		}
		else
		{
			LOG_ERROR("Failed to read project configuration file");
		}

		project_config.close();
	}
	ProjectConfig& ProjectManager::GetActiveProject() { return s_ActiveProject; };

	void ProjectManager::QueryRootProjectPath()
	{
		PWSTR my_documents_path = nullptr;
		if (SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &my_documents_path) == S_OK)
		{
			std::wstring project_folder_path_wide = my_documents_path;
			CoTaskMemFree(my_documents_path);
			std::string project_folder_path = WideStrToNarrowStr(project_folder_path_wide);
			ORI_ACTIVE_PATH = project_folder_path + ORI_ORION_PROJECT_ROOT_PATH;
		}
	}
	void ProjectManager::CreateProject(std::string _name)
	{
		ProjectConfig config;
		config.ActiveRenderer = "InfiniteVision";
		config.API = "OpenGL";
		config.EngineVersion = "1.0";
		config.LastOpen = "-";
		config.Name = _name;
		config.Type = "General";
		config.Version = "1.0.0";

		s_ProjectConfig.insert(std::make_pair(config.Name, config));
	}
}