#include<Windows.h>
#include<CommCtrl.h>
#include"resource.h"

#include"function.h"

CONST CHAR SZ_CLASS_NAME[] = "MyWindowClass";

CHAR szFileName[MAX_PATH]{};
LPSTR lpszFileText = NULL;
//VOID WatchChanges(HWND hwnd, void* Action);


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLice, int nCmdShow)
{
	//1) –Â„ËÒÚ‡ˆËˇ ÍÎ‡ÒÒ‡ ÓÍÌ‡:
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

	//2) —ÓÁ‰‡ÌËÂ ÓÍÌ‡: 
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

	//3) ÷ËÍÎ ÒÓÓ·˘ÂÌËÈ: (Message loop)
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


		//////////////////////////////////////////////////////////////////////////////////
		HWND hTool = CreateWindowEx
		(
			0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
			hwnd, (HMENU)IDC_TOOLBAR, GetModuleHandle(NULL), NULL
		);
		SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

		//ADD BUTTONs:

		TBBUTTON tbb[3]{};
		TBADDBITMAP tbab;
		tbab.hInst = HINST_COMMCTRL;
		tbab.nID = IDB_STD_SMALL_COLOR;
		SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);

		ZeroMemory(tbb, sizeof(tbb));

		tbb[0].iBitmap = STD_FILENEW;
		tbb[0].fsState = TBSTATE_ENABLED;
		tbb[0].fsStyle = TBSTYLE_BUTTON;
		tbb[0].idCommand = ID_FILE_NEW;

		tbb[1].iBitmap = STD_FILEOPEN;
		tbb[1].fsState = TBSTATE_ENABLED;
		tbb[1].fsStyle = TBSTYLE_BUTTON;
		tbb[1].idCommand = ID_FILE_OPEN;

		tbb[2].iBitmap = STD_FILESAVE;
		tbb[2].fsState = TBSTATE_ENABLED;
		tbb[2].fsStyle = TBSTYLE_BUTTON;
		tbb[2].idCommand = ID_FILE_SAVE;

		SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
		//////////////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////////////////////////

		HWND hStatus = CreateWindowEx
		(
			0,STATUSCLASSNAME,0,WS_CHILD|WS_VISIBLE|SBARS_SIZEGRIP,0,0,0,0,
			hwnd, (HMENU)IDC_STATUS,GetModuleHandle(NULL), NULL
			
		);
		int  statwidth[] = { 100,300, -1 };
		SendMessage(hStatus, SB_SETPARTS, sizeof(statwidth) / sizeof(int), (LPARAM)statwidth);
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Chiza");
		//////////////////////////////////////////////////////////////////////////////////
		
	}

	/*case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, LPARAM(hIcon));
	}*/
	break;
	case WM_SIZE:
	{
		/*RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		SetWindowPos(GetDlgItem(hwnd, IDC_EDIT), NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);*/
		
		//////////////////////////////////////////////////////////////////////////////////
					//¬€—Œ“¿ œ¿Õ≈À» »Õ—“–”Ã≈Õ“Œ¬...
		HWND hTool = GetDlgItem(hwnd, IDC_TOOLBAR);
		SendMessage(hTool, TB_AUTOSIZE, 0, 0);
		RECT rcTool;
		GetWindowRect(hTool, &rcTool);
		int iToolbarHeight = rcTool.bottom - rcTool.top;

					//¬€—Œ“¿ —“–Œ » —Œ—“ŒﬂÕ»ﬂ...
		HWND hStatus = GetDlgItem(hwnd, IDC_STATUS);
		SendMessage(hStatus, WM_SIZE, 0, 0);
		RECT rcStatus;
		GetWindowRect(hStatus, &rcStatus);
		int iStatusHeight = rcStatus.bottom - rcStatus.top;

					//–¿«Ã≈– œŒÀﬂ ƒÀﬂ ¬¬Œƒ¿...
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		int iEditHeight = rcClient.bottom - iToolbarHeight - iStatusHeight;
		SetWindowPos(hEdit, NULL, 0, iToolbarHeight, rcClient.right, iEditHeight,SWP_NOZORDER);
		//////////////////////////////////////////////////////////////////////////////////

	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
			{
				switch (MessageBox(hwnd, "Save changed in file?", "Confirmation", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO: DoFileOpen(hwnd);
				case IDCANCEL: break;
				}
			}
			else
			{
				DoFileOpen(hwnd);
			}
		}
		break;
		case ID_FILE_SAVE:
		{
			if (szFileName[0])
			{
				SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
			}
			else
			{
				SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVEAS, 0);
			}
		}
		break;
		case ID_FILE_SAVEAS:
		{
			DoFileSaveAS(hwnd);
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
		break;
		}
		break;
	}
	case WM_CLOSE:
	{
		if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
		{
			switch (MessageBox(hwnd, "Save changed in file?", "Confirmation", MB_YESNOCANCEL | MB_ICONQUESTION))
			{
			case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);

			case IDNO: DestroyWindow(hwnd);
			case IDCANCEL: break;
			}
		}
		else
			DestroyWindow(hwnd);
	}

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

//VOID WatchChanges(HWND hwnd, void* Action)
//{
//	if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
//	{
//		switch (MessageBox(hwnd, "Save changed in file?", "Confirmation", 
//			MB_YESNOCANCEL | MB_ICONQUESTION))
//		{
//		case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
//		case IDNO: Action(hwnd);
//		case IDCANCEL: break;
//		}
//	}
//	else
//		Action(hwnd);
//}