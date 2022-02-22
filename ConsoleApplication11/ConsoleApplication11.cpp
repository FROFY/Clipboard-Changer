#include <iostream>
#include <Windows.h>
#include <atlstr.h>
#include <string>
using namespace std;

#pragma warning(disable : 4996)

void ReadClip(HWND);

void Clipboard(char str[], int length, CString);

void Check(int length);

void GetKEY();

bool KEY[256];

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	MessageBeep(1);
	MessageBox(NULL, L"Program activated", L"Clipboard by FROFY", NULL);
	while (true)
	{
		GetKEY();
		if (KEY[118])
		{
			ReadClip(hWnd);
		}
		else
			if (KEY[119])
			{
				exit(NULL);
			}
		Sleep(100);
	}
	ReadClip(hWnd);
	return 0;
}

void ReadClip(HWND hWnd)
{
	HGLOBAL hgBuffer;
	char* chBuffer;
	CString fromClipboard;
	int length = 0;
	if (OpenClipboard(hWnd))
	{
		HANDLE datta = GetClipboardData(CF_TEXT);
		char* chBuffer = (char*)GlobalLock(datta);
		fromClipboard = chBuffer;
		GlobalUnlock(datta);
		CloseClipboard();
	}
	length = fromClipboard.GetLength();
	char str[50] = " ";
	for (int i = 0; i < length; i++)
	{
		str[i] += '1';
	}
	Clipboard(str, length, fromClipboard);
}

void Check(int length)
{
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, length * sizeof(CHAR*));
	LPVOID gl = GlobalLock(h);
}

void Clipboard(char str[], int length, CString fromClipboard)
{
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, length * sizeof(CHAR*));
	LPVOID gl = GlobalLock(h);
	memcpy(gl, str, length * sizeof(CHAR*));
	GlobalUnlock(gl);
	OpenClipboard(NULL); // hWnd is set to NULL
	EmptyClipboard(); // Sets clipboard ownership to someone don't know
	SetClipboardData(CF_TEXT, h);  // Successfully data to clipboard!
	CloseClipboard();
}

void GetKEY()
{
	int i = 0;
	while (i < 256)
	{	
		if (GetAsyncKeyState(i)) KEY[i] = 1; 
			else KEY[i] = 0;
				i++;
	}
}
