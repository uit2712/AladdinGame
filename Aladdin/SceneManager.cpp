#include "SceneManager.h"



SceneManager::SceneManager(LPDIRECT3DDEVICE9 d3ddev, UINT screenWidth, UINT screenHeight)
{
	zoom = D3DXVECTOR3(2.0f, 2.0f, 1.0f);
	this->d3ddev = d3ddev;
	viewPort = new ViewPort(0, 450, screenWidth / zoom.x, screenHeight / zoom.y);

	aladdin = new Aladdin(D3DXVECTOR2(20, 530));

	camera = new Camera(screenWidth, screenHeight, 0.0f, zoom);

	scenes.push_back(new Background(GameObjectTypes::Map1, MAP1_PATH, viewPort));
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
	if ((int)(aladdin->GetPosition().y + aladdin->GetHeight() / 2.0f) > (int)(viewPort->GetY() + viewPort->GetHeight() / 2.0f))
	{
		DebugOut("yAladdin=" + std::to_string((int)(aladdin->GetPosition().y + aladdin->GetHeight() / 2.0f)) + ", yViewport=" + std::to_string((int)((float)viewPort->GetY() + viewPort->GetHeight() / 2.0f)) + "\n");
		float y = aladdin->GetPosition().y + aladdin->GetHeight()/2.0f - viewPort->GetHeight()/2.0f;
		viewPort->SetY(y);
		
	}

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

void SceneManager::Update(float dt)
{
	if (aladdin)
		aladdin->Update(0.0f); // cập nhật aladdin

	SetViewPort();

	if (scenes.size() > 0)
	{
		scenes[0]->SetViewPort(viewPort);
		scenes[0]->Update(dt);
	}

	camera->Update(viewPort);
	if (camera) camera->SetTransform(d3ddev);
}
