#ifndef OE1_MAIN_VIEWPORT_H_
#define OE1_MAIN_VIEWPORT_H_

#include "../BaseViewport.h"

namespace OE1Core
{
	class MainViewport : public BaseViewport
	{
	public:
		MainViewport();
		~MainViewport();


		void Update() override;
		void Render() override;

	protected:
		void HandlePayloadPackage();
		void HandleClickOverViewport();
	};
}

#endif // !OE1_MAIN_VIEWPORT_H_
