#pragma once
#include <d3dx9.h>
#include <iostream>

using namespace std;

class Sprite
{
public:
	virtual ~Sprite() {};

	// getters
	const UINT GetWidth() const;
	const UINT GetHeight() const;
	virtual const D3DXVECTOR2 GetPosition() const;
	virtual const UINT GetCurrBound() const;
	const RECT GetRect() const;

	// setters
	void SetWidth(const UINT width);
	void SetHeight(const UINT height);
	virtual void SetPosition(const D3DXVECTOR2 position);
	void SetCurrBound(const UINT currentBound);

	// methods
	virtual void Draw(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Load(LPDIRECT3DDEVICE9 device) = 0;
protected:
	// directx attributes
	D3DXVECTOR2			m_Position;
	D3DXIMAGE_INFO		m_ImgInfo;
	LPDIRECT3DTEXTURE9	m_pTexture;
	LPD3DXSPRITE		m_pSprite;

	// sprite attributes
	std::string			m_Path;
	UINT				m_Width;
	UINT				m_Height;
	D3DCOLOR			m_Color;
	UINT				m_CurrentBound;
	UINT				m_Row;
	UINT				m_Col;
};

