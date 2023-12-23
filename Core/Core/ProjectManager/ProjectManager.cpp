#include  "ProjectManager.h"


namespace OE1Core
{
	ProjectManager::ProjectManager()
	{
		QueryRootProjectPath();

		if (ReadMetaData())
		{
			ReadProjectConfig();

			if (!s_ProjectConfig.empty())
			{
				ORI_ACTIVE_PATH += s_ProjectConfig.at("Pilot").Name;

				// In case if the user remove the directory structure
				if (!std::filesystem::exists(ORI_ACTIVE_PATH))
				{
					std::filesystem::create_directories(ORI_ACTIVE_PATH);
					InitializeDirectoryHierarchy(ORI_ACTIVE_PATH + "\\");
				}
			}
			else
			{
				LOG_ERROR("It seems project file is loaded, but empty!");
			}
			
			
		}
		else
		{
			// If there is no meta data it means there is no priore project
			// os create one

			// Create Project
			CreateProject("Pilot");
			InitlizeMetaData();
		}

		s_ActiveProject = s_ProjectConfig.at("Pilot");


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

		std::wstring project_folder_path = std::wstring(ORI_ACTIVE_PATH.begin(), ORI_ACTIVE_PATH.end());
		project_folder_path += _project_root;

		if (!std::filesystem::exists(project_folder_path))
		{
			std::filesystem::create_directories(project_folder_path);
		}

		ORI_ACTIVE_PATH = WideStrToNarrowStr(project_folder_path);
		InitializeDirectoryHierarchy(ORI_ACTIVE_PATH + "\\");
	}
	void ProjectManager::CleanVirtualAsset(std::string _path)
	{
		if (!std::filesystem::exists(_path))
			return;
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
	bool ProjectManager::InitlizeMetaData()
	{
		LOG_INFO("No configuration file found!");
		LOG_INFO("Creating new configuration file...");
		std::ofstream meta_out(ORI_ENGEIN_METAL_FILE);
		if (meta_out.is_open())
		{
			LOG_INFO("Project configuration file created succesfully!");
			Serilize(meta_out);
			meta_out.close();

			return true;
		}
		else
		{
			LOG_ERROR("Failed to create configuration file!");
		}

		return false;
	}
	bool ProjectManager::ReadMetaData()
	{
		std::ifstream project_config(ORI_ENGEIN_METAL_FILE);

		if (project_config.is_open())
		{
			LOG_INFO("Project configuration loaded succesfully!");
			project_config.close();

			return true;
		}

		return false;
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
		else
		{
			LOG_ERROR("Failed to locate local user Document path!");
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
		std::wstring _local_project_root = std::wstring(_name.begin(), _name.end());
		CreateProjectDirStrcture(_local_project_root);
	}
}