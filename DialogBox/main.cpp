#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//MessageBox(NULL, /*Massage text*/"Sir Charles Spencer Chaplin KBE (16 April 1889 Ц 25 December 1977)",/*1: MBname*/"History message",
	//	//Settings
	//	MB_HELP |
	//	MB_ICONEXCLAMATION |
	//	MB_DEFBUTTON2 |
	//	MB_SYSTEMMODAL);
	//    //Settings 

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;

//ANSI - ASCII
//L -- unicode
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, LPARAM(hIcon));
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hwnd, "Ѕыла нажата кнопка ќки", "info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}