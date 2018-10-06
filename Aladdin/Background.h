#pragma once
#include "ImageLoader.h"
#include "Sprite.h"
#include "Viewport.h"
#include "Debug.h"

// Thiết lập các thông tin về background
class Background: public Sprite
{
protected:
	ImageLoader* backgroundImg;
	ViewPort* viewport;
	// directx attributes
	D3DXVECTOR2			m_Position;
	D3DXIMAGE_INFO		m_ImgInfo;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pSprite;
public:
	Background(GameObjectTypes type, std::string location, ViewPort* viewport);
	~Background();
	// methods
	void Draw(float dt);
	void Update(float dt);
	void Load(LPDIRECT3DDEVICE9 device);

	void SetViewPort(ViewPort* viewport);
};

