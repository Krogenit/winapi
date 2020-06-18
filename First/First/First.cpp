// First.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "First.h"

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
	LoadString(hInstance, IDC_FIRST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIRST));

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

HPEN pen;
HBRUSH brush;

struct Color
{
public:
	int x, y, z;
	Color(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

Color white(255, 255, 255);
Color black(0, 0, 0);
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);
int objectType = 0;
int penType = 0;
int brushType = 0;
Color brushColor = white;
Color penColor = black;

bool isPainting;
int x, y, prevX, prevY, back;


void createBrush()
{
	switch (brushType)
	{
	case 0:
		brush = CreateHatchBrush(HS_VERTICAL, RGB(brushColor.x, brushColor.y, brushColor.z));
		break;
	case 1:
		brush = CreateHatchBrush(HS_HORIZONTAL, RGB(brushColor.x, brushColor.y, brushColor.z));
		break;
	case 2:
		brush = CreateHatchBrush(HS_CROSS, RGB(brushColor.x, brushColor.y, brushColor.z));
		break;
	}
}

void createPen()
{
	switch (penType)
	{
	case 0:
		pen = CreatePen(PS_SOLID, 1, RGB(penColor.x, penColor.y, penColor.z));
		break;
	case 1:
		pen = CreatePen(PS_DASH, 1, RGB(penColor.x, penColor.y, penColor.z));
		break;
	case 2:
		pen = CreatePen(PS_DOT, 1, RGB(penColor.x, penColor.y, penColor.z));
		break;
	}
}

void drawObjects(HDC hdc)
{
	SelectObject(hdc, pen);	SelectObject(hdc, brush);

	switch (objectType)
	{
	case 1:
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, prevX, prevY);
		break;
	case 2:
		Rectangle(hdc, x - 100, y - 50, x + 100, y + 50);
		break;
	case 3:
		Ellipse(hdc, x - 100, y - 50, x + 100, y + 50);
		break;
	case 4:
		POINT points[5];
		points[0].x = x - 100;
		points[0].y = y - 50;
		points[1].x = x - 50;
		points[1].y = y - 20;
		points[2].x = x + 100;
		points[2].y = y + 0;
		points[3].x = x + 50;
		points[3].y = y + 0;
		points[4].x = x - 80;
		points[4].y = y - 10;
		Polygon(hdc, points, 5);
		break;
	case 5:
		points[0].x = x - 50;
		points[0].y = y - 50;
		points[1].x = x - 0;
		points[1].y = y + 20;
		points[2].x = x + 50;
		points[2].y = y - 20;
		points[3].x = x + 100;
		points[3].y = y + 50;
		points[4].x = x + 120;
		points[4].y = y - 60;
		Polyline(hdc, points, 5);
		break;
	case 6:
		RoundRect(hdc, x - 100, y - 50, x + 100, y + 50, 100, 100);
		break;
	}
}

void onMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	x = LOWORD(lParam);
	y = HIWORD(lParam);

	if (isPainting)
	{
		InvalidateRect(hWnd, NULL, false);
		UpdateWindow(hWnd);
	}

	prevX = x;
	prevY = y;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	createBrush();
	createPen();

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FIRST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
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
		case ID_SELECTOBJECT_RECTANGLE:
			objectType = 2;
			break;
		case ID_SELECTOBJECT_ELLIPSE:
			objectType = 3;
			break;
		case ID_SELECTOBJECT_POLYLINE:
			objectType = 5;
			break;
		case ID_SELECTOBJECT_POLYGON:
			objectType = 4;
			break;
		case ID_SELECTOBJECT_ROUNDRECT:
			objectType = 6;
			break;
		case ID_SELECTOBJECT_FREEDRAW:
			objectType = 1;
			break;
		case ID_EDIT_CLEAR:
			back = objectType;
			objectType = 0;
			InvalidateRect(hWnd, NULL, true);
			break;
		case ID_BRUSH_RED:
			brushColor = red;
			createBrush();
			break;
		case ID_BRUSH_GREEN:
			brushColor = green;
			createBrush();
			break;
		case ID_BRUSH_BLUE:
			brushColor = blue;
			createBrush();
			break;
		case ID_BRUSH_WHITE:
			brushColor = white;
			createBrush();
			break;
		case ID_BRUSH_BLACK:
			brushColor = black;
			createBrush();
			break;
		case ID_PEN_RED:
			penColor = red;
			createPen();
			break;
		case ID_PEN_GREEN:
			penColor = green;
			createPen();
			break;
		case ID_PEN_BLUE:
			penColor = blue;
			createPen();
			break;
		case ID_PEN_WHITE:
			penColor = white;
			createPen();
			break;
		case ID_PEN_BLACK:
			penColor = black;
			createPen();
			break;
		case ID_SETBRUSH_VERTICA:
			brushType = 0;
			createBrush();
			break;
		case ID_SETBRUSH_HORIZONTAL:
			brushType = 1;
			createBrush();
			break;
		case ID_SETBRUSH_CROSS:
			brushType = 2;
			createBrush();
			break;
		case ID_SETPEN_SOLIDE:
			penType = 0;
			createPen();
			break;
		case ID_SETPEN_DASH:
			penType = 1;
			createPen();
			break;
		case ID_SETPEN_DOT:
			penType = 2;
			createPen();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		if (objectType == 1)
		{
			isPainting = true;
		}
		else
		{
			InvalidateRect(hWnd, NULL, false);
		}
		break;
	case WM_LBUTTONUP:
		isPainting = false;
		break;
	case WM_MOUSEMOVE:
		onMouseMove(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (back != 0)
		{
			objectType = back;
			back = 0;
		}
		else
			drawObjects(hdc);

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
