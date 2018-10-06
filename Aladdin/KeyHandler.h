#pragma once
#include "IKeyEventHandler.h"
#include "Debug.h"
#include <dinput.h>

class KeyHandler : public IKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

