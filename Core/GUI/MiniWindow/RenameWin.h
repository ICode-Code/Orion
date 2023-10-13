#ifndef OE1_RENAME_WIN_H_
#define OE1_RENAME_WIN_H_

#include "BaseMiniWindw.h"
#include "../../Core/Component/TagComponent/TagComponent.h"


namespace OE1Core
{
	class RenameWin : public BaseMiniWindow
	{
	public:
		RenameWin();
		~RenameWin();

		virtual void Render() override;
		static void Open(Component::TagComponent& _tag);
		static void Close();

	private:
		inline static bool s_ShouldOpen = false;
		virtual void Update() override;

	protected:
		inline static Component::TagComponent* s_ActiveTag = nullptr;
		inline static bool s_EmptyTextError = false;
		const inline static int s_NewNameBufferSize = 512;
		inline static char s_NewNameBuffer[s_NewNameBufferSize];
	};
}

#endif // !OE1_RENAME_WIN_H_
