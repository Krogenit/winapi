// Second.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Second.h"
#include "math.h"
#include <string>

#define MAX_LOADSTRING 100

using namespace std;

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	CreateDiagram(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_SECOND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SECOND));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SECOND));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SECOND);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HPEN pen;
HBRUSH brush;

HWND backup;
int diagramType;
int diagramDataX[20], diagramDataY[20];
int diagramDataLength;
double globalAngle;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	backup = hWnd;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
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
		case ID_CREATEDIAGRAM_VERTICAL:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATEDIAGRAM), hWnd, CreateDiagram);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
					 hdc = BeginPaint(hWnd, &ps);

					 pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					 SelectObject(hdc, pen);

					 int prevX = 0;
					 int prevY = 0;

					 for (int i = 0; i < diagramDataLength; i++)
					 {
						 MoveToEx(hdc, prevX, prevY, NULL);//перемещаем курсор
						 int x = diagramDataX[i];//кординаты точки
						 int y = diagramDataY[i];

						 if (prevX != 0 && prevY != 0)//если ненулеввая точка начинаем рисовать
							LineTo(hdc, x, y);//рисуем
						 prevX = x;
						 prevY = y;
					 }

					 EndPaint(hWnd, &ps);
					 break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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

int dataIndex;

INT_PTR CALLBACK CreateDiagram(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		int command = LOWORD(wParam);

		switch (command)
		{
		case IDC_BUTTON1:
			diagramDataLength = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, false);
			dataIndex = 0;
			break;
		case IDC_BUTTON2:
			if (diagramDataLength != 0)
			{
				//получаем данные о точках
				diagramDataX[dataIndex] = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, false);
				diagramDataY[dataIndex] = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, false);
				dataIndex++;
				//делаем пустые строчки
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT2), L"");
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), L"");
				if (dataIndex == diagramDataLength)
				{
					//закрываем окно если ввели все точки
					EndDialog(hDlg, LOWORD(wParam));
					InvalidateRect(backup, NULL, true);
				}
			}
			break;
		case IDC_BUTTON3:
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}

		if (command == IDC_BUTTON3)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}
		else
		{
			//if (command == IDC_BUTTON2)
			//	EndDialog(hDlg, LOWORD(wParam));
		}
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}