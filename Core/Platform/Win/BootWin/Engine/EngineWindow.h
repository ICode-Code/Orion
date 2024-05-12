#ifndef OE1_ENGINE_WINDOW_H_
#define OE1_ENGINE_WINDOW_H_

#include "../../BaseWindow.h"


namespace OE1Core
{
	class EngineWindow : public BaseWindow
	{
	public:
		EngineWindow(SDL_Event* _event);
		~EngineWindow();

		void SetCloseTrigger(bool* _val);
		virtual void OnEvent(OECore::IEvent& e) override;

		/// <summary>
		/// Whene every you want to make sure the event is called inside this window call this
		/// it will restet it store the it user data in the call back function
		/// </summary>
		virtual void ResetCallbacks() override;

	protected:
		virtual bool HandleWindowCloseEvent(OECore::WindowCloseEvent& e) override;
		virtual bool HandleWindowResizeEvent(OECore::WindowResizeEvent& e) override;
		virtual bool HandleWindowMax(OECore::WindowMaximizedEvent& e) override;
		virtual bool HandleWindowMin(OECore::WindowMinimizedEvent& e) override;
		virtual bool HandleApplicationKeyInput(OECore::KeyPressedEvent& e) override;

	protected:
		bool* m_CloseTrigger = nullptr;
	};
}


#endif // !OE1_ENGINE_WINDOW_H_
