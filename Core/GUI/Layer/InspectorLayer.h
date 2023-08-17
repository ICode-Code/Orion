#ifndef OE1_INSPECTOR_H_
#define OE1_INSPECTOR_H_


#include "LayerBase.h"

namespace OE1Core
{
	class InspectorLayer : public LayerBase
	{
	public:
		InspectorLayer();
		~InspectorLayer();


		virtual void Update() override;
		virtual void Render() override;
	};
}

#endif // !OE1_INSPECTOR_H_
