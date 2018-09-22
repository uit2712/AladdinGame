#include "Game.h"

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	Game game(hInstance);
	if (!game.Init()) return 1;

	return game.Run();
}