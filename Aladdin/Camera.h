#pragma once
#include <d3dx9.h>
#include "Sprite.h"
#include "Viewport.h"
#include <string>
#include "Debug.h"

#pragma comment (lib, "d3dx9.lib")

using namespace std;

class Camera
{
public:
	Camera(int width, int height, float angle, D3DXVECTOR3 scaleFactors);
	Camera(void);
	~Camera(void);
protected:
	D3DXVECTOR2 m_Position;		// vị trí của camera
	int			m_Width;
	int			m_Height;

	D3DXVECTOR3 m_ScaleFactors;
	D3DXMATRIX	m_OrthographicMatrix;
	D3DXMATRIX	m_IdentityMatrix;
	D3DXMATRIX	m_ViewMatrix;

	Sprite*		m_Sprite;
	bool		isFollow;
	float		m_Angle;
public:
	void Update();
	void Update(ViewPort* viewPort);
	void SetTransform(LPDIRECT3DDEVICE9 d3ddev) const;
	void SetX(int x);
	void Follow(Sprite* player);
	void UnFollow();
	bool IsFollowing();
};