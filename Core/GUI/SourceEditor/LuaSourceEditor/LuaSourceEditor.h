#ifndef OE1_LUA_SOURCE_EDITOR_H_
#define OE1_LUA_SOURCE_EDITOR_H_

#include "../Core/Component/ScriptComponent/ScriptComponent.h"

#include "../../CustomFrame/CustomFrame.h"
#include <vector>
#include <Gui.h>

namespace OE1Core
{
	typedef std::function<void(std::string)> PURGE_CALLBACK;
	class LuaSourceEditor
	{
		friend class SourceEditorManager;
	public:
		LuaSourceEditor(Component::ScriptComponent* _script);
		~LuaSourceEditor();

		void SetPurgCallback(const PURGE_CALLBACK& _cabback);
		void Render();
		void Update();
		bool m_ShouldOpen = false;

	private:
		ImGuiTreeNodeFlags m_Flag = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanFullWidth;
		float m_Indent = 16.0f;
		Component::ScriptComponent* m_ScriptComponent = nullptr;
		PURGE_CALLBACK m_PurgCallback;
		std::string m_SourceBuffer;
		char m_TextBuffer[2048 * 16] = { 0 };
	private: // style
		void PushStyle();
		void PopStyle();
	};
}



#endif // !OE1_LUA_SOURCE_EDITOR_H_
