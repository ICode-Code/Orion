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
		float m_EntityMiniPopupMenuButtonWidth = 200.0f;
		std::string m_PopUpID = "";
		uint64_t m_OpenedPopupEntityID = 0;
		bool m_OpenEntityMiniPopupMenuPopup = false;
		void DrawEntityNode(Entity& _entity, ActiveEntity* _active_entity);

	private:
		void EntityMiniPopupMenu();
	};
}

#endif // !OE1_SCENE_HIERARCHY_LAYER_H_
