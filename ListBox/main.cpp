#include<Windows.h>
#include"resource.h"

HWND hList;
CONST CHAR* str[] = 
{
	"This","is","my","first","List","Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	//	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	//	SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(str) / sizeof(*str); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)str[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{

			CHAR str[256]{};
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);

			MessageBox(hwnd, str, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:

		EndDialog(hwnd, 0);
		break;
	default:return FALSE;
	}
	return TRUE;
}