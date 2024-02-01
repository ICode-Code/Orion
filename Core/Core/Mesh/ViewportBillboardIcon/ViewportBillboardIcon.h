#ifndef OE1_VIEWPORT_BILLBOARD_ICON_H_
#define OE1_VIEWPORT_BILLBOARD_ICON_H_

#include "../../Texture/Texture.h"
#include "../../MeshCluster/BaseQuad.h"
#include "../../MeshCluster/ViewportBillboardInstancePkg.h"
#include "ViewportBillboardIconType.h"

#include "Log.h"

namespace OE1Core
{
	namespace Renderer { class IVViewportBillboardIconRenderer;  }
	class ViewportBillboardIcon
	{
		friend class Renderer::IVViewportBillboardIconRenderer;
	public:
		ViewportBillboardIcon(Texture* _texture);
		ViewportBillboardIcon(ViewportBillboardIcon& _other);
		~ViewportBillboardIcon();

		const Texture* GetTexture() const;
		const BaseQuad* GetBaseQuad() const;

		int GetInstanceCount() const;

		/// <summary>
		/// This will increase the instance count and return 
		/// the memory offset which can bes used as the insatnce id as well
		/// </summary>
		/// <returns></returns>
		int AddInstance(uint32_t _instanceID);
		/// <summary>
		/// reaturn weather the operation was succesffull or not
		/// %% Call this before deleting the entity %%
		/// </summary>
		/// <param name="_instance_id"></param>
		/// <returns></returns>
		bool PurgeInstance(uint32_t _instance_id, class Scene* _scene);


	private:
		std::vector<uint32_t> m_InstanceIDs;
		Texture* m_Texture = nullptr;
		BaseQuad* m_BaseQuad = nullptr;
		int m_InstanceCount = 0;
		GLuint m_InstanceBuffer = 0;
		int m_ActiveInstanceCount = 0;
		int m_InitialInstanceBufferSize = 2048;

	private:
		void Init();
	};
}

#endif // !OE1_VIEWPORT_BILLBOARD_ICON_H_
