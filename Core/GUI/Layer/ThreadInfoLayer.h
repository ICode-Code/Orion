#ifndef OE1_THREAD_INFO_LAYER_H_
#define OE1_THREAD_INFO_LAYER_H_

#include "LayerBase.h"

namespace OE1Core
{
	class ThreadInfoLayer : public LayerBase
	{
	public:
		ThreadInfoLayer();
		~ThreadInfoLayer();


		virtual void Update() override;
		virtual void Render() override;
		void IsLoading(bool _loading);

	protected:
		bool m_LoadingInProgress = false;
	};
}

#endif // !OE1_THREAD_INFO_LAYER_H_
