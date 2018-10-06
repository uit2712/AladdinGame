#include "ViewPort.h"
#include "Debug.h"

ViewPort::ViewPort(const LONG x, const LONG y, const LONG width, const LONG height)
{
	DebugOut("y=" + std::to_string(y));
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

ViewPort::ViewPort(const RECT r)
{
	m_X = r.left;
	m_Y = r.top;
	m_Width = r.right - r.left;
	m_Height = r.bottom - r.top;
}

ViewPort::~ViewPort()
{

}

const LONG& ViewPort::GetX() const
{
	return m_X;
}

const LONG& ViewPort::GetY() const
{
	return m_Y;
}

const LONG& ViewPort::GetWidth() const
{
	return m_Width;
}

const LONG& ViewPort::GetHeight() const
{
	return m_Height;
}

const RECT ViewPort::GetRect() const
{
	RECT r;
	r.top = m_Y;
	r.left = m_X;
	r.right = r.left + m_Width;
	r.bottom = r.top + m_Height;

	return r;
}

void ViewPort::SetX(const LONG x)
{
	this->m_X = x;
}

void ViewPort::SetY(const LONG y)
{
	this->m_Y = y;
}

void ViewPort::SetWidth(const LONG width)
{
	this->m_Width = width;
}

void ViewPort::SetHeight(const LONG height)
{
	this->m_Height = height;
}