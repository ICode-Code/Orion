#ifndef OE1_PREFERENCE_WIN_H_
#define OE1_PREFERENCE_WIN_H_

#include "BaseMiniWindw.h"

namespace OE1Core
{
	class PreferenceWin : public BaseMiniWindow
	{
	public:
		PreferenceWin();
		~PreferenceWin();
		virtual void Render() override;
		inline static bool s_ShouldOpen = false;
	private:
		virtual void Update() override;
		class Scene* m_Scene = nullptr;

	};
}


#endif // !OE1_PREFERENCE_WIN_H_
