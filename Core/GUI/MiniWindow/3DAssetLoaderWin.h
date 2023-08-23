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
		virtual void Update() override;
	};
}

#endif // !OE1_3D_ASSET_LOAD_WIN_H_
