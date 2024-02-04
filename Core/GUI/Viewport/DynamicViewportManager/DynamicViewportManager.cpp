#include "DynamicViewportManager.h"
#include "LogUI.h"

namespace OE1Core
{
	DynamicViewportManager::DynamicViewportManager()
	{

	}
	DynamicViewportManager::~DynamicViewportManager()
	{
		for (auto viewport : s_DynamicViewport)
			delete viewport.second;
		s_DynamicViewport.clear();
	}

	DynamicViewport* DynamicViewportManager::RegisterDynamicViewport(std::string _name, CameraPackage* _camera)
	{
		if (s_DynamicViewport.find(_name) != s_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to create viewport! The same already exist", OELog::CRITICAL));
			return nullptr;
		}

		s_DynamicViewport.insert(std::make_pair(_name, new DynamicViewport(_camera, _name)));
		return s_DynamicViewport[_name];
	}
	DynamicViewport* DynamicViewportManager::GetViewport(std::string _name)
	{
		if (s_DynamicViewport.find(_name) != s_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to find viewport!", OELog::CRITICAL));
			return nullptr;
		}
		return s_DynamicViewport[_name];
	}
	bool DynamicViewportManager::PurgeDynamicViewport(std::string _name)
	{
		if (s_DynamicViewport.find(_name) != s_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to find viewport for removal!", OELog::CRITICAL));
			return false;
		}
		
		delete s_DynamicViewport[_name];
		s_DynamicViewport.erase(_name);


		return true;
	}
}