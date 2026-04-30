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
			if (MessageBox(0, "Are you sure you want to exit?",
				"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
};

bool InitializeWindow(HINSTANCE hinstance, int ShowWind, int wignt, int heignt, bool windowed)
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
	wc.lpszClassName = WndClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ERROR REGISTER WINDOW", "Error", MB_OK);
		return false;
	}

	hWND = CreateWindowEx(
		NULL,
		WndClassName,
		"3D REDACTOR",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Wight, Heignt,
		NULL, NULL,
		hinstance,
		NULL
	);

	if (!hWND)
	{
		MessageBox(NULL, "ERROR CREATE WINDOW", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	ShowWindow(hWND, ShowWind);
	UpdateWindow(hWND);
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
			frameCount++;
			if (GetTime() > 1.0f)
			{
				fps = frameCount;
				frameCount = 0;
				StartTimer();
			}

			frameTime = GetFrameTime();

			D3DEX_.UpdateGraphic();
			D3DEX_.UpdateScene(frameTime);
		}
	}
	return (int)msg.wParam;
};