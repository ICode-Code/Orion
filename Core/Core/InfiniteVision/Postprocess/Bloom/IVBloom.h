#ifndef OE1_IV_BLOOM_H_
#define OE1_IV_BLOOM_H_

#include "ShaderManager/ShaderManager.h"
#include "../Core/DS/Quad/Quad.h"

namespace OE1Core
{
	class Scene;
	namespace Component 
	{ 
		class CameraComponent; 
	}
	namespace Renderer
	{
		class IVBloom
		{
		friend class Component::CameraComponent;
		friend class PreferenceWin;
		public:
			IVBloom();
			~IVBloom();


			void ApplyBloom(class Component::CameraComponent* _camera);


		private:
			Shader* m_UpSample = nullptr;
			Shader* m_DownSample = nullptr;
			DS::Quad* m_Quad = nullptr;
			Scene* m_Scene = nullptr;


		protected:
			void DrawQuad();
			void DownSamplePass(class Component::CameraComponent* _camera);
			void UpSamplePass(class Component::CameraComponent* _camera);

		};
	}
}


#endif // !OE1_IV_BLOOM_H_
