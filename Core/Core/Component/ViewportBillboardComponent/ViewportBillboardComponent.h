#ifndef OE1_VIEWPORT_BILLBOARD_COMPONENT_H_
#define OE1_VIEWPORT_BILLBOARD_COMPONENT_H_

#include "../../MeshCluster/ViewportBillboardInstancePkg.h"
#include "../../Mesh/ViewportBillboardIcon/ViewportBillboardIconType.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace OE1Core
{
	class ViewportBillboardIcon;
	namespace Component
	{
		class ViewportBillboardComponent
		{
		public:
			ViewportBillboardComponent() = default;
			ViewportBillboardComponent(ViewportBillboardIcon* _sprite, uint32_t _entity_id, ViewportIconBillboardType _type);
			ViewportBillboardComponent(ViewportBillboardComponent& other, uint32_t _entity_id);
			~ViewportBillboardComponent();

			void UpdateOffset(const GLintptr _offset);
			void Update(glm::mat4& _transform, glm::mat4& _camera_view);
			ViewportIconBillboardType GetType()  const;
			//const char* GetSpriteName() const;
			uint32_t GetEntityID() const;
			GLuint GetInstanceBufferID() const;
			GLintptr GetMemoryOffset() const;
			//GLuint GetTextureID() const;
			ViewportBillboardInstancePkg GetInstanceData() const;

			void SetEntityID(uint32_t _id);
			bool IsReady() const;

			void SetScale(float _scale);
			float GetScale() const;



		protected:
			uint32_t m_EntityID = -1;
			GLuint m_InstanceBufferID = -1;
			GLintptr m_MemoryOffset = -1;
			ViewportBillboardInstancePkg m_InstanceData;
			ViewportIconBillboardType m_Type;
			bool m_Ready = false;
			float m_Scale = 0.05f;
			class ViewportBillboardIcon* m_Sprite = nullptr;

		private: // Utitlity function
			glm::mat4 FaceCamera(glm::mat4 _transform);


		};
	}
}
#endif // !OE1_VIEWPORT_BILLBOARD_COMPONENT_H_
