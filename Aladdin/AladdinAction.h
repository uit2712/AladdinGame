#pragma once
#include "Sprite.h"
#include <string>

using namespace std;

enum EAladdinAction
{
	Stand,
	BrandishTwoDirection,
	Burn,
	ClimbBrandishOneDirection,
	ClimbJump,
	ClimbString,
	ClimbThrowApple,
	Jump,
	JumpBrandishOneDirection,
	JumpThrowApple,
	LookingUp,
	Run,
	RunAndJump,
	SitBrandishOneDirection,
	SitThrowApple,
	Sitdown,
	StandBrandishOneDirection,
	StandThrowApple,
	StopRunning,
	None
};

class AladdinAction : public Sprite
{
public:
	AladdinAction(EAladdinAction actionType, const D3DXVECTOR2 position, UINT frames, RECT rectInImg);
	~AladdinAction();

	// methods
	void Draw(float dt) { };
	void Update(float dt) { NextFrame(); };
	void Load(LPDIRECT3DDEVICE9 device) { };
	RECT GetRectInImg();
	RECT GetCurrentRect();
	void NextFrame();
	boolean IsEnd1Loop();
	void StopRendering();
	void EnableRendering();
	void ResetAction();
private:
	// phạm vi hành động trong ảnh chung các hành động của Aladdin
	RECT rectInImg;
	EAladdinAction actionType;
	boolean startLoop;
	// dừng chuyển frame
	boolean stopRendering;
};