#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
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
		SetFocus(GetDlgItem(hwnd, IDC_TEXT_EDIT));
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hwnd, IDC_COLOR))
		{
		HDC hdc = (HDC)wParam; // HDC - Handler to Decive Context.
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0,100,0));
		return (int)GetStockObject(NULL_BRUSH);
		}
	}
	break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkColor(hdc, OPAQUE);
		SetBkColor(hdc, RGB(100,200,120));
		HBRUSH hBrush = CreateSolidBrush(RGB(0,100,0));
		SetTextColor(hdc, RGB(255, 0, 0));

		return (LRESULT)hBrush;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	//default: return FALSE; // In this case  WM_INITDIALOG works incorrect.
	}
		return FALSE; // In this case  WM_INITDIALOG works more correct.
//	return TRUE;
}