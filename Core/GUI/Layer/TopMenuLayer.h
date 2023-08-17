#ifndef OE1_TOP_MENU_LAYER_H_
#define OE1_TOP_MENU_LAYER_H_

#include "LayerBase.h"


namespace OE1Core
{
	class TopMenuLayer : public LayerBase
	{
	public:
		TopMenuLayer();
		~TopMenuLayer();


		virtual void Update() override;
		virtual void Render() override;

	protected:
		void File();
		void Edit();
		void Window();
		void Tools();
		void Debug();
		void Help();
	};
}

#endif // !OE1_TOP_MENU_LAYER_H_
