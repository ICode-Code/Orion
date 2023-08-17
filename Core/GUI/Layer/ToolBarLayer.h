#ifndef OE1_TOOL_BAR_H_
#define OE1_TOOL_BAR_H_


#include "LayerBase.h"


namespace OE1Core
{
	class ToolBarLayer : public LayerBase
	{
	public:
		ToolBarLayer();
		~ToolBarLayer();


		virtual void Update() override;
		virtual void Render() override;
	};
}

#endif // !OE1_TOOL_BAR_H_
