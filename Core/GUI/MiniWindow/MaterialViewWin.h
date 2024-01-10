#ifndef OE1_MATERIAL_VIEW_WIN_H_
#define OE1_MATERIAL_VIEW_WIN_H_


#include "BaseMiniWindw.h"
#include "MinTextureFilterWin.h"
#include "../Core/InfiniteVision/DisplayCanavs/IV2DTextureArrayExtractorFramebuffer.h"

namespace OE1Core
{

	// The goal of this stuct is when we click newtexture in
	// in the mini material view and it list possible texture
	// and when we click one of them it will pop another mini window
	// which contain the all texture loaded to the engine
	// inorder and when we select the texture it store it in temp memory
	// and this temp memory need to read by the texture slote which I originaly clicked
	// in order to remember which texture I click I enable this flag
	struct MaterialTextureIssueFlag
	{
		bool ColorMapIssued				= false;
		bool NormalMapIssued			= false;
		bool MetalMapIssued				= false;
		bool RoughnessMapIssued			= false;
		bool MetalRougnessMapIssued		= false;
		bool EmissionMapIssued			= false;
		bool AlphaMapIssued				= false;
		bool AOMapIssued				= false;

		// After enabiling flags rest
		void Reset()
		{
			ColorMapIssued			= false;
			NormalMapIssued			= false;
			MetalMapIssued			= false;
			RoughnessMapIssued		= false;
			MetalRougnessMapIssued	= false;
			EmissionMapIssued		= false;
			AlphaMapIssued			= false;
			AOMapIssued				= false;
		}
	};


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
		MaterialTextureIssueFlag m_TextureIssueFlag;

		/// <summary>
		///  This is where the texture will be stored after I clicked it, the pointer to the texture anyway
		/// </summary>
		OE1Core::MaterialType m_TempTexType;
		OE1Core::Texture* m_TempTextureMemPtr = nullptr;
		MasterMaterial* m_Material = nullptr;
		std::string m_WinName = "";
		bool m_Open = false;
		Renderer::IV2DTextureArrayExtractorFramebuffer* m_Framebuffer = nullptr;
		ImVec2 m_TextureSize;
		ImVec2 m_TextureSizeZoom;
		 


	protected: // Util
		void TexturePreviewPainter(GLuint _index, std::string _name, MaterialType _type, bool _has_texture);
		void AnalizeTextureSelectionFlag(OE1Core::Texture* _texture, OE1Core::MaterialType _type);
		void TextureListButton(std::string _name, MaterialType _type, bool _has_texture, ImVec2 _size, bool& _issue_flag);
		bool ImageWithName(GLuint _image, std::string _name, float _size);
		void PrepareMaterialView();
		void PushTextureViewStyle();
		void PopTextureViewStyle();
		void PrintTextureName(const char* _name);
		void PaintTexture(GLuint& _texture, const char* _name, const MaterialType _type);

		// call this function when ever you update texture or add a new one
		void PushUpdateViewCommand();
		
	};
}

#endif // !OE1_MATERIAL_VIEW_WIN_H_
