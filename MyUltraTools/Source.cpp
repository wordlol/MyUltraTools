#include "WindowAPP.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE rhinstance, LPSTR lpstr, int nshowcmd)
{


	if (!InitializeWindow(hinstance, nshowcmd, Wight, Heignt, true))
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

	if (!D3DEX_.CreateScene())
	{
		MessageBox(0, "Scene Create - error", "Error", MB_OK);
		return 0;
	}

	MassegeLoop(D3DEX_);
	D3DEX_.CleanAPP();
	return 0;
}