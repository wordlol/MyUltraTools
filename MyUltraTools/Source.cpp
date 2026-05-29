#include "WindowAPP.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE rhinstance, LPSTR lpstr, int nshowcmd)
{

	if (!InitializeWindow(hinstance, nshowcmd, 800, 800, true))
	{
		MessageBox(0, "Window Create - error", "Error", MB_OK);
		return 0;
	}

	D3DEX D3DEX_(hinstance);

	if (!D3DEX_.GetHR)
	{
		MessageBox(0, "DIRECT3D Create - error", "Error", MB_OK);
		return 0;
	}

	MassegeLoop(D3DEX_);
	return 0;
}