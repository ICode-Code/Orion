#ifndef OE_LAYER_BASE_H_
#define OE_LAYER_BASE_H_

#include "../../Core/ActiveEntity/ActiveEntity.h"
#include "../../Core/Command/ExecutionHandler.h"
#include "../../AssetManager/AssetManager.h"
#include "../../Platform/Win/WindowManager.h"
#include "../Native/WindowFileDialog.h"
#include "../../Core/Command/Commnad.h"
#include "../MiniWindow/IMiniWin.h"
#include <Gui.h>

namespace OE1Core
{
	class LayerBase
	{
	public:
		LayerBase()
		{ }
		virtual ~LayerBase()
		{ }

		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}


#endif // !OE_LAYER_BASE_H_
