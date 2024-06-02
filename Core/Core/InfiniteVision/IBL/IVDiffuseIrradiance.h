#ifndef OE1_IV_DIFFUSE_IRRADIANCE_H_
#define OE1_IV_DIFFUSE_IRRADIANCE_H_

#include "../Core/DS/Cube/Cube.h"
#include "../Core/Texture/QTextureHandle.h"
#include "ShaderManager/ShaderManager.h"
#include "Loader/IVLoader.h"
#include "IBLUTIL.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVDiffuseIrradiance
		{
			friend class IVLightRoomManager;
		public:
			IVDiffuseIrradiance();
			~IVDiffuseIrradiance();

			bool Exist(std::string _name);
			std::string RegisterHDRI(std::string _hdr_source, std::string _name = "");
			GLuint GetIrradianceMap(std::string _name);
			GLuint GetCubeMap(std::string _name);

			

		private:
			GLsizei m_CubeMapResolution = 512;
			GLsizei m_IrradianceMapResolution = 32;
			GLuint m_Framebuffer = 0;

		private: // Shader
			Shader* m_ToCubeMap = nullptr;
			Shader* m_ToIrradinceMap = nullptr;

		private: // renderbale cube
			DS::Cube* m_Cube = nullptr;

		private: // Buffers
			std::unordered_map<std::string, GLuint> m_IrradianceMaps;
			std::unordered_map<std::string, GLuint> m_CubeMaps;


		protected: // Util functions
			void CreateCubeMapStorage(std::string _name);
			void ConvertHDRI(GLuint _hdri_source, GLuint& _cube_map_source);
			void CreateIrradianceMap(std::string _name);
			void DrawCube();
		};
	}
}

#endif // !OE1_IV_DIFFUSE_IRRADIANCE_H_
