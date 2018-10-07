#pragma once
#include "Aladdin.h"
#include "Camera.h"
#include "Background.h"
#include "DeviceInputManager.h"

class SceneManager
{
protected:
	Aladdin* aladdin;
	Camera* camera;
	D3DXVECTOR3 zoom;
	vector<Background*> scenes;
	ViewPort* viewPort;
	LPDIRECT3DDEVICE9 d3ddev;
	DeviceInputManager*		m_pDIManager;
	IKeyEventHandler*		keyHandler;
public:
	SceneManager(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev, UINT screenWidth, UINT screenHeight);
	~SceneManager();

	void Load(LPDIRECT3DDEVICE9 d3ddev);
	void Draw(float dt);
	void Update(float dt);

	void ProcessKeyboard();
private:
	void SetViewPort();
};

