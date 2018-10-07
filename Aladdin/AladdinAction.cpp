#include "AladdinAction.h"



AladdinAction::AladdinAction(EAladdinAction actionType, const D3DXVECTOR2 position, UINT frames, RECT rectInImg)
{
	this->actionType = actionType;
	this->m_Position = position;
	this->m_Col = frames;
	this->rectInImg = rectInImg;

	this->m_Width = (this->rectInImg.right - this->rectInImg.left) / frames;
	this->m_Height = this->rectInImg.bottom - this->rectInImg.top;
	this->m_Row = 1;
	this->m_CurrentBound = 0;
	startLoop = true;
	stopRendering = false;
}


AladdinAction::~AladdinAction()
{
}

RECT AladdinAction::GetRectInImg()
{
	return rectInImg;
}

RECT AladdinAction::GetCurrentRect()
{
	RECT r;
	r.left = m_CurrentBound * m_Width;
	r.right = r.left + m_Width;
	r.top = rectInImg.top;
	r.bottom = r.top + m_Height;

	return r;
}

void AladdinAction::NextFrame()
{
	if(!stopRendering)
		m_CurrentBound = (m_CurrentBound + 1) % m_Col;
	//MessageBox(NULL, std::to_string(m_CurrentBound).c_str(), "fsd", MB_OK);
}

void AladdinAction::StopRendering()
{
	if(!stopRendering)
		stopRendering = true;
}

void AladdinAction::EnableRendering()
{
	if (stopRendering)
		stopRendering = false;
}

void AladdinAction::ResetAction()
{
	startLoop = true;
	m_CurrentBound = 0;
	EnableRendering();
}

boolean AladdinAction::IsEnd1Loop()
{
	if (m_CurrentBound == 0)
		startLoop = true;
	if (m_CurrentBound == m_Col - 1)
		startLoop = false;

	return !startLoop;
}
