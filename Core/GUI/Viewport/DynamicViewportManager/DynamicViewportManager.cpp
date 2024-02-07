#include "DynamicViewportManager.h"
#include "LogUI.h"

namespace OE1Core
{
	DynamicViewportManager::DynamicViewportManager()
	{

	}
	DynamicViewportManager::~DynamicViewportManager()
	{
		for (auto viewport : m_DynamicViewport)
			delete viewport.second;
		m_DynamicViewport.clear();
	}

	DynamicViewport* DynamicViewportManager::RegisterDynamicViewport(std::string _name, CameraPackage* _camera)
	{
		if (m_DynamicViewport.find(_name) != m_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to create viewport! The same already exist", OELog::CRITICAL));
			return nullptr;
		}

		if (!_camera->HasParentEntity())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to create viewport! Invalid Camera Property!", OELog::CRITICAL));
			return nullptr;
		}

		Entity _camera_entity((entt::entity)_camera->GetParentEntity(), SceneManager::GetActiveScene());
		
		m_DynamicViewport.insert(std::make_pair(_name, new DynamicViewport(_camera, _name, _camera_entity)));
		return m_DynamicViewport[_name];
	}
	DynamicViewport* DynamicViewportManager::GetViewport(std::string _name)
	{
		if (m_DynamicViewport.find(_name) != m_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to find viewport!", OELog::CRITICAL));
			return nullptr;
		}
		return m_DynamicViewport[_name];
	}
	bool DynamicViewportManager::HasViewport(std::string _name)
	{
		return m_DynamicViewport.find(_name) != m_DynamicViewport.end();
	}
	bool DynamicViewportManager::PurgeDynamicViewport(std::string _name)
	{
		if (m_DynamicViewport.find(_name) == m_DynamicViewport.end())
		{
			LOG_ERROR(LogLayer::Pipe("Unable to find viewport for removal!", OELog::CRITICAL));
			return false;
		}
		
		delete m_DynamicViewport[_name]; 
		m_DynamicViewport.erase(_name);


		return true;
	}
}