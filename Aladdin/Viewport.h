#pragma once
#include <Windows.h>
#include <d3dx9.h>

class ViewPort
{
protected:
	LONG		m_X;
	LONG		m_Y;
	LONG		m_Width;
	LONG		m_Height;
public:
	ViewPort(const LONG x, const LONG y, const LONG width, const LONG height);
	ViewPort(const RECT r);
	~ViewPort();

	// Getters and setters
	const LONG& GetX() const;
	const LONG& GetY() const;
	const LONG& GetWidth() const;
	const LONG& GetHeight() const;
	const RECT GetRect() const;

	void SetWidth(const LONG width);
	void SetHeight(const LONG height);
	void SetX(const LONG x);
	void SetY(const LONG y);
};