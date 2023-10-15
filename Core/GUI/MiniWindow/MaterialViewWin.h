#ifndef OE1_MATERIAL_VIEW_WIN_H_
#define OE1_MATERIAL_VIEW_WIN_H_


#include "BaseMiniWindw.h"
#include "../Core/InfiniteVision/DisplayCanavs/IV2DTextureArrayExtractorFramebuffer.h"

namespace OE1Core
{
	class MaterialViewWin : public BaseMiniWindow
	{
		friend class ExecutionHandler;
	public:
		MaterialViewWin(MasterMaterial* _material);
		~MaterialViewWin();

		virtual void Render() override;
		virtual void Update() override;
		inline MasterMaterial* GetMaterial() { return m_Material; }
		inline bool IsOpen() const { return m_Open; }

	protected: // data
		MasterMaterial* m_Material = nullptr;
		std::string m_WinName = "";
		bool m_Open = false;
		Renderer::IV2DTextureArrayExtractorFramebuffer* m_Framebuffer = nullptr;



	protected: // Util
		void PrepareMaterialView();
		void PushTextureViewStyle();
		void PopTextureViewStyle();
		void PrintTextureName(const char* _name);
		
	};
}

#endif // !OE1_MATERIAL_VIEW_WIN_H_
