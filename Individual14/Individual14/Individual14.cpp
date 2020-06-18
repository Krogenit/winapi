// MaksInd4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Individual14.h"
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
LRESULT CALLBACK	Child1(HWND, UINT, WPARAM, LPARAM);//������� ������ ��������� ����1
LRESULT CALLBACK	Child2(HWND, UINT, WPARAM, LPARAM);//������� ������ ��������� ����2
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
	LoadString(hInstance, IDC_INDIVIDUAL14, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INDIVIDUAL14));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INDIVIDUAL14));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_INDIVIDUAL14);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
int i = 1, n = 0;//i - ������� ����� � �������, n - ���������� ����� � ������

int countW;
int xSize = 40;

//������� �������� ��������� ����1
void createWindow1(HWND hwnd)
{
	WNDCLASS w;//����� ����
	memset(&w, 0, sizeof(WNDCLASS));//��������� ������ ��� ����
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = Child1;//��������� ���� ������� ��� ��������� ��������� � ����� ������ ��� Child
	w.hInstance = hInst;//����������� ������ �� ������� ����
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//���� ����
	w.lpszClassName = L"ChildClass1";//�������� ������
	w.hCursor = LoadCursor(nullptr, IDC_ARROW);//���������
	//w.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	RegisterClass(&w);//������������ ����
	HWND child;//hwnd ��������� ����
	child = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"ChildClass1", L"����1",
		WS_CHILD | WS_OVERLAPPEDWINDOW, 0, 0, 450, 450, hwnd, (HMENU)(int)(ID_CHILDWIN1), hInst, NULL);//������� ����, 0,0-������� ����, 450 - �������

	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, IDM_MENUTEST, L"&���������");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&���");

	SetMenu(child, hMenubar);

	ShowWindow(child, SW_NORMAL);//�������� ����
	UpdateWindow(child);//��������
}

//������� �������� ��������� ����2
void createWindow2(HWND hwnd)
{
	WNDCLASS w;//����� ����
	memset(&w, 0, sizeof(WNDCLASS));//��������� ������ ��� ����
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = Child2;//��������� ���� ������� ��� ��������� ��������� � ����� ������ ��� Child
	w.hInstance = hInst;//����������� ������ �� ������� ����
	w.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));//���� ����
	w.lpszClassName = L"ChildClass2";//�������� ������
	w.hCursor = LoadCursor(nullptr, IDC_ARROW);//���������
	RegisterClass(&w);//������������ ����
	HWND child;//hwnd ��������� ����
	child = CreateWindowEx(0, L"ChildClass2", L"����2",
		WS_CHILD | WS_OVERLAPPEDWINDOW, 450, 0, 700, 450, hwnd, (HMENU)(int)(ID_CHILDWIN2), hInst, NULL);//������� ����, 0,0-������� ����, 450 - �������

	ShowWindow(child, SW_NORMAL);//�������� ����
	UpdateWindow(child);//��������
}

int x = 0;//������� �������� ����� ��� ������ � �����
int y = 0;
int summ = 0;
//������� ������ �������, ����� ������ �����������, �� ���������� ��� �������
void CALLBACK timerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	summ += i;
	i += 1;

	if (summ > 100000)//���� ����� ������ int_max, �� ������� ������
		KillTimer(hwnd, 0);

	arr[n].x = x;//����������� ������ ������ ����������
	arr[n].y = y;
	arr[n].chars = to_wstring(summ);//����������� ����� to_wstring ��������� ����� � ������
	n++;//����������� �������
	if (summ > 10000)
		x += 55;
	else if (summ > 1000)
		x += 45;
	else if (summ > 100)
		x += 35;
	else
		x += 25;
	if (x > 475)//���� ������� �� ������� ����, �� ��������� �� ���� ������
	{
		y += 15;//���������� ����
		x = 0;//�������� x
	}

	InvalidateRect(hwnd, NULL, false);//�������������� �������� ����
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
		case ID_DOCH1:
			createWindow1(hWnd);
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
			break;
		case ID_DOCH2:
			SetTimer(hWnd, 0, 100, &timerProc);//��� �������� ���� ����������� ������ � ��������� 8, ����� ������, &timerProc - ������ �� ���� ������� �������
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

//������� ��������� ������ ��������� ����1
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
					   case ID_VAGON2:
						   countW = 2;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_VAGON4:
						   countW = 4;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_VAGON6:
						   countW = 6;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_VAGON10:
						   xSize = 40;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_VAGON20:
						   xSize = 60;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   case ID_VAGON40:
						   xSize = 80;
						   InvalidateRect(hDlg, NULL, true);
						   break;
					   }
					   break;
	}
	case WM_PAINT:
	{
					 int x = 20;
					 int y = 60;
					 int size = 40;
					 int ySize = 20;

					 int wheelSize = 3;

					 hdc = BeginPaint(hDlg, &ps);

					 Rectangle(hdc, x+5, y-20, x+15, y);
					 Rectangle(hdc, x, y, x + size, y + ySize);

					 Rectangle(hdc, x + size, y + ySize-1, x + size + 10, y + ySize);

					 Ellipse(hdc, x - wheelSize+5, y + ySize - 5 - wheelSize, x + 15 + wheelSize, y + ySize + 5 + wheelSize);
					 Ellipse(hdc, x + size - 15 - wheelSize, y + ySize - 5 - wheelSize, x + size + wheelSize-5, y + ySize + 5 + wheelSize);

					 for (int i = 0; i < countW; i++)
					 {
						 Rectangle(hdc, xSize * i + 70, 60, i * xSize + 65 + xSize, 80);

						 Rectangle(hdc, i * xSize + 65 + xSize, 79, i * xSize + 65 + xSize+10, 80);

						 Ellipse(hdc, xSize * i + 70 - wheelSize+5, y + ySize - 5 - wheelSize, xSize * i + 70 + 15 + wheelSize, y + ySize + 5 + wheelSize);

						 Ellipse(hdc, i * xSize + 65 + xSize - 15 - wheelSize, y + ySize - 5 - wheelSize, i * xSize + 65 + xSize + wheelSize-5, y + ySize + 5 + wheelSize);
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


//������� ��������� ������ ��������� ����2
LRESULT CALLBACK Child2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
						   countW = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, false);
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
