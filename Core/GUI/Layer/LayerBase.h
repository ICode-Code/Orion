#ifndef OE_LAYER_BASE_H_
#define OE_LAYER_BASE_H_

#include <Gui.h>

namespace OE1Core
{
	class LayerBase
	{
	public:
		LayerBase()
		{ }
		~LayerBase()
		{ }

		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}


#endif // !OE_LAYER_BASE_H_
