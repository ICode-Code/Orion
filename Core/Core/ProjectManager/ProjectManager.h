#ifndef OE1_PROJECT_MANAGER_H_
#define OE1_PROJECT_MANAGER_H_

#include <Log.h>

#include "ProjectUtil.h"
#include "PreDef.h"
#include <fstream>
#include <filesystem>

#include <ShlObj.h>
#include <Shlwapi.h> // For PathFileExists

#include <unordered_map>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace OE1Core
{
	class ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager();

		static void CreateProject(std::string _name);
		static ProjectConfig& GetActiveProject();

	protected:
		static void Init();
		static void CreateProjectDirStrcture(std::wstring _project_root);
		static void CleanVirtualAsset(std::string _path);
		static void InitializeDirectoryHierarchy(std::string _root);

	protected:
		static void InitlizeMetaData();
		static void Serilize(std::ofstream& _file);
		static void ReadProjectConfig();

	protected:
		void QueryRootProjectPath();



	protected:
		inline static ProjectConfig s_ActiveProject;
		inline static std::unordered_map<std::string, ProjectConfig> s_ProjectConfig;
	};
}

#endif // !OE1_PROJECT_MANAGER_H_
