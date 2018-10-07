#pragma once
#include "ImageLoader.h"
#include "Util.h"
#include "AladdinAction.h"
#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ISprite.h"
#include <dinput.h>
#include "Debug.h"

enum EDirection
{
	Left,
	Right
};

#define JUMP_KEY DIK_C
#define BRANDISH_KEY DIK_X
#define THROW_APPLE_KEY DIK_Z
#define NONE_KEY -1

class Aladdin : public Sprite, public ISprite
{
protected:
	ImageLoader*				aladdinImg;
	std::vector<Sprite*>		actions;
	Sprite*						currentAction;
	EDirection					direction;
	EAladdinAction				mainAction;
	EAladdinAction				bonusAction;
	EAladdinAction				bonusAction1;
public:
	Aladdin(D3DXVECTOR2 position);
	~Aladdin();

	// methods
	void Draw(float dt);
	void Update(float dt);
	void Load(LPDIRECT3DDEVICE9 device);
	// thiết lập hành động dựa vào phím đang được nhấn
	void SetActionByKeyPress(int keyCode);
	void ProcessAction(int keyCode);
private:
	void InitProperties(D3DXVECTOR2 position);
	void InitActions();
	void SetMainAction(EAladdinAction mainAction);
	void SetBonusAction(EAladdinAction bonusAction);
};
