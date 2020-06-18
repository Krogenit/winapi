// LizaIndividual1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LizaIndividual1.h"
#include <string>

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
	LoadString(hInstance, IDC_LIZAINDIVIDUAL1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL1));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIZAINDIVIDUAL1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LIZAINDIVIDUAL1);
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

//функция создания файла
void createFile(string numerals, TCHAR *name)//первый параметр строка с числами, второй название файла
{
	const char* test = numerals.c_str();//преобразовываем нашу строку в массив чаров

	char DataBuffer[4096];//создаем буфер для записи в файл
	strncpy_s(DataBuffer, test, sizeof(DataBuffer));//копируем наши чары в буфер
	DataBuffer[sizeof(DataBuffer)-1] = 0;//указываем конец буфера
	DWORD bytesto = (DWORD)strlen(DataBuffer);//узнаем длину буфера
	DWORD byteswriten = 0;//переменная, которая считает сколько байтов записали в файл
	DWORD bytesread = 0;//
	HANDLE hFile;//переменная обработчика файла

	hFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);//создаем файл
	WriteFile(hFile, DataBuffer, bytesto, &byteswriten, NULL);//записываем в него наш DataBuffer
	FindClose(hFile);//закрываем файл

	hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//создаем файл
	char buffir[4096];

	char data[4096] = {};
	if (ReadFile(hFile, static_cast<LPVOID>(&data), sizeof(DataBuffer), &bytesread, NULL))
	{
		for (int i = 0; i < sizeof(data); i++)
		{
			string out = readInt(data, &i);
			if (out.compare("null"))
			{
				int x = atoi(out.c_str());
				x++;
			}
		}
	}
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
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_FILE_CREATECATALOG:
		{
			CreateDirectory(L"catalog1", NULL);//создаем наш каталог
			SetCurrentDirectory(L"catalog1");//выбираем его

			string numerals;//строка с нашими числами

			for (int i = 0; i < 1000; i++)//выбираем нужные
			{
				bool isHaveSeven = false;//есть ли у нас семерка?
				int a = i;
				while (a != 0)//пока не ноль
				{
					if (a % 10 == 7)//берем остаток
					{
						isHaveSeven = true;//нашли семерку в числе
						break;
					}
					a /= 10;//делим на десять
				}
				if (isHaveSeven)//если содержит семерку
				{
					/*добавлем к строке наше число
					//to_string(i) - переводит число в строку для записи
					//append - соединяет строку в одно целое
					// \n - переход на новую строку
					*/
					numerals.append(to_string(i)).append("\n");
				}
			}
			createFile(numerals, L"file1.txt");//вызываем функцию создания файла, она описана выше
		}
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
