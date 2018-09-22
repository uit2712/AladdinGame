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

}

bool Game::Init()
{
	if (!InitWindow())
		return false;

	if (!InitDirect3D())
		return false;

	//sceneManager = new SceneManager(m_pDevice3D, m_hInstance, m_hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

int Game::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	DWORD frame_start = GetTickCount();;
	DWORD tick_per_frame = 1000 / FRAME_RATE;

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD now = GetTickCount();
			unsigned int dt = now - frame_start;
			if (dt >= tick_per_frame)
			{
				frame_start = now;
				// render
				Render(0.0f);

				// update
				Update(0.0f);
			}
		}
	}

	return static_cast<int>(msg.wParam);
}

void Game::End()
{
	//Memory::SafeDelete(sceneManager);
	Memory::SafeRelease(m_pDevice3D);
	Memory::SafeRelease(m_pD3D);
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
		//sceneManager->Draw(dt);
		//sceneManager->Update(dt);

		m_pDevice3D->EndScene();
	}

	m_pDevice3D->Present(NULL, NULL, NULL, NULL);
}

void Game::Render(float dt)
{
	ProcessCollapsion();
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
		End();
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}