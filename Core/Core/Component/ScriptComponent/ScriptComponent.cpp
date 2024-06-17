#include "ScriptComponent.h"


namespace OE1Core
{
	namespace Component
	{
		ScriptComponent::ScriptComponent(std::string _name)
			: m_IsEnable(false)
		{
			m_State = luaL_newstate();
			luaL_openlibs(m_State);

			m_Name = _name;
			m_SourcePath = RTSIntializer::CreateRTSTemplate(m_Name);
			m_Source = RTSIntializer::QuerySource(m_SourcePath);
			if (luaL_dofile(m_State, m_SourcePath.c_str()) != LUA_OK)
			{
				m_Valid = false;
				const char* _load_error = lua_tostring(m_State, -1);
				LOG_ERROR("Error Loading Script: {0}", _load_error);
				lua_pop(m_State, 1);
				return;
			}

			m_Valid = true;
		}
		ScriptComponent::ScriptComponent(const ScriptComponent& _other)
		{

		}
		ScriptComponent::~ScriptComponent()
		{
			lua_close(m_State);
		}

		void ScriptComponent::OnInit()
		{
			
		}
		void ScriptComponent::OnUpdate()
		{
			lua_getglobal(m_State, "onUpdate");
			lua_pcall(m_State, 0, 0, 0);
		}
		void ScriptComponent::OnEnbale()
		{

		}
		void ScriptComponent::OnDisable()
		{

		}

		void ScriptComponent::OnInit_D()
		{
			lua_getglobal(m_State, "onInit");
			if (lua_pcall(m_State, 0, 0, 0) != LUA_OK)
			{
				const char* _error = lua_tostring(m_State, -1);
				m_Valid = false;
				LOG_ERROR("onInit Error:: {0}", _error);

				lua_pop(m_State, 1);
			}
		}
		void ScriptComponent::OnUpdate_D()
		{
			lua_getglobal(m_State, "onUpdate");
			if (lua_pcall(m_State, 0, 0, 0) != LUA_OK)
			{
				const char* _error = lua_tostring(m_State, -1);
				m_Valid = false;
				LOG_ERROR("onUpdate Error:: {0}", _error);

				lua_pop(m_State, 1);
			}
		}
		void ScriptComponent::OnEnbale_D()
		{

		}
		void ScriptComponent::OnDisable_D()
		{

		}

		void ScriptComponent::Enable(bool _val)
		{

		}
		bool ScriptComponent::IsActive()
		{
			return m_IsEnable && m_Valid;
		}
		void ScriptComponent::ReCompileSource()
		{
			m_Source = RTSIntializer::QuerySource(m_SourcePath);
			if (luaL_dofile(m_State, m_SourcePath.c_str()) != LUA_OK)
			{
				m_Valid = false;
				const char* _load_error = lua_tostring(m_State, -1);
				LOG_ERROR("Error Loading Script: {0}", _load_error);
				lua_pop(m_State, 1);
				return;
			}

			m_Valid = true;
		}
		void ScriptComponent::ReCompileSource(std::string _path)
		{

		}
		void ScriptComponent::RecompileFromSource(std::string _source)
		{

		}
	}
}