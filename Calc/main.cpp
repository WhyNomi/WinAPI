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
		//SetWindowText(GetDlgItem(hwnd, IDC_BUTTON_POWER), "\221A");
		//SetWindowText(GetDlgItem(hwnd, IDC_BUTTON_SQRT), "x\u207F");
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) >= 1000 && LOWORD(wParam) <= 1009)
		{
			GetWindowText(hEdit, sz_buffer, N_BUFFER_SIZE);
			if (strcmp(sz_buffer, sz_buffer_a) == 0)
			{
				SetWindowText(hEdit, "");
			}
			SendMessage(hEdit, WM_CHAR, LOWORD(wParam) - 952, 0);
		}
		if (LOWORD(wParam) >= 1012 && LOWORD(wParam) <= 1018)
		{
			CHAR op[2]{};
			GetWindowText(GetDlgItem(hwnd, LOWORD(wParam)), op, 2);
			if (s)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_RESULT, 0);
			s = op[0];
			GetNumber();

		}
		switch (LOWORD(wParam))
		{
			/*case IDC_BUTTON0:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x30, 0); break;
			case IDC_BUTTON1:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x31, 0); break;
			case IDC_BUTTON2:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x32, 0); break;
			case IDC_BUTTON3:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x33, 0); break;
			case IDC_BUTTON4:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x34, 0); break;
			case IDC_BUTTON5:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x35, 0); break;
			case IDC_BUTTON6:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x36, 0); break;
			case IDC_BUTTON7:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x37, 0); break;
			case IDC_BUTTON8:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x38, 0); break;
			case IDC_BUTTON9:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 0x39, 0); break;*/
		case IDC_BUTTON_POINT:SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_CHAR, 46, 0); break;

		case IDC_BUTTON_PLUS:
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_RESULT, 0);
			s = '+';
			GetNumber();
		}
		break;
		case IDC_BUTTON_MINUS:
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_RESULT, 0);
			s = '-';
			GetNumber();
		}
		break;
		case IDC_BUTTON_ASTER:
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_RESULT, 0);
			s = '*';
			GetNumber();
		}
		break;
		case IDC_BUTTON_SLASH:
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_RESULT, 0);
			s = '/';
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
			b = 0;
			s = 0;
			//strcpy(sz_buffer_a, a - (int)a ? std::to_string(a).c_str() : std::to_string((int)a).c_str());
			strcpy(sz_buffer_a, std::to_string(a - (int)a ? a : (int)a).c_str());
			SetWindowText(hEdit, sz_buffer_a);
		}
		break;
		case IDC_BUTTON_CLEAR:
		{
			a = b = 0;
			s = 0;
			ZeroMemory(sz_buffer, N_BUFFER_SIZE);
			ZeroMemory(sz_buffer_a, N_BUFFER_SIZE);
			ZeroMemory(sz_buffer_b, N_BUFFER_SIZE);
			SetWindowText(hEdit, "");
		}
		break;
		case ID_VIEW_SCINTIFIC:
		{
			EndDialog(hwnd, 0);
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), 0, DlgProc, 0);
			break;
		}
		case ID_VIEW_BLONDE:
		{
			EndDialog(hwnd, 0);
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
			break;
		}
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
		strcpy(sz_buffer_a, sz_buffer);
		a = atof(sz_buffer);
	}
	else
	{
		strcpy(sz_buffer_b, sz_buffer);
		b = atof(sz_buffer);
	}
}