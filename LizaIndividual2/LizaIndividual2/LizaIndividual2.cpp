// LizaIndividual2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LizaIndividual2.h"

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
	LoadString(hInstance, IDC_LIZAINDIVIDUAL2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL2));

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

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIZAINDIVIDUAL2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL2);
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

int state = 0;//������� ������, 0-��������� ������������� � �������, 1-������������� ������, 2-����� ������
int lastTime;//���������� ���������� ��������� �����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
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
		switch (state)//��� ������?
		{
		case 0://��������� ����� � �������������
		{
				  SelectObject(hdc, CreateSolidBrush(RGB(245, 64, 145)));//�������� ��������� �����
				  POINT p[5];//����� ������ ��������������
				  p[0].x = 0;//������ ��������� �����
				  p[0].y = 100;
				  p[1].x = 560;
				  p[1].y = 0;
				  p[2].x = 900;
				  p[2].y = 150;
				  p[3].x = 800;
				  p[3].y = 560;
				  p[4].x = 220;
				  p[4].y = 460;

				  Polygon(hdc, p, 5);//������� �������������
				  SelectObject(hdc, CreateSolidBrush(RGB(64, 64, 255)));//�������� ����� �����
				  Ellipse(hdc, 130, 24, 870, 500);//������ �����
				  break;
		}
		case 1:
			SelectObject(hdc, CreateSolidBrush(RGB(245, 255, 64)));//�������� ������ �����
			Rectangle(hdc, 0, 0, 900, 600);//������ �������������
			break;
		case 2:
			SelectObject(hdc, CreateSolidBrush(RGB(64, 255, 64)));//�������� ������ �����
			Ellipse(hdc, 0, 0, 900, 600);//������ �����
			break;
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONUP://���� ����� ������ ���� ���� ��������
	{
		int time = GetTickCount();//�������� ������� ���� ������� (�� ����, ���� ���������� ������� ���������� �� ������ �����)
		if (state == 1 && time - lastTime < 200)//���� � ��� �������� ������������� � �������� ����� ������ ������ � ����������� < 200 �� ��� ������� �������
			//�� �.�. ����� 2 ������� ����� ������ ������ ������ 200 �����
			state = 0;//����������� � ��������������
		else
			state = 1;//����� ������ �������������
		lastTime = time;//��������� ���� � ����������, ��� ����� ��������� �������� � ������ ���� �� ������ ������ 2 ����
		InvalidateRect(hWnd, NULL, true);//��������������
		break;
	}
	case WM_RBUTTONUP://����� ������ ��������, ����� ������� WM_RBUTTONDOWN, �� ��� ��� �������� ��
		state = 2;//���� ����� ������ �� ��� ����� �������, ���� ��� ��� ������
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
