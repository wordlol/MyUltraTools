#pragma once
#include "DirectEngine.h"


// Window app
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
				DestroyWindow(hwnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
};

bool InitializeWindow(HINSTANCE hinstance, int ShowWind, int wignt, int heignt, bool Fullscreen)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Window.WndClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ERROR REGISTER Window", "Error", MB_OK);
		return false;
	}
	DWORD dwStyle = Fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
	Window.hWND = CreateWindowEx(
		NULL,
		Window.WndClassName,
		"3D REDACTOR",
		dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wignt, heignt,
		NULL, NULL,
		hinstance,
		NULL
	);

	if (!Window.hWND)
	{
		MessageBox(NULL, "ERROR CREATE Window", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	ShowWindow(Window.hWND, ShowWind);
	UpdateWindow(Window.hWND);
	return true;
};

int MassegeLoop(D3DEX D3DEX_) {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Timer.frameCount++;
			if (Timer.GetTime() > 1.0f)
			{
				Timer.fps = Timer.frameCount;
				Timer.frameCount = 0;
				Timer.StartTimer();
			}

			Timer.frameTime = Timer.GetFrameTime();

			D3DEX_.UpdateDX(Timer.frameTime);
		}
	}
	return (int)msg.wParam;
};