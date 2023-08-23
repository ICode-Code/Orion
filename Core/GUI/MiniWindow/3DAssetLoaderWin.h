#ifndef OE1_3D_ASSET_LOAD_WIN_H_
#define OE1_3D_ASSET_LOAD_WIN_H_



#include "BaseMiniWindw.h"
#include "Util/NameHandle.h"
#include "Util/LoadArgs.h"
#include "Geometry/GeometryLoader.h"
#include <glm/glm.hpp>


namespace OE1Core
{
	class Asset3DLoaderWin : public BaseMiniWindow
	{
	public:
		Asset3DLoaderWin();
		~Asset3DLoaderWin();

		virtual void Render() override;
		static void Open(std::string _asset_path);

	protected:
		inline static bool s_ShouldOpen = false;
		inline static std::string s_AssetPath;
		inline static Loader::LoadArgs s_LoadArgs;
		const inline static int s_DirectoryNameBufferSize = 256;
		// if we have separate directory
		inline static char s_DirectoryNameBuffer[s_DirectoryNameBufferSize];
		inline static bool s_CreateSeparateFolder = false;
	protected:
		virtual void Update() override;


	protected: // Util
		void CleanBuffer(char* _buffer, int _size);
	};
}

#endif // !OE1_3D_ASSET_LOAD_WIN_H_
