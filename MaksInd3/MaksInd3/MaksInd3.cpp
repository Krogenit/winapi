// MaksInd3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MaksInd3.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
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

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MAKSIND3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAKSIND3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAKSIND3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MAKSIND3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

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

int step;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
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
		// Parse the menu selections:
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

		POINT p[4];
		p[0].x = 60;
		p[0].y = 255;
		p[1].x = 70;
		p[1].y = 250;
		p[2].x = 110;
		p[2].y = 275;
		p[3].x = 55;
		p[3].y = 260;
		Polygon(hdc, p, 4);
		Ellipse(hdc, 100, 200, 200, 300);
		Ellipse(hdc, 150, 250, 152, 252);

		p[0].x = 140;
		p[0].y = 140;
		p[1].x = 150;
		p[1].y = 175;
		p[2].x = 130;
		p[2].y = 175;
		Polygon(hdc, p, 3);
		p[0].x = 160;
		p[0].y = 140;
		p[1].x = 170;
		p[1].y = 175;
		p[2].x = 150;
		p[2].y = 175;
		Polygon(hdc, p, 3);

		Ellipse(hdc, 125, 160, 175, 210);

		Ellipse(hdc, 125, 160, 175, 210);
		//глаза
		Ellipse(hdc, 133, 170, 147, 182);
		SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
		Ellipse(hdc, 137, 170, 147, 180);
		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
		Ellipse(hdc, 152, 170, 166, 182);
		SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
		Ellipse(hdc, 156, 170, 166, 180);
		SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
		Ellipse(hdc, 147, 186, 154, 191);
		MoveToEx(hdc, 150, 191, NULL);
		LineTo(hdc, 150, 195);
		//усы
		MoveToEx(hdc, 150, 195, NULL);
		LineTo(hdc, 140, 195);
		MoveToEx(hdc, 140, 195, NULL);
		LineTo(hdc, 135, 190);
		MoveToEx(hdc, 150, 195, NULL);
		LineTo(hdc, 160, 195);
		MoveToEx(hdc, 160, 195, NULL);
		LineTo(hdc, 165, 190);
		//лапы ноги
		MoveToEx(hdc, 170, 290, NULL);
		LineTo(hdc, 170, 320);
		MoveToEx(hdc, 170, 320, NULL);
		LineTo(hdc, 180, 320);
		MoveToEx(hdc, 130, 290, NULL);
		LineTo(hdc, 130, 320);
		MoveToEx(hdc, 130, 320, NULL);
		LineTo(hdc, 140, 320);
		//лапы руки
		switch (step)
		{
		case 0:
			MoveToEx(hdc, 100, 250, NULL);
			LineTo(hdc, 170, 230);
			MoveToEx(hdc, 200, 240, NULL);
			LineTo(hdc, 260, 220);
			Ellipse(hdc, 260, 167, 264, 177);
			Ellipse(hdc, 265, 165, 270, 177);
			SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
			Ellipse(hdc, 260, 175, 270, 185);
			break;
		case 1:
			MoveToEx(hdc, 100, 250, NULL);
			LineTo(hdc, 265, 180);
			MoveToEx(hdc, 200, 240, NULL);
			LineTo(hdc, 265, 180);
			Ellipse(hdc, 260, 167, 264, 177);
			Ellipse(hdc, 265, 165, 270, 177);
			SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
			Ellipse(hdc, 260, 175, 270, 185);
			break;
		case 2:
			MoveToEx(hdc, 100, 250, NULL);
			LineTo(hdc, 150, 195);
			MoveToEx(hdc, 200, 240, NULL);
			LineTo(hdc, 150, 195);
			break;
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONUP:
		step++;
		if (step > 2)
			step = 0;
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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
