#include "Game.h"

namespace
{
	// used to forward msgs to user defined proc function
	Game* g_pGame = nullptr;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pGame) return g_pGame->MsgProc(hWnd, msg, wParam, lParam);
	else return DefWindowProc(hWnd, msg, wParam, lParam);
}

Game::Game(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	m_hWnd = NULL;
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
	m_AppTittle = "Aladdin Game :D";
	m_WndStyle = WS_OVERLAPPEDWINDOW;

	g_pGame = this;
	m_pD3D = nullptr;
	m_pDevice3D = nullptr;
}

Game::~Game(void)
{
	if (sceneManager != NULL)
	{
		delete sceneManager;
		sceneManager = NULL;
	}

	if (m_pDevice3D != NULL)
	{
		m_pDevice3D->Release();
		m_pDevice3D = NULL;
	}

	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

bool Game::Init()
{
	if (!InitWindow())
		return false;

	if (!InitDirect3D())
		return false;

	sceneManager = new SceneManager(m_hWnd, m_pDevice3D, SCREEN_WIDTH, SCREEN_HEIGHT);
	sceneManager->Load(m_pDevice3D);

	return true;
}

int Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			sceneManager->ProcessKeyboard();

			Update(dt);
			Render(dt);
		}
		else Sleep(tickPerFrame - dt);
	}

	return 1;
}

bool Game::InitWindow()
{
#pragma region create and register window classex
	WNDCLASSEX wce;
	ZeroMemory(&wce, sizeof(WNDCLASSEX));

	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.cbSize = sizeof(WNDCLASSEX);
	wce.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wce.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wce.hInstance = m_hInstance;
	wce.lpfnWndProc = MainWndProc;
	wce.lpszClassName = "WNDCLASS1";
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wce))
	{
		OutputDebugString("\nFAILED TO CREATE WINDOW CLASS\n");
		return false;
	}
#pragma endregion

	RECT r = { 0, 0, m_Width, m_Height };
	AdjustWindowRect(&r, m_WndStyle, FALSE);
	UINT width = r.right - r.left;
	UINT height = r.bottom - r.top;

	UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	m_hWnd = CreateWindow("WNDCLASS1",
		m_AppTittle.c_str(),
		m_WndStyle, x, y,
		m_Width, m_Height,
		NULL, NULL,
		m_hInstance, NULL);

	if (!m_hWnd)
	{
		OutputDebugString("\nFAILED TO CREATE WINDOW\n");
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);

	return true;
}

bool Game::InitDirect3D()
{
	// create Direct3D
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D)
		return false;

	D3DPRESENT_PARAMETERS m_D3DPP;
	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.hDeviceWindow = m_hWnd;
	m_D3DPP.Windowed = TRUE;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&m_D3DPP, &m_pDevice3D);

	if (!m_pDevice3D)
		return false;

	return true;
}

void Game::Update(float dt)
{
	m_pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (m_pDevice3D->BeginScene())
	{
		sceneManager->Draw(dt);
		sceneManager->Update(dt);

		m_pDevice3D->EndScene();
	}

	m_pDevice3D->Present(NULL, NULL, NULL, NULL);
}

void Game::Render(float dt)
{
	ProcessCollapsion();
}

void Game::ProcessKeyboard()
{
	
	// xử lý phím và thay đổi trạng thái của aladdin
	
}

void Game::ProcessCollapsion()
{
	//sceneManager->ProcessCollapsion();
}

LRESULT Game::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}