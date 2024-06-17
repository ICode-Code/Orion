#include "RTSInitializer.h"



namespace OE1Core
{
	RTSIntializer::RTSIntializer()
	{


	}
	RTSIntializer::~RTSIntializer()
	{
	}

	std::string RTSIntializer::CreateRTSTemplate(std::string _name)
	{
		std::string _full_url = ORI_PROJECT_HOT_DIRECTORY + "\\" + _name + ".lua";
		std::ofstream script_file(_full_url, std::ios::out | std::ios::binary);
		WriteBinary(script_file, "-- ORION ENGINE  \n\n");
		WriteBinary(script_file, "function onInit() \n");
		WriteBinary(script_file, "-- Called when the script is initialized \n");
		WriteBinary(script_file, "end \n\n");

		WriteBinary(script_file, "function onUpdate() \n");
		WriteBinary(script_file, "-- Called on every frame \n");
		WriteBinary(script_file, "end \n\n");

		WriteBinary(script_file, "function onEnable() \n\n");
		WriteBinary(script_file, "-- Called when the script is enabled \n");
		WriteBinary(script_file, "end \n\n");


		WriteBinary(script_file, "function onDisable() \n");
		WriteBinary(script_file, "-- Called when the script is disabled \n");
		WriteBinary(script_file, "end \n\n");

		script_file.close();

		s_Scripts.insert(std::make_pair(_name, _full_url));

		Command::CALL_ContentBrowserLayerNotifyCallback();

		return _full_url;
	}
	void RTSIntializer::WriteSourceToFile(std::string _path, const std::string& _source)
	{
		std::ofstream file(_path); // Open file at _path

		if (file.is_open()) {
			file << _source; // Write _source to the file
			file.close(); // Close the file
		}
	}
	std::string RTSIntializer::QuerySource(std::string _path)
	{
		std::ifstream file(_path);
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open file: " + _path);
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
	std::string RTSIntializer::GetSourcePath(std::string _name)
	{
		if (s_Scripts.find(_name) == s_Scripts.end())
			return std::string("");

		return s_Scripts[_name];
	}

	void RTSIntializer::WriteBinary(std::ofstream& _file, std::string _data)
	{
		_file.write(_data.c_str(), _data.size());
	}
}