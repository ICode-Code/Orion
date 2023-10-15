#ifndef OE1_IV2D_TEXTURE_ARRAY_EXTRACTOR_FRAMEBUFFER_H_
#define OE1_IV2D_TEXTURE_ARRAY_EXTRACTOR_FRAMEBUFFER_H_


#include "IVForwardBaseFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{

		struct MatPreviewTexture
		{
			std::pair<GLuint, int> Color;
			std::pair<GLuint, int> Normal;
			std::pair<GLuint, int> Metal;
			std::pair<GLuint, int> Roughness;
			std::pair<GLuint, int> MetalRougness;
			std::pair<GLuint, int> Emission;
			std::pair<GLuint, int> Alpha;
			std::pair<GLuint, int> AO;
		};
		struct CheckMatPreviewTexture
		{
			bool HasColor			= false;
			bool HasNormal			= false;
			bool HasMetal			= false;
			bool HasRoughness		= false;
			bool HasMetalRougness	= false;
			bool HasEmission		= false;
			bool HasAlpha			= false;
			bool HasAO				= false;
		};

		class IV2DTextureArrayExtractorFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IV2DTextureArrayExtractorFramebuffer(const int _width, const int _height, CheckMatPreviewTexture _texture);
			IV2DTextureArrayExtractorFramebuffer(const int _res[2], CheckMatPreviewTexture _texture);
			virtual ~IV2DTextureArrayExtractorFramebuffer();


			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _index) override;
			inline MatPreviewTexture& GetTextureAttachment() { return m_Textures; }
			inline CheckMatPreviewTexture& GetCheckMaterialTextureX() { return m_HasTextureX; }


		protected:
			MatPreviewTexture m_Textures;
			CheckMatPreviewTexture m_HasTextureX;
			GLuint m_Depth;
			int m_DrawBuffers;

		private: // util
			void SetBufferAttachment() override;
			void FilterTextureIdx();

		};
	}
}

#endif // !OE1_IV2D_TEXTURE_ARRAY_EXTRACTOR_FRAMEBUFFER_H_
