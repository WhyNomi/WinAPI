#include<Windows.h>

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
	wc.hIcon - LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = NULL;
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
		"THIS IS MY first WINDOW",
		WS_OVERLAPPEDWINDOW,
		450, 200, 640, 480,
		NULL, NULL, hInstance, NULL
	);

	//3) Цикл сообщений: (Message loop)
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}