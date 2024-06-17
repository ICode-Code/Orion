#ifndef OE1_SOURCE_EDITOR_MANAGER_H_
#define OE1_SOURCE_EDITOR_MANAGER_H_


#include "LuaSourceEditor/LuaSourceEditor.h"
#include "../Core/Component/ScriptComponent/ScriptComponent.h"
#include <unordered_map>
#include <functional>


namespace OE1Core
{
	class SourceEditorManager
	{
	public:
		SourceEditorManager();
		~SourceEditorManager();

		static void Render();
		static void Update();

		static void Register(std::string _name, Component::ScriptComponent& _script);
		static void Purge(std::string _name);

	private:
		inline static std::unordered_map<std::string, LuaSourceEditor*> s_SourceEditors;
	};
}


#endif // !OE1_SOURCE_EDITOR_MANAGER_H_
