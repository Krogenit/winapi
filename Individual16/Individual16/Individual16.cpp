// Individual16.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Individual16.h"
#include <string>
#include <ctime>

#define MAX_LOADSTRING 100

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
	LoadString(hInstance, IDC_INDIVIDUAL16, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INDIVIDUAL16));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INDIVIDUAL16));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_INDIVIDUAL16);
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

string readInt(char* buffer, int* index)
{
	if (buffer[*index] != '\n' && buffer[*index] != '\0' && *index < 4096)
	{
		int x = buffer[*index] - 48;
		string test = to_string(x);
		(*index)++;
		string next = readInt(buffer, index);
		if (!next.compare("null"))
		{
			return test;
		}
		else
		{
			return test.append(next);
		}
	}
	else return string("null");
}

int countNum;

void createFile(string numerals, TCHAR *name)//������ �������� ������ � �������, ������ �������� �����
{
	const char* test = numerals.c_str();//��������������� ���� ������ � ������ �����

	char DataBuffer[4096];//������� ����� ��� ������ � ����
	strncpy_s(DataBuffer, test, sizeof(DataBuffer));//�������� ���� ���� � �����
	DataBuffer[sizeof(DataBuffer)-1] = 0;//��������� ����� ������
	DWORD bytesto = (DWORD)strlen(DataBuffer);//������ ����� ������
	DWORD byteswriten = 0;//����������, ������� ������� ������� ������ �������� � ����
	HANDLE hFile;//���������� ����������� �����

	hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//������� ����
	WriteFile(hFile, DataBuffer, bytesto, &byteswriten, NULL);//���������� � ���� ��� DataBuffer
	CloseHandle(hFile);//��������� ����
}

int N;

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
		case ID_INPUTFILE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog);
			break;
		case ID_OUTFILE:
		{
			HANDLE hFile = CreateFile(L"input.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//��������� ��� ������ ����
			DWORD bytesread = 0;//
			char data[4096] = {};//������ ��� ������
			if (ReadFile(hFile, static_cast<LPVOID>(&data), 4096, &bytesread, NULL))//���������
			{
				string numerals;//������ � ������ �������
				for (int i = 0; i < sizeof(data); i++)
				{
					string out = readInt(data, &i);
					if (out.compare("null"))
					{
						int x = atoi(out.c_str());
						int a = x;
						int num = 0;
						while (a > 0)
						{
							num+=a%10;
							a /= 10;
						}
						if (num == countNum)//����� ���� �����
						{
							numerals.append(to_string(x)).append("\n");
						}
					}
				}
				createFile(numerals, L"output.txt");//�������� ������� �������� �����, ��� ������� ����
			}
		}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
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

int min;

// Message handler for about box.
INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		int command = LOWORD(wParam);
		switch (command)
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		case IDC_BUTTON1:

			N = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, false);

			CreateDirectory(L"Temp", NULL);//������� ��� �������
			SetCurrentDirectory(L"Temp");//�������� ���

			string numerals;//������ � ������ �������
			min = 1000;
			srand(time(NULL));
			for (int i = 0; i < N; i++)
			{
				int x = rand() % 1000;//��������� �����
				if (x < min)
				{
					min = x;
					int a = x;
					countNum = 0;
					while (a > 0)
					{
						countNum+=a % 10;
						a /= 10;
					}
				}
				/*�������� � ������ ���� �����
				//to_string(i) - ��������� ����� � ������ ��� ������
				//append - ��������� ������ � ���� �����
				// \n - ������� �� ����� ������
				*/
				numerals.append(to_string(x)).append("\n");
			}
			createFile(numerals, L"input.txt");//�������� ������� �������� �����, ��� ������� ����
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
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