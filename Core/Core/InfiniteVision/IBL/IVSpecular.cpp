#include "IVSpecular.h"
#include "../GUI/Layer/LogLayer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVSpecular::IVSpecular()
		{
			m_Quad = new DS::Quad();
			m_Cube = new DS::Cube();

			m_MipLevel = 6;
			m_PreBRDF = ShaderManager::GetShader(ShaderID::PRE_BRDF_MAP);
			m_PrefilteredMap = ShaderManager::GetShader(ShaderID::PREFILTERD_ENV_MAP);

			m_PrefilteredMapResolution = 128;

			// create lut / since it does not depend on env maps
			//CreateLUT();
			//WriteLUT();

		}

		IVSpecular::~IVSpecular()
		{
			delete m_Quad;
			delete m_Cube;
		}

		GLuint IVSpecular::GetLUT() { return m_Lut; }
		GLuint IVSpecular::GetPrefilteredReflectionMap(std::string _name)
		{
			if (m_PrefilteredReflectionMaps.find(_name) == m_PrefilteredReflectionMaps.end())
				return 0;

			return m_PrefilteredReflectionMaps[_name];
		}
		GLuint IVSpecular::GetPrefilteredPreviewReflectionMap(std::string _name)
		{
			if (m_MapPreviews.find(_name) == m_MapPreviews.end())
				return 0;

			return m_MapPreviews[_name];
		}

		void IVSpecular::RegisterEnviromnetMap(GLuint _env_map, std::string _name)
		{
			if (m_EnviromentMaps.find(_name) != m_EnviromentMaps.end())
			{
				LOG_WARRNING(LogLayer::Pipe("Failed to register Enviroment map name already exist '" + _name + "'", OELog::WARNING));
				return;
			}

			m_EnviromentMaps.insert(std::make_pair(_name, _env_map));
			m_MapPreviews.insert(std::make_pair(_name, 0));
			CreateCubeMapStorage(_name);
			WritePrefilteredMap(_name);

			// Write Preview
			Renderer::IVHDRPreviewRenderer::Render(m_PrefilteredReflectionMaps[_name], m_MapPreviews[_name], SceneManager::GetActiveScene());
		}

		void IVSpecular::CreateCubeMapStorage(std::string _name)
		{
			glGenTextures(1, &m_PrefilteredReflectionMaps[_name]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_PrefilteredReflectionMaps[_name]);

			for (int i = 0; i < 6; i++)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, m_PrefilteredMapResolution, m_PrefilteredMapResolution, 0, GL_RGBA, GL_FLOAT, NULL);


			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}
		void IVSpecular::WritePrefilteredMap(std::string _name)
		{
			glGenFramebuffers(1, &m_Framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			m_PrefilteredMap->Attach();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnviromentMaps[_name]);

			m_PrefilteredMap->SetMat4("Projection", IBL_UTIL::Projection);

			for (int i = 0; i < m_MipLevel; i++)
			{
				int _width = (int)(m_PrefilteredMapResolution * std::pow(0.5f, (double)i));
				int _height = (int)(m_PrefilteredMapResolution * std::pow(0.5f, (double)i));

				glViewport(0, 0, _width, _height);
				float roughness = (float)i / (float)(m_MipLevel - 1);

				m_PrefilteredMap->Set1f("Roughness", roughness);

				for (int k = 0; k < 6; k++)
				{
					m_PrefilteredMap->SetMat4("View", IBL_UTIL::View[k]);
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + k, m_PrefilteredReflectionMaps[_name], i);
					glClear(GL_COLOR_BUFFER_BIT);

					DrawCube(); 
				}
			}
			m_PrefilteredMap->Detach();
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &m_Framebuffer);
		}

		void IVSpecular::CreateLUT()
		{
			glGenTextures(1, &m_Lut);
			glBindTexture(GL_TEXTURE_2D, m_Lut);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, m_BRDFResolution, m_BRDFResolution, 0, GL_RG, GL_FLOAT, 0);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		void IVSpecular::WriteLUT()
		{
			glGenFramebuffers(1, &m_Framebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Lut, 0);
			
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
				printf("Error: Framebuffer is not complete!\n");
			}
			glViewport(0, 0, 512, 512);
			glClear(GL_COLOR_BUFFER_BIT);

			m_PreBRDF->Attach();

			

			DrawQuad();

			m_PreBRDF->Detach();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, &m_Framebuffer);

			//glFlush();
			glFinish();

		}

		void IVSpecular::DrawCube()
		{
			glBindVertexArray(m_Cube->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
		void IVSpecular::DrawQuad()
		{
			glBindVertexArray(m_Quad->GetVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}