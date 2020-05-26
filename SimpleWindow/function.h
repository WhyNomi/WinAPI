#pragma once
#include<Windows.h>
#include"resource.h"

extern CHAR szFileName[MAX_PATH];
extern LPSTR lpszFileText;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL LoadTextFileToEdit(HWND hEdit, LPCTSTR lpszFileName);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCTSTR lpszFileName);

VOID DoFileOpen(HWND hwnd);
VOID DoFileSaveAS(HWND hwnd);
VOID SetFileNameToStatusBar(HWND hEdit);


BOOL FileChanged(HWND hEdit);
