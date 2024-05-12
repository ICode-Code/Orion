#ifndef OE1_GENESIS_WINDOW_H_
#define OE1_GENESIS_WINDOW_H_


#include "../../BaseWindow.h"


namespace OE1Core
{
	class GenesisWindow : public BaseWindow
	{
	public:
		GenesisWindow(SDL_Event* _event, SDL_GLContext _Context = nullptr);
		~GenesisWindow();

		virtual void ResetCallbacks() override;
		virtual void OnEvent(OECore::IEvent& e) override;

	protected:
		virtual bool HandleWindowCloseEvent(OECore::WindowCloseEvent& e) override;
		virtual bool HandleWindowResizeEvent(OECore::WindowResizeEvent& e) override;
		virtual bool HandleWindowMax(OECore::WindowMaximizedEvent& e) override;
		virtual bool HandleWindowMin(OECore::WindowMinimizedEvent& e) override;
		virtual bool HandleApplicationKeyInput(OECore::KeyPressedEvent& e) override;
	};
}

#endif // !OE1_GENESIS_WINDOW_H_
