#ifndef OE1_SCENE_HIERARCHY_LAYER_H_
#define OE1_SCENE_HIERARCHY_LAYER_H_

#include "LayerBase.h"


namespace OE1Core
{
	class SceneHierarchyLayer : public LayerBase
	{
	public:
		SceneHierarchyLayer();
		~SceneHierarchyLayer();


		virtual void Update() override;
		virtual void Render() override;


	protected:
		ImGuiTreeNodeFlags m_NodeFlags;
		void DrawEntityNode(Entity& _entity, ActiveEntity* _active_entity);
	};
}

#endif // !OE1_SCENE_HIERARCHY_LAYER_H_
