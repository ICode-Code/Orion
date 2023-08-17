#ifndef OE1_CONTENT_BROWSER_LAYER_H_
#define OE1_CONTENT_BROWSER_LAYER_H_

#include "LayerBase.h"


namespace OE1Core
{
	class ContentBrowserLayer : public LayerBase
	{
	public:
		ContentBrowserLayer();
		~ContentBrowserLayer();

		virtual void Update() override;
		virtual void Render() override;
	};
}

#endif // !OE1_CONTENT_BROWSER_LAYER_H_
