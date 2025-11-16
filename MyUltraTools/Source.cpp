#include "Windows.h"
#include <chrono>
#include "string.h"
#pragma comment(lib,"shell32")

using namespace std;

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
} window;

class ChronoTimer
{
public:
	ChronoTimer() {
		BeginFrame = chrono::steady_clock::now();
	}

	float FrameTimer()
	{
		return chrono::duration<float>(chrono::steady_clock::now() - BeginFrame).count();
	}
	void ResetTimerFrame()
	{
		BeginFrame = chrono::steady_clock::now();
	}
private:
	chrono::steady_clock::time_point BeginFrame;
}Timer;

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

	//регистрация класса окна
	auto NameClassId = RegisterClassEx(&wc);

	//деструктор окна
	window.hWnd = CreateWindowEx(
		NULL,
		MAKEINTATOM(NameClassId),
		"practicum5",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		window.rc.right - window.rc.left,
		window.rc.bottom - window.rc.top,
		NULL,
		NULL,
		window.hIns,
		NULL
	);

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

//загрузка модулей приложения
void InitApp()
{
	//создание и иниализация контекста устройсва и девайс устройства
	window.dev_cont = GetDC(window.hWnd);
	window.contx = CreateCompatibleDC(window.dev_cont);
	SelectObject(window.contx, CreateCompatibleBitmap(window.dev_cont, window.width, window.height));

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	ShellExecute(0, "open", "https://docs.google.com/forms/d/e/1FAIpQLScWQMsOvlFoq9vQm_OywhujJZSwYVG58vPFjwKTx886W7khpQ/viewform", NULL, NULL, SW_SHOWDEFAULT);
}

void StartSite()
{
	Sleep(400);
	keybd_event(0x74, VkKeyScan(0x74), NULL, NULL);
	Sleep(3000);
	keybd_event(0x74, VkKeyScan(0x74), NULL, NULL);
	Sleep(3000);
	keybd_event(0x09, VkKeyScan(0x09), NULL, NULL);
	Sleep(30);
	keybd_event(0x09, VkKeyScan(0x09), NULL, NULL);
	Sleep(30);
	keybd_event(0x09, VkKeyScan(0x09), NULL, NULL);
	Sleep(30);
}

void NextQuestion()
{
	Sleep(30);
	keybd_event(0x09, VkKeyScan(0x09), NULL, NULL);
}

void RandСhoice()
{
	srand(Timer.FrameTimer());
	int R = rand() % 10;

	if (R == 0)
		R = 1;

	for (int i = 0; i < R; i++)
	{
		Sleep(16);
		keybd_event(0x28, VkKeyScan(0x28), NULL, NULL);
	}
}

void Variant(int v)
{
	for (int ii = 0; ii < v; ii++)
	{
		NextQuestion();
		srand(Timer.FrameTimer() + ii);
		int R = rand() % 10;

		if (R == 0)
			R = 1;

		if (R % 2)
		{
			keybd_event(0x20, VkKeyScan(0x20), NULL, NULL);
		}
	}
}

void CopyWord()
{
	const wchar_t* output1 = L"Пиццу";
	const wchar_t* output2 = L"Мясные";
	const wchar_t* output3 = L"Выпечку";
	const wchar_t* output4 = L"Десерты";
	const wchar_t* output5 = L"Вегетарианские";

		srand(Timer.FrameTimer());
		int R = rand() % 5;

		if (R == 0)
			R = 1;

		if (R == 1)
		{
			const size_t len = (wcslen(output1) + 1) * sizeof(wchar_t);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output1, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		if (R == 2)
		{
			const size_t len = (wcslen(output2) + 1) * sizeof(wchar_t);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output2, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		if (R == 3)
		{
			const size_t len = (wcslen(output3) + 1) * sizeof(wchar_t);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output3, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		if (R == 4)
		{
			const size_t len = (wcslen(output4) + 1) * sizeof(wchar_t);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output4, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
		if (R == 5)
		{
			const size_t len = (wcslen(output5) + 1) * sizeof(wchar_t);
			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
			memcpy(GlobalLock(hMem), output5, len);
			GlobalUnlock(hMem);
			OpenClipboard(0);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}

}


void pastWord()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN, NULL, NULL, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTUP, NULL, NULL, 0, 0);
}

void pastWord2()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);

};

void MoveCur(int x,int y)
{
	SetCursorPos(x, y);
}

void Questions(int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i != 4)
		{
		RandСhoice();
		NextQuestion();
		}
		else
		{
			CopyWord();
			MoveCur(window.width/2, (window.height / 2)+10);
			pastWord();
			MoveCur(window.width / 2+40, (window.height / 2) + 153);
			pastWord2();
		}

		NextQuestion();

	}
}

//обновление приложения
void UpdateApp()
{
	StartSite();
	Questions(10);
	Sleep(20);
 	keybd_event(0x20, VkKeyScan(0x20), NULL, NULL);
	Sleep(2000);
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
	}
	return 0;
}