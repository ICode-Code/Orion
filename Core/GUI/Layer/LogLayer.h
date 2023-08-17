#ifndef OE1_LOG_LAYER_H_
#define OE1_LOG_LAYER_H_


#include "LayerBase.h"


namespace OE1Core
{
	class LogLayer : public LayerBase
	{
	public:
		LogLayer();
		~LogLayer();

		virtual void Update() override;
		virtual void Render() override;
	};
}


#endif // !OE1_LOG_LAYEr_H_
