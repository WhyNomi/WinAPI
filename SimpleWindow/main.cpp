#include<Windows.h>
#include<CommCtrl.h>
#include"resource.h"

#include"function.h"

CONST CHAR SZ_CLASS_NAME[] = "MyWindowClass";

CHAR szFileName[MAX_PATH]{};
LPSTR lpszFileText = NULL;
//VOID WatchChanges(HWND hwnd, void* Action);


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//MessageBox(NULL, lpCmdLine, "Command cool", MB_OK | MB_ICONINFORMATION);
	//MessageBox(NULL, , GetCommandLine(), "Command cool", MB_OK | MB_ICONINFORMATION);

	if (lpCmdLine[0]) //если командная строка не пуста
	{
		//то там лежит имя файла, и мы загружаем его в наше имя файла:
		//strcpy_s(szFileName, MAX_PATH, lpCmdLine);
		for (int i = 0, j = 0; lpCmdLine[i]; i++)
		{
			if (lpCmdLine[i] != '\"')szFileName[j++] = lpCmdLine[i];
		}
	}

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
		WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES,
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

		if (szFileName[0])
		{
			LoadTextFileToEdit(hEdit, szFileName);
		}

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

		//tbb[0].iBitmap = STD_FILENEW;
		//tbb[0].fsState = TBSTATE_ENABLED;
		//tbb[0].fsStyle = TBSTYLE_BUTTON;
		//tbb[0].idCommand = ID_FILE_NEW;

		//tbb[1].iBitmap = STD_FILEOPEN;
		//tbb[1].fsState = TBSTATE_ENABLED;
		//tbb[1].fsStyle = TBSTYLE_BUTTON;
		//tbb[1].idCommand = ID_FILE_OPEN;

		//tbb[2].iBitmap = STD_FILESAVE;
		//tbb[2].fsState = TBSTATE_ENABLED;
		//tbb[2].fsStyle = TBSTYLE_BUTTON;
		//tbb[2].idCommand = ID_FILE_SAVE;

		for (int i = 0; i < sizeof(tbb) / sizeof(TBBUTTON);i++)
		{
			tbb[i].iBitmap = STD_FILENEW + i;
			tbb[i].fsState = TBSTATE_ENABLED;
			tbb[i].fsStyle = TBSTYLE_BUTTON;
			tbb[i].idCommand = ID_FILE_NEW+i;
		}

		SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)&tbb);
		//////////////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////////////////////////////////////

		HWND hStatus = CreateWindowEx
		(
			0,STATUSCLASSNAME,0,WS_CHILD|WS_VISIBLE|SBARS_SIZEGRIP,0,0,0,0,
			hwnd, (HMENU)IDC_STATUS,GetModuleHandle(NULL), NULL
			
		);

	
		int  statwidth[] = { 500,800, -1 };
		SendMessage(hStatus, SB_SETPARTS, sizeof(statwidth) / sizeof(int), (LPARAM)statwidth);
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)(szFileName[0]?szFileName:"Not found"));
		//////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////
		///////////////////////    HOTKEY    ////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////

		RegisterHotKey(hwnd, HOTKEY_NEW, MOD_CONTROL,'N');
		RegisterHotKey(hwnd, HOTKEY_OPEN, MOD_CONTROL,'O');
		RegisterHotKey(hwnd, HOTKEY_SAVE, MOD_CONTROL,'S');
		RegisterHotKey(hwnd, HOTKEY_SAVEAS, MOD_CONTROL+MOD_ALT,'S');
		RegisterHotKey(hwnd, HOTKEY_ABOUT, 0, VK_F1);

		/////////////////////////////////////////////////////////////////////////////////
		//////////////////////////    FONTS    //////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////

		HDC hdc = GetDC(NULL);
		long lfHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		ReleaseDC(NULL, hdc);

		HFONT hf = CreateFont(
			lfHeight,
			0, 0, 0, 0,
			TRUE, 0, 0, 
			0, 0, 0, 0, 0,
			//"Times New Roman"
			"Malgun Gothic"
		);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hf, 0);
		/////////////////////////////////////////////////////////////////////////////////

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
					//ВЫСОТА ПАНЕЛИ ИНСТРУМЕНТОВ...
		HWND hTool = GetDlgItem(hwnd, IDC_TOOLBAR);
		SendMessage(hTool, TB_AUTOSIZE, 0, 0);
		RECT rcTool;
		GetWindowRect(hTool, &rcTool);
		int iToolbarHeight = rcTool.bottom - rcTool.top;

					//ВЫСОТА СТРОКИ СОСТОЯНИЯ...
		HWND hStatus = GetDlgItem(hwnd, IDC_STATUS);
		SendMessage(hStatus, WM_SIZE, 0, 0);
		RECT rcStatus;
		GetWindowRect(hStatus, &rcStatus);
		int iStatusHeight = rcStatus.bottom - rcStatus.top;

					//РАЗМЕР ПОЛЯ ДЛЯ ВВОДА...
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		RECT rcClient;
		GetClientRect(hwnd, &rcClient);
		int iEditHeight = rcClient.bottom - iToolbarHeight - iStatusHeight;
		SetWindowPos(hEdit, NULL, 0, iToolbarHeight, rcClient.right, iEditHeight,SWP_NOZORDER);
		//////////////////////////////////////////////////////////////////////////////////
	}
	break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		DragQueryFile(hDrop, 0, szFileName, MAX_PATH);
		LoadTextFileToEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName);
		DragFinish(hDrop);
	}
	break;
	case WM_HOTKEY:
		switch (wParam)
		{
		case HOTKEY_NEW:	SendMessage(hwnd, WM_COMMAND, ID_FILE_NEW, 0);		break;
		case HOTKEY_OPEN:	SendMessage(hwnd, WM_COMMAND, ID_FILE_OPEN, 0);		break;
		case HOTKEY_SAVE:	SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);		break;
		case HOTKEY_SAVEAS: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVEAS, 0);	break;
		case HOTKEY_ABOUT:  SendMessage(hwnd, WM_COMMAND, ID_HELP_ABOUT, 0);	break;
		
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
		{
			DoFileNew(hwnd);
		}
		break;
		case ID_FILE_OPEN:
		{
			if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
			{
				WatchChanges(hwnd, DoFileOpen);
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
	case WM_CLOSE:
	{
		if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
		{
			
			WatchChanges(hwnd, DestroyWindow);
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

VOID SetFileNameToStatusBar(HWND hEdit)
{


	CHAR szTitle[MAX_PATH] = "SimpleWindowEditor";

	if (szFileName[0])
	{
	LPSTR szNameOnly = strrchr(szFileName, '\\') + 1;

	strcat_s(szTitle, MAX_PATH, " <-> ");
	strcat_s(szTitle, MAX_PATH, szNameOnly);

	}

	HWND hwparent = GetParent(hEdit);
//	SetWindowText(hwparent, szTitle);
	SendMessage(hwparent, WM_SETTEXT, MAX_PATH, (LPARAM)szTitle);
	HWND hStatus = GetDlgItem(hwparent, IDC_STATUS);
	SendMessage(hStatus, WM_CLEAR, 0, (LPARAM)"");
	SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)szFileName);
	

	/*else
	{
		HWND hwndParent = GetParent(hEdit);
		SetWindowText(hwndParent, "Simple WindowEditro");
	}*/
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