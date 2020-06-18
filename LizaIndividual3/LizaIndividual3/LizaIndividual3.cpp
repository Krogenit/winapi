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
INT_PTR CALLBACK	Dialog(HWND, UINT, WPARAM, LPARAM);//������� ������ ����������� ����
LRESULT CALLBACK	Child(HWND, UINT, WPARAM, LPARAM);//������� ������ ��������� ����

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

struct vect//��� ���������, ������� �������� ����� � ��� ������� �� x y
{
public://��������� ������
	int x, y;//�������
	wstring chars;//����� � ���� ������
	vect()//����������� 
	{

	}
	vect(int x, int y, wstring chars)//����������� � �����������, ���������� � �����
	{
		this->x = x;//����������� ��������
		this->y = y;
		this->chars = chars;
	}
};

HWND hwndBack;//������ �� ������� ����
vect arr[1024];//����� �����
int i = 0, n = 0;//i - ������� ����� � �������, n - ���������� ����� � ������
bool isDraw = false;//������ �� ���?

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	hwndBack = hWnd;//��������� ������ �������� ����

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
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, Dialog);//��������� ���������� ���� Dialog - ���� ������� ��������� ����������� ����, IDD_DIALOGBAR - id ����
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

			Rectangle(hdc, 700, 300, 1000, 500);//������ ����
			Rectangle(hdc, 900, 400, 950, 500);//�����
			Rectangle(hdc, 750, 350, 850, 450);//����
			Rectangle(hdc, 720, 100, 760, 300);//�����
			POINT p[3];//����� ��� �����
			p[0].x = 600;
			p[0].y = 300;
			p[1].x = 1100;
			p[1].y = 300;
			p[2].x = 850;
			p[2].y = 150;
			Polygon(hdc, p, 3);//����� ����
			//����� �� �� ��������, ����, ����� ������� � �����, �� ������� ��� �� ���������(
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

int x = 0;//������� �������� ����� ��� ������ � �����
int y = 0;
//������� ������ �������, ����� ������ �����������, �� ���������� ��� �������
void CALLBACK timerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	if (i > 1000)//���� ����� ������ 1000, �� ������� ������
		KillTimer(hwnd, 0);

	bool isHaveTree = false;//���� �� � ��� 3?
	bool isHaveEight = false;//���� �� � ��� 8?
	int a = i;
	while (a != 0)//���� �� ����
	{
		if (a % 10 == 3)//����� �������
		{
			isHaveTree = true;//����� ������ � �����
		}
		else if (a % 10 == 8)//����� �������
		{
			isHaveEight = true;//����� 8 � �����
		}
		a /= 10;//����� �� ������
	}

	if (isHaveTree || isHaveEight) //���� 3 ��� 8 ���� � �����
	{
		arr[n].x = x;//����������� ������ ������ ����������
		arr[n].y = y;
		arr[n].chars = to_wstring(i);//����������� ����� to_wstring ��������� ����� � ������
		n++;//����������� �������

		x += 25;//������� ������ ����. ����� �� 25
		if (x > 475)//���� ������� �� ������� ����, �� ��������� �� ���� ������
		{
			y += 15;//���������� ����
			x = 0;//�������� x
		}

		InvalidateRect(hwnd, NULL, false);//�������������� �������� ����
	}

	i++;//����������� i
}

//������� �������� ��������� ����
void createWindow(HWND hwnd)
{
	WNDCLASS w;//����� ����
	memset(&w, 0, sizeof(WNDCLASS));//��������� ������ ��� ����
	w.lpfnWndProc = Child;//��������� ���� ������� ��� ��������� ��������� � ����� ������ ��� Child
	w.hInstance = hInst;//����������� ������ �� ������� ����
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//���� ����
	w.lpszClassName = L"ChildClass";//�������� ������
	w.hCursor = LoadCursor(nullptr, IDC_CROSS);//���������
	RegisterClass(&w);//������������ ����
	HWND child;//hwnd ��������� ����
	child = CreateWindowEx(0, L"ChildClass", (LPCTSTR)NULL,
		WS_CHILD | WS_BORDER | WS_VISIBLE, 0, 0, 450, 450, hwnd, (HMENU)(int)(ID_CHILDWIN), hInst, NULL);//������� ����, 0,0-������� ����, 450 - �������
	ShowWindow(child, SW_NORMAL);//�������� ����
	UpdateWindow(child);//��������

}

//������� ��������� ������ ��������� ����
LRESULT CALLBACK Child(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_PAINT:
	{
					 hdc = BeginPaint(hDlg, &ps);

					 for (int i = 0; i < n; i++)//������ ��� ����� �� ������ ������ �� n - �������
					 {

						 const wchar_t *test = arr[i].chars.c_str();//��������� ������ � ���
						 TextOut(hdc, arr[i].x, arr[i].y, test, _tcslen(test));//������ ����� � ������������ �� ������ � _tcslen - �������� ����� ������
					 }

					 EndPaint(hDlg, &ps);
					 break;
	}
	default:
		return DefWindowProc(hDlg, message, wParam, lParam);
	}
	return 0;
}

//������� ��������� ��������� ����������� ����
INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		int command = LOWORD(wParam);//���� �������
		switch (command)
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON1://���� ������ ���� 1 ������
			isDraw = true;//����� �������� ���
			InvalidateRect(hwndBack, NULL, false);//�������������� ������� ����
			break;
		case IDC_BUTTON2://���� ������ ���� 2 ������
			//DialogBox(inst, MAKEINTRESOURCE(IDD_DIALOGBAR1), hwndBack, Timer);//��������� �������� ����, IDD_DIALOGBAR1 - id ����, hwndBack - ������ �� ������� ����, 
			//Timer - �������� ����� �������
			SetTimer(hwndBack, 0, 8, &timerProc);//��� �������� ���� ����������� ������ � ��������� 8, ����� ������, &timerProc - ������ �� ���� ������� �������
			createWindow(hwndBack);//�������� ������� �������� ����, ������� ����

			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ��� �� � �����)
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
