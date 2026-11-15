#include "Windows.h"
#include "string"
#pragma comment(lib, "Msimg32.lib") // библиотека нужна дл€ работы метода TransparentBlt

//стурктура где хран€тьс€ данные о windows окне
struct
{
	//дескрипторы, контейнеры и буфферы дл€ windows
	RECT rc;
	HINSTANCE hIns;
	HWND hWnd;
	HDC dev_cont, contx;
	MSG msg;
	BOOL gbool = true;

	//определ€ет размер экрана в вашей сиситеме
	int width, height;
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

//создани€ windows окна
void InitWindow()
{
	SetProcessDPIAware();
	window.hWnd = CreateWindow("edit", 0, WS_POPUP | WS_VISIBLE | WS_MAXIMIZE, 0, 0, 0, 0, 0, 0, 0, 0);

	RECT r;
	GetClientRect(window.hWnd, &r);
	window.dev_cont = GetDC(window.hWnd);//из хэндла окна достаем хэндл контекста устройства дл€ рисовани€
	window.width = r.right - r.left;//определ€ем размеры и сохран€ем
	window.height = r.bottom - r.top;
	window.contx = CreateCompatibleDC(window.dev_cont);//второй буфер
	SelectObject(window.contx, CreateCompatibleBitmap(window.dev_cont, window.width, window.height));//прив€зываем окно к контексту
	GetClientRect(window.hWnd, &r);
}

//начало обрезки изображени€
HRGN BEGIN_CLIP(HDC hdc, int x, int y, int w, int h)
{
	HRGN _clip_rgn = CreateRectRgn((x), (y), (x)+(w), (y)+(h));
		SelectClipRgn((hdc), _clip_rgn);

		return _clip_rgn;
}
//конец обрезки изображени€
void END_CLIP(HDC hdc, HRGN _clip_rgn)
{
	SelectClipRgn((hdc), NULL);
	DeleteObject(_clip_rgn);
}

//отрисовка изображений .bmp
void ShowBitmap(HDC hDC, int x, int y, int x1, int y1, HBITMAP hBitmap, bool alpha = false)
{
	HBITMAP hbm, hOldbm;
	HDC hMemDC;
	BITMAP bm;

	hMemDC = CreateCompatibleDC(hDC); // —оздаем контекст пам€ти, совместимый с контекстом отображени€
	hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);// ¬ыбираем изображение bitmap в контекст пам€ти

	if (hOldbm) // ≈сли не было ошибок, продолжаем работу
	{
		GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm); // ќпредел€ем размеры изображени€

		if (alpha)
		{
			TransparentBlt(window.contx, x, y, x1, y1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));//все пиксели белого цвета будут интепретированы как прозрачные
		}
		else
		{
			StretchBlt(hDC, x, y, x1, y1, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); // –исуем изображение bitmap
		}

		SelectObject(hMemDC, hOldbm);// ¬осстанавливаем контекст пам€ти
	}

	DeleteDC(hMemDC); // ”дал€ем контекст пам€ти
}

//загрузка данных из файла .bmp
HBITMAP GetHBITMAP(const LPCSTR& NameImage)
{
	return (HBITMAP)LoadImageA(NULL, NameImage, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

//рисование заливкой
void FillTile(HDC hdc, int px, int py, int size, COLORREF color)
{
	RECT r = { px, py, px + size, py + size };
	HBRUSH br = CreateSolidBrush(color);
	FillRect(hdc, &r, br);
	DeleteObject(br);
}

//ковертирует число в текст дл€ WriteText
LPCSTR ConvertNumInText(float num)
{
	static char txt[32];
	_snprintf_s(txt, sizeof(txt), _TRUNCATE, "%.2f", num);
	return txt;
}

//печатает текст
void WriteText(int x, int y, LPCSTR Text, COLORREF color = RGB(255,255,255))
{
	//поиграем шрифтами и цветами
	SetTextColor(window.contx, color);
	SetBkColor(window.contx, RGB(0, 0, 0));
	SetBkMode(window.contx, TRANSPARENT);
	HFONT hFont = CreateFontW(
		70, 0, 0, 0, FW_BOLD,0, 0, 0,
		RUSSIAN_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"CALIBRI"
	);

	auto hTmp = (HFONT)SelectObject(window.contx, hFont);

	TextOutA(window.contx, x, y, Text, strlen(Text));

	SelectObject(window.contx, hTmp);
	DeleteObject(hFont);
}

//обновление изображений
void UpdateImage()
{
	BitBlt(window.dev_cont, 0, 0, window.width, window.height, window.contx, 0, 0, SRCCOPY);
	//отрисовка заднего фона
	ShowBitmap(window.contx, 0, 0, window.width, window.height, GetHBITMAP("back.bmp"));

	WriteText(100, 60, "ѕривет Windows!");
}


//загрузка модулей приложени€
void InitApp()
{
	//создание и иниализаци€ контекста устройсва и девайс устройства
	window.dev_cont = GetDC(window.hWnd);
	window.contx = CreateCompatibleDC(window.dev_cont);
	SelectObject(window.contx, CreateCompatibleBitmap(window.dev_cont, window.width, window.height));
}

//обновление приложени€
void UpdateApp()
{
	










}


//обработка команд устройств ввода
void UpdateKeyCode()
{
	//выход из приложени€ на ESC
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		window.msg.message = WM_QUIT;
	}
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

	//основной цикл обновлени€ приложени€
	while (window.gbool)
	{
		//обработка соощений дл€ окна
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

		//задержка обновлени€
		Sleep(16);
	}
	return 0;
}