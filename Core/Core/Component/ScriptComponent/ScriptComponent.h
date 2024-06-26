#ifndef OE1_SCRIPT_COMPONENT_H_
#define OE1_SCRIPT_COMPONENT_H_

#include <Lua/lua.hpp>
#include <string>
#include <Log.h>


#include "../Core/RTS/RTSInitializer.h"

namespace OE1Core
{
	class LuaSourceEditor;
	namespace Component
	{
		class ScriptComponent
		{
			friend LuaSourceEditor;
			friend class InspectorComponent;
		public:
			ScriptComponent(std::string _name);
			ScriptComponent(const ScriptComponent& _other);
			~ScriptComponent();

			void OnInit();
			void OnUpdate();
			void OnEnbale();
			void OnDisable();

			void OnInit_D();
			void OnUpdate_D();
			void OnEnbale_D();
			void OnDisable_D();

			void Enable(bool _val);

			bool IsActive();

			/// <summary>
			/// Recomplie source adter user code change
			/// </summary>
			void ReCompileSource();

			// remopile and replace with this new source path
			void ReCompileSource(std::string _path);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="_source"></param>
			void RecompileFromSource(std::string _source);
			lua_State* GetState();

		private:
			lua_State* m_State = nullptr;
			bool m_IsEnable = false;
			std::string m_SourcePath = "-##-";
			std::string m_Source = "--";
			std::string m_Name = "-##-";
			bool m_Valid = false;
		};
	}
}

#endif // !OE1_SCRIPT_COMPONENT_H_
