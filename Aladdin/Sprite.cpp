#include "Sprite.h"

const UINT Sprite::GetWidth() const
{
	return m_Width;
}

const UINT Sprite::GetHeight() const
{
	return m_Height;
}

const D3DXVECTOR2 Sprite::GetPosition() const
{
	return m_Position;
}

const UINT Sprite::GetCurrBound() const
{
	return m_CurrentBound;
}

const RECT Sprite::GetRect() const
{
	RECT r;
	r.left = (long)m_Position.x;
	r.top = (long)m_Position.y;
	r.right = r.left + m_Width;
	r.bottom = r.top + m_Height;

	return r;
}


void Sprite::SetWidth(const UINT width)
{
	m_Width = width;
}

void Sprite::SetHeight(const UINT height)
{
	m_Height = height;
}

void Sprite::SetPosition(const D3DXVECTOR2 position)
{
	m_Position = position;
}

void Sprite::SetCurrBound(const UINT currentBound)
{
	m_CurrentBound = currentBound;
}