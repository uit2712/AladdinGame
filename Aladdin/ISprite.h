#pragma once
#include <d3dx9.h>

class ISprite
{
public:
	ISprite() {};
	virtual ~ISprite() {};
	virtual void Draw(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Load(LPDIRECT3DDEVICE9 device) = 0;
};