#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "sha512.hh"
#pragma comment (lib, "ws2_32.lib")
using namespace std;
using namespace sw;
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
void decode64(string b64, string output);
string encode64(string filename);
string base64_decode(std::string const& encoded_string);
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

void main()
{

	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk;
		return;
	}

	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY; 
	serverHint.sin_family = AF_INET; 
	serverHint.sin_port = htons(7777); 

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}

	sockaddr_in client;
	int clientLength = sizeof(client);
	char sizebuf[1024];
	char typbuf[1024];
	char filename[4096];
	char hash[513];
	
	while (true)
	{
		ZeroMemory(&client, clientLength);
		ZeroMemory(sizebuf, 1024);
		ZeroMemory(typbuf, 1024);
		ZeroMemory(filename, 4096);
		ZeroMemory(hash, 513);

		int pre_typ = recvfrom(in, typbuf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (pre_typ == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}

		if ((string)typbuf == "DATA") {
			int pre_name = recvfrom(in, filename, 4096, 0, (sockaddr*)&client, &clientLength);
			if (pre_name == SOCKET_ERROR)
			{
				cout << "Error receiving from client " << WSAGetLastError() << endl;
				continue;
			}
			int pre_hash = recvfrom(in, hash, 513, 0, (sockaddr*)&client, &clientLength);
			if (pre_hash == SOCKET_ERROR)
			{
				cout << "Error receiving from client " << WSAGetLastError() << endl;
				continue;
			}
		}

		int pre_bytes = recvfrom(in, sizebuf, 1024, 0, (sockaddr*)&client, &clientLength);
		if (pre_bytes == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}

		vector<char> buf;
		int size = stoi(sizebuf) + 2;
		buf.resize(size);
		int bytesInput = recvfrom(in, &buf[0], buf.size(), 0, (sockaddr*)&client, &clientLength);
		
		if (bytesInput == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		char clientIp[256];
		ZeroMemory(clientIp, 256);
		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
		string type = typbuf;
		if (type == "TEXT") 
		{
			char clientIp[256];
			ZeroMemory(clientIp, 256);
			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
			cout << clientIp << " : [" << size - 1 << " bytes] " << "[" << typbuf << "] ";
			for (auto i = buf.begin(); i != buf.end(); ++i) {
				cout << *i;
			}
			cout << endl;
		}
		else if (type == "DATA") {
			stringstream bi64;
			cout << clientIp << " : [" << size - 1 << "] " << "[" << typbuf << "] ";
			for (auto i = buf.begin(); i != buf.end(); ++i) {
				bi64 << *i;
			}
			string b64 = bi64.str();
			decode64(b64, filename);
			cout << "[RECEIVED FILE: \"" << filename << "\"] ";
			if ((string)sha512::file(filename) == (string)hash) {
				cout << "HASH: " << (string)hash << " = CORRECT" << endl;
			}
			else {
				cout << "HASH: " << (string)hash << " = FAULTY" << endl;
			}

		}
		/*for (auto i = buf.begin(); i != buf.end(); ++i) {
			cout << *i;
		}
		cout << endl;
		/*
		if (stoi(typbuf) == 1) {
			char clientIp[256];
			ZeroMemory(clientIp, 256);
			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
			stringstream bi64;

			cout << clientIp << " : [" << size - 1 << "] ";
			for (auto i = buf.begin(); i != buf.end(); ++i) {
				cout << *i;
			}
			string b64 = bi64.str();
			decode64(b64, "kys.txt");
			cout << endl;
		}
		else if(stoi(typbuf) == 2) {
			char clientIp[256]; 
			ZeroMemory(clientIp, 256); 
			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
			cout << clientIp << " : [" << size - 1 << "] ";
			for (auto i = buf.begin(); i != buf.end(); ++i) {
				cout << *i;
			}
			cout << endl;
		}
		*/


	}


	closesocket(in);

	
	WSACleanup();
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