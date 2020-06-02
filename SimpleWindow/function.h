#pragma once
#include<Windows.h>
#include"resource.h"

extern CHAR szFileName[MAX_PATH];
extern LPSTR lpszFileText;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR lpszFileName);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR lpszFileName);

BOOL __stdcall DoFileOpen(HWND hwnd);
VOID DoFileSaveAS(HWND hwnd);

VOID SetFileNameToStatusBar(HWND hEdit);
BOOL FileChanged(HWND hEdit);

VOID WatchChanges(HWND hwnd, BOOL(__stdcall*Action)(HWND))
{
	if (FileChanged(GetDlgItem(hwnd, IDC_EDIT)))
	{
		switch (MessageBox(hwnd, "Save changed in file?", "Confirmation", MB_YESNOCANCEL | MB_ICONQUESTION))
		{
		case IDYES: SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
		case IDNO: Action(hwnd);
		case IDCANCEL: break;
		}
	}
	else
	{
		Action(hwnd);
	}
}