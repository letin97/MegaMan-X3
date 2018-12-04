#include <windows.h>
#include "Game.h"
using namespace Define;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	AllocConsole();

	errno_t err;
	FILE *stream;
	err = freopen_s(&stream, "CONOUT$", "w+", stdout);
	printf("DEBUG CONSOLE=================\n");

	Game game(hInstance, WinWidth, WinHeight, "Mega Man X3", 60);

	game.Init();
	game.Run();

	FreeConsole();

	return 0;
}


