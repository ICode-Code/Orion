#ifndef OE1_PROJECT_CREATOR_WIN_H_
#define OE1_PROJECT_CREATOR_WIN_H_


#include "PreDef.h"
#include "BaseMiniWindw.h"
#include "glm/glm.hpp"


namespace OE1Core
{
	class ProjectCreatorWin : public BaseMiniWindow 
	{
	public:
		ProjectCreatorWin();
		~ProjectCreatorWin();

		virtual void Render() override;
		virtual void Update() override;
		static void Open();

	protected:
		inline static bool s_ShouldOpen = false;
		const inline static int s_ProjectNameBufferSize = 256;
		inline static char s_ProjectNameBuffer[s_ProjectNameBufferSize];
		ImTextureID m_EmptyProjectIcon = 0;
		ImTextureID m_PBRTestProjectIcon = 0;
		ImTextureID m_FPSTestProjectIcon = 0;


	protected: // Util
		//void CleanBuffer(char* _buffer, int _size);
	};
}

#endif // !OE1_PROJECT_CREATOR_WIN_H_
