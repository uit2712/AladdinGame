#include "Aladdin.h"

Aladdin::Aladdin(D3DXVECTOR2 position)
{
	aladdinImg = new ImageLoader(GameObjectTypes::AladdinGO, ALADDIN_PATH);
	InitActions();
	InitProperties(position);
}

void Aladdin::InitActions()
{
	std::vector<string> info = ReadMyFile::ReadAllLine(ALADDIN_INFO_PATH);
	for (int i = 0; info.size() > 0 && i < info.size(); i++)
	{
		std::stringstream ss(info[i]);
		std::string name;
		int frames, x1, y1, x2, y2;
		ss >> name >> frames >> x1 >> y1 >> x2 >> y2;
		RECT r;
		r.top = y1;
		r.left = x1;
		r.bottom = y2;
		r.right = x2;
		Sprite* action = new AladdinAction((EAladdinAction)i, m_Position, frames, r);
		actions.push_back(action);
	}
}

void Aladdin::InitProperties(D3DXVECTOR2 position)
{
	m_Color = D3DCOLOR_XRGB(255, 255, 255);
	m_Position = position;
	direction = EDirection::Right;
	mainAction = EAladdinAction::Stand;
	currentAction = actions[EAladdinAction::Stand];
}

Aladdin::~Aladdin()
{
	if (aladdinImg != NULL)
	{
		delete aladdinImg;
		aladdinImg = NULL;
	}

	if (currentAction != NULL)
	{
		delete currentAction;
		currentAction = NULL;
	}

	if (actions.size() > 0)
	{
		for (int i = 0; i < actions.size(); i++)
			actions[i] = NULL;
	}
}

void Aladdin::Load(LPDIRECT3DDEVICE9 device)
{
	if (FAILED(D3DXCreateSprite(device, &m_pSprite)))
		MessageBox(NULL, "FAILED TO CREATE SPRITE!!", "ERROR", MB_OK);

	m_ImgInfo = aladdinImg->GetImgInfo();
	m_Path = aladdinImg->GetImgPath();

	if (FAILED(D3DXCreateTextureFromFileEx(device, m_Path.c_str(),
		m_ImgInfo.Width, m_ImgInfo.Height,
		D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		D3DCOLOR_XRGB(255, 0, 255), NULL, NULL, &m_pTexture)))
		MessageBox(NULL, "FAILED TO CREATE TEXTURE!!", "ERROR", MB_OK);
}

void Aladdin::Draw(float dt)
{
	if (m_pSprite && m_pTexture)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

		AladdinAction* action = (AladdinAction*)currentAction;

		// vẽ sprite
#pragma region vẽ sprite
		m_pSprite->Draw(m_pTexture,
			&action->GetCurrentRect(),
			NULL,
			&D3DXVECTOR3(m_Position.x, m_Position.y, 0),
			m_Color);
#pragma endregion

		m_pSprite->End();
	}
}

void Aladdin::Update(float dt)
{
	currentAction->Update(dt);
}

void Aladdin::ProcessAction(int keyCode)
{
	switch (mainAction)
	{
	case Stand:
		switch (keyCode)
		{
		case DIK_DOWN:
			((AladdinAction*)currentAction)->ResetAction();
			SetMainAction(EAladdinAction::Sitdown);
			SetBonusAction(EAladdinAction::None);
			break;
		case BRANDISH_KEY:
			((AladdinAction*)currentAction)->ResetAction();
			SetBonusAction(EAladdinAction::StandBrandishOneDirection);
			break;
		case THROW_APPLE_KEY:
			((AladdinAction*)currentAction)->ResetAction();
			SetBonusAction(EAladdinAction::StandThrowApple);
			break;
		case JUMP_KEY:
			((AladdinAction*)currentAction)->ResetAction();
			SetBonusAction(EAladdinAction::Jump);
			break;
		default:
			break;
		}
		switch (bonusAction)
		{
		case StandBrandishOneDirection:
		case StandThrowApple:
		case Jump:
			SetMainAction(bonusAction);
			break;
		}
		break;
	case BrandishTwoDirection:
		break;
	case Burn:
		break;
	case ClimbBrandishOneDirection:
		break;
	case ClimbJump:
		break;
	case ClimbString:
		break;
	case ClimbThrowApple:
		break;
	case Jump:
		if (((AladdinAction*)currentAction)->IsEnd1Loop())
		{
			((AladdinAction*)currentAction)->ResetAction();
			SetMainAction(EAladdinAction::Stand);
			SetBonusAction(EAladdinAction::None);
		}
		break;
	case JumpBrandishOneDirection:
		break;
	case JumpThrowApple:
		break;
	case LookingUp:
		break;
	case Run:
		break;
	case RunAndJump:
		break;
	case SitBrandishOneDirection:
	case SitThrowApple:
		if (((AladdinAction*)currentAction)->IsEnd1Loop())
		{
			((AladdinAction*)currentAction)->ResetAction();
			SetMainAction(EAladdinAction::Sitdown);
			SetBonusAction(EAladdinAction::None);
		}
		break;
	case Sitdown:
		switch (keyCode)
		{
		case NONE_KEY:
			((AladdinAction*)currentAction)->ResetAction();
			SetMainAction(EAladdinAction::Stand);
			SetBonusAction(EAladdinAction::None);
			break;
		case BRANDISH_KEY:
			SetBonusAction(EAladdinAction::SitBrandishOneDirection);
			break;
		case THROW_APPLE_KEY:
			SetBonusAction(EAladdinAction::SitThrowApple);
			break;
		case JUMP_KEY:
			SetBonusAction(EAladdinAction::Jump);
			break;
		case DIK_DOWN:
			if (((AladdinAction*)currentAction)->IsEnd1Loop())
				((AladdinAction*)currentAction)->StopRendering();
			break;
		}
		switch (bonusAction)
		{
		case SitBrandishOneDirection:
		case SitThrowApple:
		case Jump:
			if (mainAction != bonusAction)
				SetMainAction(bonusAction);
			break;
		case None:
			if (((AladdinAction*)currentAction)->IsEnd1Loop())
				((AladdinAction*)currentAction)->StopRendering();
			break;
		}
		break;
	case StandBrandishOneDirection:
	case StandThrowApple:
		if (((AladdinAction*)currentAction)->IsEnd1Loop())
		{
			((AladdinAction*)currentAction)->ResetAction();
			SetMainAction(EAladdinAction::Stand);
			SetBonusAction(EAladdinAction::None);
		}
		break;
	case StopRunning:
		break;
	case None:
		break;
	default:
		break;
	}
}

void Aladdin::SetMainAction(EAladdinAction mainAction)
{
	if (this->mainAction != mainAction)
	{
		this->mainAction = mainAction;
		currentAction = actions[this->mainAction];
	}
		
}

void Aladdin::SetBonusAction(EAladdinAction bonusAction)
{
	if(this->bonusAction != bonusAction)
		this->bonusAction = bonusAction;
}
