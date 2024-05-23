#ifndef OE1_ACTION_BUTTON_RENDER_MODE_GROUP_H_
#define OE1_ACTION_BUTTON_RENDER_MODE_GROUP_H_


#include "ActionButtonBase.h"
#include "../Core/Scene/SceneRenderMode.h"


namespace OE1Core
{
	class ActionButtonRenderModeGroup : public ActionButtonBase
	{
	public:
		ActionButtonRenderModeGroup();
		~ActionButtonRenderModeGroup();


		void Draw(RenderMode& _render_mode);

	protected:
		std::pair<RenderMode, VPNavButton*> m_LitPass;
		std::pair<RenderMode, VPNavButton*> m_MaterialPass;
		std::pair<RenderMode, VPNavButton*> m_WireFrame;

	protected:
		bool DrawButton(std::pair<RenderMode, VPNavButton*>& _button, RenderMode& _value);
		bool DrawButton_EXT(std::pair<RenderMode, VPNavButton*>& _button, RenderMode& _value);

	};
}

#endif // !OE1_ACTION_BUTTON_RENDER_MODE_GROUP_H_
