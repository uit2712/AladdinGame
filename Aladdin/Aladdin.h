#pragma once
#include "ImageLoader.h"
#include "Util.h"
#include "AladdinAction.h"
#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ISprite.h"

enum EDirection
{
	Left,
	Right
};

class Aladdin : public Sprite, public ISprite
{
protected:
	ImageLoader* aladdinImg;
	std::vector<Sprite*> actions;
	Sprite* currentAction;
	EDirection direction;
public:
	Aladdin(D3DXVECTOR2 position);
	~Aladdin();

	// methods
	void Draw(float dt);
	void Update(float dt);
	void Load(LPDIRECT3DDEVICE9 device);
private:
	void InitProperties(D3DXVECTOR2 position);
	void InitActions();
};
