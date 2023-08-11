#include "Platform/Win/WindowManager.h"
#include <iostream>

#include <Log.h>

#include <thread>

int main(int argc, char** argv)
{
	OE1Core::Log::Init();
	OE1Core::WindowManager window_manager;

	OE1Core::Window* _win1 = OE1Core::WindowManager::RegisterWindow("Window 1", 900, 300);
	OE1Core::Window* _win2 = OE1Core::WindowManager::RegisterWindow("Window 2");


    

    std::thread thread2([&]() {
        _win2->EnableWin();

        _win2->SetClearColor({0.1f, 0.5f, 0.9f, 1.0f});

        while (_win1) {
            _win2->CleanDefaultBuffer();


            _win2->SwapZDoubleBuffer();
        }
        });


    _win1->EnableWin();

    while (_win1) {
        _win1->CleanDefaultBuffer();

        _win1->SwapZDoubleBuffer();
    }

    

    thread2.join();
	

	return 0;
}