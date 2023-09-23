#ifndef OE1_VP_ACTION_BUTTON_H_
#define OE1_VP_ACTION_BUTTON_H_

#include <string>
#include <Gui.h>

namespace OE1Core
{
	class VPNavButton
	{
	public:
		VPNavButton(const char* _icon);

		bool Draw();

	protected:
		const char* m_Icon;
	};
}

#endif // !OE1_VP_ACTION_BUTTON_H_
