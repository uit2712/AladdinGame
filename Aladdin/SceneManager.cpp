#include "SceneManager.h"



SceneManager::SceneManager(HWND hWnd, LPDIRECT3DDEVICE9 d3ddev, UINT screenWidth, UINT screenHeight)
{
	zoom = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	this->d3ddev = d3ddev;
	viewPort = new ViewPort(0, 450, screenWidth / zoom.x, screenHeight / zoom.y);
	aladdin = new Aladdin(D3DXVECTOR2(20, 530));
	camera = new Camera(screenWidth, screenHeight, 0.0f, zoom);
	scenes.push_back(new Background(GameObjectTypes::Map1, MAP1_PATH, viewPort));

	keyHandler = new KeyHandler();
	m_pDIManager = new DeviceInputManager();
	m_pDIManager->InitKeyboard(hWnd, keyHandler);
}


SceneManager::~SceneManager()
{
	if (aladdin != NULL)
	{
		delete aladdin;
		aladdin = NULL;
	}
	if (camera != NULL)
	{
		delete camera;
		camera = NULL;
	}

	if (scenes.size() > 0)
	{
		for (int i = scenes.size() - 1; i >= 0; i--)
		{
			delete scenes[i];
			scenes[i] = NULL;
		}
	}

	if (m_pDIManager != NULL)
	{
		delete m_pDIManager;
		m_pDIManager = NULL;
	}
}

void SceneManager::Load(LPDIRECT3DDEVICE9 d3ddev)
{
	aladdin->Load(d3ddev);

	for (int i = 0; i < scenes.size(); i++)
		scenes[i]->Load(d3ddev);
}

void SceneManager::Draw(float dt)
{
	if (scenes.size() > 0) 
		scenes[0]->Draw(dt);
		
	if (aladdin)
		aladdin->Draw(0.0f);
}

void SceneManager::SetViewPort()
{
	// tạm thời chưa có vtpt: cập nhật viewport khi aladdin nhảy lên hoặc rớt xuống (tọa độ y lệch)
	/*float y = aladdin->GetPosition().y + aladdin->GetHeight() / 2.0f - viewPort->GetHeight() / 2.0f - viewPort->GetY();
	DebugOut(std::to_string(y) + "\n");
	if (y >= -40)
		viewPort->SetY(aladdin->GetPosition().y - viewPort->GetHeight() / 2.0f);*/

	// cập nhật viewport khi aladdin nhảy lên hoặc rớt xuống (tọa độ y lệch)
	if (aladdin->GetPosition().x + aladdin->GetWidth() / 2.0f > viewPort->GetX() + viewPort->GetWidth() / 2.0f)
	{
		float x = aladdin->GetPosition().x + aladdin->GetWidth() / 2.0f - viewPort->GetWidth() / 2.0f;
		viewPort->SetX(x);
	}
	else
	{
		viewPort->SetX(0);
		camera->SetX(0);
	}
}

void SceneManager::ProcessKeyboard()
{
	m_pDIManager->ProcessKeyboard();
}

void SceneManager::Update(float dt)
{
	if (aladdin)
	{
		aladdin->Update(0.0f); // cập nhật aladdin
		aladdin->ProcessAction(m_pDIManager->GetPressedKey());
	}
		

	if (scenes.size() > 0)
	{
		scenes[0]->SetViewPort(viewPort);
		scenes[0]->Update(dt);
	}

	camera->Update(viewPort);
	if (camera) camera->SetTransform(d3ddev);

	SetViewPort();
}
