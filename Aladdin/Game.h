#pragma once
#include <Windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "Util.h"
#include "SceneManager.h"
#include "DeviceInputManager.h"
#include "KeyHandler.h"

#define WIN32_LEAN_AND_MEAN
#define FRAME_RATE 30
//#define SCREEN_WIDTH 322
//#define SCREEN_HEIGHT 250
//#define SCREEN_WIDTH 966
//#define SCREEN_HEIGHT 750
#define SCREEN_WIDTH 660
#define SCREEN_HEIGHT 480

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Game
{
protected:
	// win32 attributes
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	UINT					m_Width;
	UINT					m_Height;
	std::string				m_AppTittle;
	DWORD					m_WndStyle;

	// directx attributes
	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice3D;

	// game scene
	SceneManager*			sceneManager;
public:
	Game(HINSTANCE hInstance);
	~Game(void);
public:
	// framework methods
	bool Init();
	int Run();
	void Update(float dt);
	void Render(float dt);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	// initialize win32 window
	bool InitWindow();

	// initialize direct3d
	bool InitDirect3D();

	void ProcessCollapsion(); // xử lý các va chạm

	void ProcessKeyboard(); // xử lý bàn phím
};