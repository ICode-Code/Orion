#ifndef OE1_IV_SPECULAR_H_
#define OE1_IV_SPECULAR_H_


#include "../Core/DS/Cube/Cube.h"
#include "../Core/DS/Quad/Quad.h"
#include "ShaderManager/ShaderManager.h"
#include "IBLUTIL.h"


namespace OE1Core
{
	class PreferenceWin;
	namespace Renderer
	{
		class IVSpecular
		{
			friend class IVLightRoomManager;
			friend class PreferenceWin;
		public:
			IVSpecular();
			~IVSpecular();

			void RegisterEnviromnetMap(GLuint _env_map, std::string _name);
			GLuint GetLUT();
			GLuint GetPrefilteredReflectionMap(std::string _name);



		private: 
			GLuint m_Framebuffer;
			GLuint m_Lut;
			int m_MipLevel = 20;
			GLsizei m_PrefilteredMapResolution = 512;
			GLsizei m_BRDFResolution = 512;

		private: // Shader
			Shader* m_PrefilteredMap = nullptr;
			Shader* m_PreBRDF = nullptr;

		private: // Renderable
			DS::Quad* m_Quad = nullptr;
			DS::Cube* m_Cube = nullptr;


		private: // Buffers
			std::unordered_map<std::string, GLuint> m_EnviromentMaps;
			std::unordered_map<std::string, GLuint> m_PrefilteredReflectionMaps;
			std::unordered_map<std::string, GLuint> m_MapPreviews;

		private: // Util
			void CreateCubeMapStorage(std::string _name);
			void WritePrefilteredMap(std::string _name);
			void CreateLUT();
			void WriteLUT();
			void DrawCube();
			void DrawQuad();
		};
	}
}


#endif // !OE1_IV_SPECULAR_H_
