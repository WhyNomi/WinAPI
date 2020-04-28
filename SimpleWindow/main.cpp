#include<Windows.h>
#include"Resource.h"

CONST CHAR SZ_CLASS_NAME[] = "MyWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLice, int nCmdShow)
{
	//1) Регистация класса окна:
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW+1;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = SZ_CLASS_NAME;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL,"Window registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна: 
	HWND hwnd = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		SZ_CLASS_NAME,
		"THIS IS MY FIRST WINDOW",
		WS_OVERLAPPEDWINDOW,
		550, 200, 640, 480,
		NULL, NULL, hInstance, NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window not created", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Цикл сообщений: (Message loop)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		
		break;
	case WM_COMMAND:
	{
		switch (uMsg)
		{
			//Реализовать диалоговые окна.
		}
		break;
	}
	case WM_CLOSE:
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "А шо так?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
	/*else
		{
			MessageBox(hwnd,"Хорошо", "")
		}*/
		break;
	case WM_DESTROY:
		//MessageBox(hwnd, "Da", "Info", MB_OK);
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return 0;
}