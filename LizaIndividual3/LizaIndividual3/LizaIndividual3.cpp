// LizaIndividual3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LizaIndividual3.h"
#include <string>

#define MAX_LOADSTRING 100
#define ID_CHILDWIN 100

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
INT_PTR CALLBACK	Dialog(HWND, UINT, WPARAM, LPARAM);//функция нашего диалогового окна
LRESULT CALLBACK	Child(HWND, UINT, WPARAM, LPARAM);//функция нашего дочренего окна

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
	LoadString(hInstance, IDC_LIZAINDIVIDUAL3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL3));

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



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIZAINDIVIDUAL3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

HINSTANCE inst;

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable
   inst = hInst;

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
int i = 0, n = 0;//i - текущее число в таймере, n - количество чисел в масиве
bool isDraw = false;//рисуем ли дом?

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	hwndBack = hWnd;//сохраняем ссылку главного окна

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
		case ID_DIALOGOPEN:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, Dialog);//открываем диалоговое окно Dialog - наша функция обработки диалогового окна, IDD_DIALOGBAR - id окна
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
		if (isDraw)
		{

			Rectangle(hdc, 700, 300, 1000, 500);//основа дома
			Rectangle(hdc, 900, 400, 950, 500);//дверь
			Rectangle(hdc, 750, 350, 850, 450);//окно
			Rectangle(hdc, 720, 100, 760, 300);//труба
			POINT p[3];//точки для крыши
			p[0].x = 600;
			p[0].y = 300;
			p[1].x = 1100;
			p[1].y = 300;
			p[2].x = 850;
			p[2].y = 150;
			Polygon(hdc, p, 3);//крыша дома
			//домик не оч красивый, сори, можно коненчо и лучше, ну надеюсь она не придерётся(
		}
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

int x = 0;//позиция текущего числа для записи в масив
int y = 0;
//функция нашего таймера, когда таймер выполняется, он использует эту функцию
void CALLBACK timerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	if (i > 1000)//если число больше 1000, то убиваем таймер
		KillTimer(hwnd, 0);

	bool isHaveTree = false;//есть ли у нас 3?
	bool isHaveEight = false;//есть ли у нас 8?
	int a = i;
	while (a != 0)//пока не ноль
	{
		if (a % 10 == 3)//берем остаток
		{
			isHaveTree = true;//нашли тройку в числе
		}
		else if (a % 10 == 8)//берем остаток
		{
			isHaveEight = true;//нашли 8 в числе
		}
		a /= 10;//делим на десять
	}

	if (isHaveTree || isHaveEight) //если 3 или 8 есть в числе
	{
		arr[n].x = x;//присваиваем нашему масиву коориднаты
		arr[n].y = y;
		arr[n].chars = to_wstring(i);//присваемвам число to_wstring переводит число в строку
		n++;//увеличиваем счетчик

		x += 25;//смещаем каждую след. число на 25
		if (x > 475)//если выходит за границы окна, то переходим на след строку
		{
			y += 15;//спускаемся ниже
			x = 0;//обнуляем x
		}

		InvalidateRect(hwnd, NULL, false);//перерисовываем дочернее окно
	}

	i++;//увеличиваем i
}

//функция создания дочернего окна
void createWindow(HWND hwnd)
{
	WNDCLASS w;//класс окна
	memset(&w, 0, sizeof(WNDCLASS));//выделение памяти под окно
	w.lpfnWndProc = Child;//указываем окну функцию для обработки сообщений в нашем случае это Child
	w.hInstance = hInst;//присваиваем ссылку на главное окно
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//цвет фона
	w.lpszClassName = L"ChildClass";//название класса
	w.hCursor = LoadCursor(nullptr, IDC_CROSS);//курсорчик
	RegisterClass(&w);//регистрируем окно
	HWND child;//hwnd дочренего окна
	child = CreateWindowEx(0, L"ChildClass", (LPCTSTR)NULL,
		WS_CHILD | WS_BORDER | WS_VISIBLE, 0, 0, 450, 450, hwnd, (HMENU)(int)(ID_CHILDWIN), hInst, NULL);//создаем окно, 0,0-позиция окна, 450 - размеры
	ShowWindow(child, SW_NORMAL);//показать окно
	UpdateWindow(child);//обновить

}

//функция обработки команд дочернего окна
LRESULT CALLBACK Child(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

//функция обработки сообщений диалогового окна
INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		int command = LOWORD(wParam);//берём команду
		switch (command)
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON1://если нажата наша 1 кнопка
			isDraw = true;//будем рисовать дом
			InvalidateRect(hwndBack, NULL, false);//перерисовываем главное окно
			break;
		case IDC_BUTTON2://если нажата наша 2 кнопка
			//DialogBox(inst, MAKEINTRESOURCE(IDD_DIALOGBAR1), hwndBack, Timer);//открываем дочернее окно, IDD_DIALOGBAR1 - id окна, hwndBack - ссылка на главное окно, 
			//Timer - название нашей функции
			SetTimer(hwndBack, 0, 8, &timerProc);//при открытии окна запускается таймер с задержкой 8, можно менять, &timerProc - ссылка на нашу функцию таймера
			createWindow(hwndBack);//вызываем функцию создания окна, описана выше

			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ето не я писал)
// Message handler for about box.
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
