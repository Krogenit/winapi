// Third.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Third.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THIRD, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THIRD));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THIRD));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_THIRD);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

int winwidth, winheight;
struct Figure
{
public:
	float x, y, xs, ys;
	int width, height;
	Figure(float x, float y, float width, int height, float xs, float ys)
	{
		this->x = x;
		this->y = y;
		this->xs = xs;
		this->ys = ys;
		this->width = width;
		this->height = height;
	}
	void update()
	{
		x += xs;
		y += ys;

		if (y + height + 50 > winheight)
		{
			y = winheight - height - 50;
			ys *= -1;
		}
		else if (y < 0)
		{
			y = 0;
			ys *= -1;
		}
		if (x + width > winwidth)
		{
			x = winwidth - width;
			xs *= -1;
		}
		else if (x < 0)
		{
			x = 0;
			xs *= -1;
		}

	}
	void draw(HDC hdc)
	{
		Rectangle(hdc, x, y, x + width, y + height);
	}
};


void isCollide(Figure* f1, Figure* f2)
{
	//if (f1.x + f1.width >= f2.x)
	//{
	//	if (f1.y > f2.y && f1.y < f2.y + f2.height
	//		|| f1.y + f1.height > f2.y && f1.y + f1.height < f2.y + f2.height)
	//	{
	//		f1.xs *= -1;
	//	}
	//}
	if (f1->x < f2->x + f2->width && f1->x + f1->width > f2->x && f1->y < f2->y + f2->height && f1->y + f1->height > f2->y)
	{
		f1->xs *= -1;
		//f2.xs *= -1;
	}
}

Figure f1(0,0, 100, 100, 4, 2), f2(500,0,150,150, 10, 5);

void CALLBACK timerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	f1.update();

	InvalidateRect(hwnd, NULL, true);
}

void CALLBACK timerProc2(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	f2.update();

	InvalidateRect(hwnd, NULL, true);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	SetTimer(hWnd, 0, 10, &timerProc);
	SetTimer(hWnd, 1, 20, &timerProc2);

	RECT rect;
	GetWindowRect(hWnd, &rect);
	winwidth = rect.right - rect.left;
	winheight = rect.bottom - rect.top;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		isCollide(&f1, &f2);
		isCollide(&f2, &f1);

		f1.draw(hdc);
		f2.draw(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
