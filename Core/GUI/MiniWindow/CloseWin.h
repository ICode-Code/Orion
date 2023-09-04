#ifndef OE1_CLOSE_WIN_H_
#define OE1_CLOSE_WIN_H_



#include "BaseMiniWindw.h"


namespace OE1Core
{
	class CloseWin : public BaseMiniWindow
	{
	public:
		CloseWin();
		~CloseWin();

		virtual void Render() override;
		inline static bool s_ShouldOpen = false;
	private:
		virtual void Update() override;


	private:
		ImTextureID m_LogoutTexture = 0;
	};
}

#endif // !OE1_CLOSE_WIN_H_
