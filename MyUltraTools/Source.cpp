#include "Windows.h"

//обрезка изображения
#define BEGIN_CLIP(hdc, x, y, w, h)                       \
    {                                                     \
        HRGN _clip_rgn = CreateRectRgn((x), (y), (x)+(w), (y)+(h)); \
        SelectClipRgn((hdc), _clip_rgn);
//конец обрезки изображений
#define END_CLIP(hdc)                                     \
        SelectClipRgn((hdc), NULL);                       \
        DeleteObject(_clip_rgn);                          \
    }

//стурктура где храняться данные о windows окне
struct
{
	//дескрипторы, контейнеры и буфферы для windows
	RECT rc;
	HINSTANCE hIns;
	HWND hWnd;
	HDC dev_cont, contx;
	MSG msg;
	BOOL gbool = true;

	//определяет размер экрана в вашей сиситеме
	int width = GetSystemMetrics(SM_CXSCREEN), height = GetSystemMetrics(SM_CYSCREEN);
	int startPosX = 0, startPosY = 0;
	bool fullscreen = false;

} window;

//обработка потока сообщений
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
};

//создания windows окна
void InitWindow()
{
	//имя класса окна
	const char* NameClass = "Window";

	//размер окна
	window.rc = { 0,0,window.width,window.height
	};

	//учет размера
	AdjustWindowRect(&window.rc, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	//дескриптор класса окна
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = NameClass;
	wc.hInstance = window.hIns;
	wc.lpfnWndProc = &WindowProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	//регистрация класса окна
	auto NameClassId = RegisterClassEx(&wc);

	// диструкторы окна
	if (window.fullscreen)
	{
		window.hWnd = CreateWindowEx(
			WS_EX_TOPMOST,                
			MAKEINTATOM(NameClassId),
			"project_test",
			WS_POPUP | WS_VISIBLE,        
			window.startPosX, window.startPosY,
			window.rc.right - window.rc.left,
			window.rc.bottom - window.rc.top,
			NULL,
			NULL,
			window.hIns,
			NULL
		);
	}
	else
	{
		window.hWnd = CreateWindowEx(
			NULL,
			MAKEINTATOM(NameClassId),
			"project_test",
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			window.startPosX,
			window.startPosY,
			window.rc.right - window.rc.left,
			window.rc.bottom - window.rc.top,
			NULL,
			NULL,
			window.hIns,
			NULL
		);
	}

	//показ окна
	ShowWindow(window.hWnd, SW_SHOW);
}

//отрисовка изображений .bmp
void ShowBitmap(HDC hDC, int x, int y, int x1, int y1, HBITMAP hBitmapBall)
{
	HBITMAP hbm, hOldbm;
	HDC hMemDC;
	BITMAP bm;

	hMemDC = CreateCompatibleDC(hDC);
	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmapBall);

	if (hOldbm)
	{
		GetObject(hBitmapBall, sizeof(BITMAP), (LPSTR)&bm);
		StretchBlt(hDC, x, y, x1, y1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
		SelectObject(hMemDC, hOldbm);
	}

	DeleteDC(hMemDC);
}

//рисование заливкой
void FillTile(HDC hdc, int px, int py, int size, COLORREF color)
{
	RECT r = { px, py, px + size, py + size };
	HBRUSH br = CreateSolidBrush(color);
	FillRect(hdc, &r, br);
	DeleteObject(br);
}

//загрузка модулей приложения
void InitApp()
{
	//создание и иниализация контекста устройсва и девайс устройства
	window.dev_cont = GetDC(window.hWnd);
	window.contx = CreateCompatibleDC(window.dev_cont);
	SelectObject(window.contx, CreateCompatibleBitmap(window.dev_cont, window.width, window.height));
}

//обновление приложения
void UpdateApp()
{
	










}

//обработка команд устройств ввода
void UpdateKeyCode()
{
	//выход из приложения на ESC
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		window.msg.message = WM_QUIT;
	}
}

//обновление изображений
void UpdateImage()
{
	BitBlt(window.dev_cont, 0, 0, window.width, window.height, window.contx, 0, 0, SRCCOPY);
	//отрисовка заднего фона
	ShowBitmap(window.contx, 0, 0, window.width, window.height, (HBITMAP)LoadImageA(NULL, "back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

//вход в программу
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	window.hIns = hInstance;
	InitWindow();
	InitApp();

	//основной цикл обновления приложения
	while (window.gbool)
	{
		//обработка соощений для окна
		while (PeekMessage(&window.msg, NULL, 0, 0, PM_REMOVE))
		{
			UpdateKeyCode();

			//отбработка сообщений
			if (window.msg.message == WM_QUIT)
			{
				window.gbool = false;
				break;
			}
			TranslateMessage(&window.msg);
			DispatchMessage(&window.msg);
		}

		UpdateImage();
		UpdateApp();

		//задержка обновления
		Sleep(16);
	}
	return 0;
}