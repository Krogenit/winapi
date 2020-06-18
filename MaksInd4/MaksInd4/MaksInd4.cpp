// MaksInd4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MaksInd4.h"
#include <string>

#define MAX_LOADSTRING 100
#define ID_CHILDWIN1 100
#define ID_CHILDWIN2 101
#define IDM_MENUTEST 10204
#define IDM_MENUTEST1 10205

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Child1(HWND, UINT, WPARAM, LPARAM);//функция нашего дочренего окна1
LRESULT CALLBACK	Child2(HWND, UINT, WPARAM, LPARAM);//функция нашего дочренего окна2
INT_PTR CALLBACK	Dialog(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MAKSIND4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAKSIND4));

	// Main message loop:
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAKSIND4));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MAKSIND4);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

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

struct vect//это структура, которая содержит число и его позицию по x y
{
public://публичные данные
	int x, y;//позиция
	wstring chars;//число в виде строки
	vect()//конструктор 
	{

	}
	vect(int x, int y, wstring chars)//конструктор с параметрами, координаты и число
	{
		this->x = x;//присваиваем значения
		this->y = y;
		this->chars = chars;
	}
};

HWND hwndBack;//ссылка на главное окно
vect arr[1024];//масив чисел
int i, n = 0;//i - текущее число в таймере, n - количество чисел в масиве

int countW = 1;
int xSize = 100, ySize = 50;

//функция создания дочернего окна1
void createWindow1(HWND hwnd)
{
	WNDCLASS w;//класс окна
	memset(&w, 0, sizeof(WNDCLASS));//выделение памяти под окно
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = Child1;//указываем окну функцию для обработки сообщений в нашем случае это Child
	w.hInstance = hInst;//присваиваем ссылку на главное окно
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//цвет фона
	w.lpszClassName = L"ChildClass1";//название класса
	w.hCursor = LoadCursor(nullptr, IDC_ARROW);//курсорчик
	//w.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	RegisterClass(&w);//регистрируем окно
	HWND child;//hwnd дочренего окна
	child = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"ChildClass1", L"окно1",
		WS_CHILD | WS_OVERLAPPEDWINDOW, 0, 0, 450, 450, hwnd, (HMENU)(int)(ID_CHILDWIN1), hInst, NULL);//создаем окно, 0,0-позиция окна, 450 - размеры

	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_MENUTEST, L"&Настройки");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&Дом");

	SetMenu(child, hMenubar);

	ShowWindow(child, SW_NORMAL);//показать окно
	UpdateWindow(child);//обновить
}

//функция создания дочернего окна2
void createWindow2(HWND hwnd)
{
	WNDCLASS w;//класс окна
	memset(&w, 0, sizeof(WNDCLASS));//выделение памяти под окно
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = Child2;//указываем окну функцию для обработки сообщений в нашем случае это Child
	w.hInstance = hInst;//присваиваем ссылку на главное окно
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//цвет фона
	w.lpszClassName = L"ChildClass2";//название класса
	w.hCursor = LoadCursor(nullptr, IDC_ARROW);//курсорчик
	RegisterClass(&w);//регистрируем окно
	HWND child;//hwnd дочренего окна
	child = CreateWindowEx(0, L"ChildClass2", L"окно2",
		WS_CHILD | WS_OVERLAPPEDWINDOW, 450, 0, 700, 450, hwnd, (HMENU)(int)(ID_CHILDWIN2), hInst, NULL);//создаем окно, 0,0-позиция окна, 450 - размеры

	ShowWindow(child, SW_NORMAL);//показать окно
	UpdateWindow(child);//обновить
}

int x = 0;//позиция текущего числа для записи в масив
int y = 0;
//функция нашего таймера, когда таймер выполняется, он использует эту функцию
void CALLBACK timerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	i += 2;

	if (i > 100000)//если число больше int_max, то убиваем таймер
		KillTimer(hwnd, 0);

	arr[n].x = x;//присваиваем нашему масиву коориднаты
	arr[n].y = y;
	arr[n].chars = to_wstring((int)pow(i,2)+1);//присваемвам число to_wstring переводит число в строку
	n++;//увеличиваем счетчик
	if ((int)pow(i, 2) + 1 > 10000)
		x += 55;
	else if ((int)pow(i, 2) + 1 > 1000)
		x += 45;
	else if ((int)pow(i, 2) + 1 > 100)
		x += 35;
	else
		x += 25;
	if (x > 475)//если выходит за границы окна, то переходим на след строку
	{
		y += 15;//спускаемся ниже
		x = 0;//обнуляем x
	}

	InvalidateRect(hwnd, NULL, false);//перерисовываем дочернее окно
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	hwndBack = hWnd;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_DOCH1:
			createWindow1(hWnd);
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
			break;
		case ID_DOCH2:
			SetTimer(hWnd, 0, 1000, &timerProc);//при открытии окна запускается таймер с задержкой 8, можно менять, &timerProc - ссылка на нашу функцию таймера
			createWindow2(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
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

//функция обработки команд дочернего окна1
LRESULT CALLBACK Child1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu1;
	HMENU hPopupMenu;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_COMMAND:
	{
					   int wmId = LOWORD(wParam);
					   switch (wmId)
					   {
					   case ID_SIZE1:
						   xSize = 100;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_SIZE2:
						   xSize = 150;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_SIZE3:
						   xSize = 200;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_WND1:
						   countW = 10;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_WND2:
						   countW = 20;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_WND3:
						   countW = 30;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   }
					   break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hDlg, &ps);
		Rectangle(hdc, 100, 50, 102, xSize + 50);
		for (int i = 0; i < countW; i++)
		{
			MoveToEx(hdc, 100, 60+(5*i), NULL);
			LineTo(hdc, 80, 80 + (5 * i));
			MoveToEx(hdc, 100, 60 + (5 * i), NULL);
			LineTo(hdc, 120, 80 + (5 * i));
		}
		EndPaint(hDlg, &ps);
		break;
	}
	case WM_RBUTTONDOWN:


		POINT pt;
		GetCursorPos(&pt);
		hMenu1 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));


		hPopupMenu = GetSubMenu(hMenu1, 0);

		TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hDlg, 0);

		DestroyMenu(hMenu1);
		break;
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return 0;
}


//функция обработки команд дочернего окна2
LRESULT CALLBACK Child2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hDlg, &ps);

		for (int i = 0; i < n; i++)//рисуем все числа из нашего масива до n - счетчик
		{

			const wchar_t *test = arr[i].chars.c_str();//переводим строку в чар
			TextOut(hdc, arr[i].x, arr[i].y, test, _tcslen(test));//рисуем число с координатами из масива и _tcslen - вычисяет длину строки
		}

		EndPaint(hDlg, &ps);
		break;
	}
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
					   int command = LOWORD(wParam);
					   switch (command)
					   {
					   case IDOK:
					   case IDCANCEL:
						   EndDialog(hDlg, LOWORD(wParam));
						   return (INT_PTR)TRUE;
						   break;
					   case IDC_BUTTON1:
						   xSize = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, false);
						   ySize = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, false);
						   countW = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, false);
						   InvalidateRect(hwndBack, NULL, true);
						   break;
					   }
					   break;
	}
	}
	return (INT_PTR)FALSE;
}

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
