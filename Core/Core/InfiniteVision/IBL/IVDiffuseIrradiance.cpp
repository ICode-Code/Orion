#include "IVDiffuseIrradiance.h"
#include "../GUI/Layer/LogLayer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVDiffuseIrradiance::IVDiffuseIrradiance()
		{
			m_Cube = new DS::Cube();
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
			m_ToIrradinceMap = ShaderManager::GetShader(ShaderID::TO_IRRADIANCEMAP);
			m_ToCubeMap = ShaderManager::GetShader(ShaderID::TO_CUBEMAP);
		}
		IVDiffuseIrradiance::~IVDiffuseIrradiance()
		{
			delete m_Cube;
		}
		bool IVDiffuseIrradiance::Exist(std::string _name)
		{
			return m_IrradianceMaps.find(_name) != m_IrradianceMaps.end();
		}
		std::string IVDiffuseIrradiance::RegisterHDRI(std::string _hdr_source, std::string _name)
		{
			QTextureHandle t_hdl(OE1Core::Loader::TextureLoader::OELoadHDRI(_hdr_source));
			
			std::string T_NAME = _name;

			if (T_NAME.empty())
				T_NAME = t_hdl.GetName();

			// Init Default
			m_IrradianceMaps.insert(std::make_pair(T_NAME, 0));
			m_CubeMaps.insert(std::make_pair(T_NAME, 0));

			CreateCubeMapStorage(T_NAME);
			ConvertHDRI(t_hdl.GetTextureID(), m_CubeMaps[T_NAME]);
			CreateIrradianceMap(T_NAME);

			return T_NAME;
		}
		GLuint IVDiffuseIrradiance::GetIrradianceMap(std::string _name)
		{
			if (Exist(_name))
				return m_IrradianceMaps[_name];

			LOG_WARRNING(LogLayer::Pipe("Unable to find Irradiance map name  '" + _name + "'. ", OELog::WARNING));
			return 0;
		}
		GLuint IVDiffuseIrradiance::GetCubeMap(std::string _name)
		{
			if (m_CubeMaps.find(_name) != m_CubeMaps.end())
				return m_CubeMaps[_name];

			LOG_WARRNING(LogLayer::Pipe("Unable to find cube map name  '" + _name + "'. ", OELog::WARNING));
			return 0;
		}

		void IVDiffuseIrradiance::CreateCubeMapStorage(std::string _name)
		{
			glGenTextures(1, &m_CubeMaps[_name]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMaps[_name]);

			for (int i = 0; i < 6; i++)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, m_CubeMapResolution, m_CubeMapResolution, 0, GL_RGBA, GL_FLOAT, nullptr);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		void IVDiffuseIrradiance::ConvertHDRI(GLuint _hdri_source, GLuint& _cube_map_dest)
		{
			glGenFramebuffers(1, &m_Framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			glViewport(0, 0, m_CubeMapResolution, m_CubeMapResolution);

			m_ToCubeMap->Attach();

			m_ToCubeMap->SetMat4("Projection", IBL_UTIL::Projection);
			m_ToCubeMap->Set1i("HDRI", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _hdri_source);

			for (int i = 0; i < 6; i++)
			{
				m_ToCubeMap->SetMat4("View", IBL_UTIL::View[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _cube_map_dest, 0);
				glClear(GL_COLOR_BUFFER_BIT);

				// Draw Cube
				DrawCube();
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &m_Framebuffer);

			// Wait for the GPU to finish executing the previous commands
			glFinish();
		}

		void IVDiffuseIrradiance::CreateIrradianceMap(std::string _name)
		{
			glGenTextures(1, &m_IrradianceMaps[_name]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_IrradianceMaps[_name]);

			for (int i = 0; i < 6; i++)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, m_IrradianceMapResolution, m_IrradianceMapResolution, 0, GL_RGBA, GL_FLOAT, nullptr);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGenFramebuffers(1, &m_Framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			glViewport(0, 0, m_IrradianceMapResolution, m_IrradianceMapResolution);

			m_ToIrradinceMap->Attach();
			m_ToIrradinceMap->SetMat4("Projection", IBL_UTIL::Projection);

			m_ToIrradinceMap->Set1i("CubeMap", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMaps[_name]);

			for (int i = 0; i < 6; i++)
			{
				m_ToIrradinceMap->SetMat4("View", IBL_UTIL::View[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_IrradianceMaps[_name], 0);
				glClear(GL_COLOR_BUFFER_BIT);

				DrawCube();
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &m_Framebuffer);
			// Wait for the GPU to finish executing the previous commands
			glFinish();
		}
		void IVDiffuseIrradiance::DrawCube()
		{
			glBindVertexArray(m_Cube->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
}