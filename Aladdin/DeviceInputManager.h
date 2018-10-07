#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Debug.h"
#include "IKeyEventHandler.h"
#include "KeyHandler.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/*
Abstract class to define keyboard event handlers
*/
typedef IKeyEventHandler * LPKEYEVENTHANDLER;

class DeviceInputManager
{
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
public:
	void InitKeyboard(HWND hWnd, LPKEYEVENTHANDLER handler);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	int GetPressedKey();
	DeviceInputManager();
	~DeviceInputManager();
};

