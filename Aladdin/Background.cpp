#include "Background.h"

Background::Background(GameObjectTypes type, std::string location, ViewPort* viewport)
{
	this->viewport = viewport;
	m_Color = D3DCOLOR_XRGB(255, 255, 255);
	backgroundImg = new ImageLoader(type, location);
}

Background::~Background()
{
	if (backgroundImg == NULL)
	{
		delete backgroundImg;
		backgroundImg = NULL;
	}

	if (viewport == NULL)
	{
		delete viewport;
		viewport = NULL;
	}
}

void Background::Draw(float dt)
{
	if (m_pSprite && m_pTexture)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

		// vẽ sprite
#pragma region vẽ sprite
		m_pSprite->Draw(m_pTexture,
			&viewport->GetRect(),
			NULL,
			&D3DXVECTOR3(viewport->GetRect().left, viewport->GetRect().top, 0),
			m_Color);
#pragma endregion

		m_pSprite->End();
	}
}

void Background::Update(float dt)
{
	
}

void Background::Load(LPDIRECT3DDEVICE9 device)
{
	if (FAILED(D3DXCreateSprite(device, &m_pSprite)))
		MessageBox(NULL, "FAILED TO CREATE SPRITE!!", "ERROR", MB_OK);

	m_ImgInfo = backgroundImg->GetImgInfo();
	m_Path = backgroundImg->GetImgPath();

	if (FAILED(D3DXCreateTextureFromFileEx(device, m_Path.c_str(),
		m_ImgInfo.Width, m_ImgInfo.Height,
		D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		D3DCOLOR_XRGB(255, 0, 255), NULL, NULL, &m_pTexture)))
		MessageBox(NULL, "FAILED TO CREATE TEXTURE!!", "ERROR", MB_OK);
}

void Background::SetViewPort(ViewPort* viewport)
{
	this->viewport = viewport;
}
