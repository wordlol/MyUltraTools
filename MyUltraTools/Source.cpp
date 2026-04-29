#include "WindowAPP.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE rhinstance, LPSTR lpstr, int nshowcmd)
{
	if (!InitializeWindow(hinstance, nshowcmd, Wight, Heignt, true))
	{
		MessageBox(0, "Window Create - error", "Error", MB_OK);
		return 0;
	}

	if (!InitializeDirect3dApp(hinstance))
	{
		MessageBox(0, "DIRECT3D Create - error", "Error", MB_OK);
		return 0;
	}

	if (!InitScene())
	{
		MessageBox(0, "Scene Create - error", "Error", MB_OK);
		return 0;
	}

	MassegeLoop();
	CleanAPP();
	return 0;
}