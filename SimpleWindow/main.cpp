#include<Windows.h>
#include"Resource.h"

CONST CHAR SZ_CLASS_NAME[] = "MyWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR lpszFileName);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR lpszFileName);
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
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 2;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = SZ_CLASS_NAME;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window registration failed", "Error", MB_OK | MB_ICONERROR);
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
	{
		HICON hIcon = (HICON)LoadImage(NULL, "wood.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);


		////////////////////////////////////////
						//KEK//
		////////////////////////////////////////

		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		//rcClient.

		HWND hEdit = CreateWindowEx
		(
			WS_EX_CLIENTEDGE, "EDIT", "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			100, 100,
			rcClient.right - 100, rcClient.bottom - 100,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		SetFocus(hEdit);
	}
	/*case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, LPARAM(hIcon));
	}*/
	break;
	case WM_SIZE:
	{
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		SetWindowPos(GetDlgItem(hwnd, IDC_EDIT), NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			//----------------OPEN TXT FILE----------------// 
			OPENFILENAME ofn;
			CHAR szFileName[MAX_PATH]{};

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0All files (*.*)\0*.*";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt";

			if (GetOpenFileName(&ofn))
			{
				LoadTextFileToEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
			}
			//----------------OPEN TXT FILE----------------// 
		}
		break;
		case ID_FILE_SAVEAS:
		{
			OPENFILENAME ofn;
			CHAR szFileName[MAX_PATH]{};

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.text)\0*.txt\0All file: (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "txt";

			if (GetSaveFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				SaveTextFileFromEdit(hEdit,szFileName);
			}
		}
		case ID_FILE_EXIT:
		{
			DestroyWindow(hwnd);
			break;
		}
		///////////////////////////////////
		case ID_HELP_ABOUT:
		{

			switch (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC)AboutDlgProc))
			{
			case IDOK:MessageBox(hwnd, "OK", "Info", NULL); break;
			case IDCANCEL:MessageBox(hwnd, "CANCEL", "Info", NULL); break;
			}
		}
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

LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != UINT_MAX)
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (lpszFileText != NULL)
			{
				DWORD dwRead;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))
				{
					if (SetWindowText(hEdit, lpszFileText))
						bSuccess = TRUE;
				}
				GlobalFree(lpszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR lpszFileName)
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(
		lpszFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);


	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextlength = GetWindowTextLength(hEdit);
		if (dwTextlength)
		{
			LPSTR lpszCurrentText = (LPSTR)GlobalAlloc(GPTR, dwTextlength + 1);
			if (lpszCurrentText)
			{
				if (GetWindowText(hEdit, lpszCurrentText, dwTextlength + 1))
				{
					DWORD dwWrite;
					if (WriteFile(hFile, lpszCurrentText, dwTextlength, &dwWrite, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(lpszCurrentText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}