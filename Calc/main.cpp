#include<Windows.h>
#include<string>
#include"resource.h"

CONST UINT N_BUFFER_SIZE = 256;
CHAR sz_buffer[N_BUFFER_SIZE]{};
CHAR sz_buffer_a[N_BUFFER_SIZE]{};
CHAR sz_buffer_b[N_BUFFER_SIZE]{};
double a = 0, b = 0;
CHAR s;

HWND hEdit;

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID GetNumber();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		hEdit = GetDlgItem(hwnd, IDC_EDIT1);
		//SetFocus(hEdit);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON0:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x30, 0); break;
		case IDC_BUTTON1:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x31, 0); break;
		case IDC_BUTTON2:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x32, 0); break;
		case IDC_BUTTON3:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x33, 0); break;
		case IDC_BUTTON4:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x34, 0); break;
		case IDC_BUTTON5:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x35, 0); break;
		case IDC_BUTTON6:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x36, 0); break;
		case IDC_BUTTON7:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x37, 0); break;
		case IDC_BUTTON8:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x38, 0); break;
		case IDC_BUTTON9:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x39, 0); break;
		case IDC_BUTTON_POINT:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 46, 0); break;

		case IDC_BUTTON_PLUS:
		{
			s = '+';
			GetNumber();
		}
		break;
		case IDC_BUTTON_RESULT:
		{
			GetNumber();
			switch (s)
			{
			case '+': a += b; break;
			case '-': a -= b; break;
			case '*': a *= b; break;
			case '/': a /= b; break;
			}
			b == 0;
			s = 0;
			strcpy(sz_buffer_a, std::to_string(a).c_str());
			SetWindowText(hEdit, sz_buffer_a);
		}
		break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

VOID GetNumber()
{
	GetWindowText(hEdit, sz_buffer, N_BUFFER_SIZE);
	if (a == 0)
	{
		strcpy(sz_buffer_a, sz_buffer_a);
		a = atof(sz_buffer);
	}
	else
	{
		strcpy(sz_buffer_b, sz_buffer);
		b = atof(sz_buffer);
	}
}