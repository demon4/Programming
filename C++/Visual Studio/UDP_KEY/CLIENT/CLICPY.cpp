#include "pch.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "sha512.hh"
#pragma comment (lib, "ws2_32.lib")
#pragma warning( disable : 4267) 
using namespace std;
using namespace sw;
static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
void decode64(string b64, string output);
string encode64(string filename);
bool is_file_alive(string filename);
static inline bool is_base64(unsigned char c);
void send_text(string data, SOCKET out, SOCKADDR_IN server);
void send_file(string filename, SOCKET out, SOCKADDR_IN server);
string base64_decode(std::string const& encoded_string);
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
void print_vector(vector<string> v);

int main()
{
	sockaddr_in server;
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk;
		return 88;
	}
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);


	for (;;) {
		string data;
		cout << "(msg): ";
		getline(cin, data);
		send_text(data, out, server);
		cout << endl;
		string filename;
		cout << "(file): ";
		getline(cin, filename);
		send_file(filename, out, server);
	}

	closesocket(out);

	WSACleanup();
}

bool is_file_alive(string filename) {
	std::ifstream infile(filename);
	return infile.good();
}

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

void send_text(string data, SOCKET out, SOCKADDR_IN server) {

	string size = to_string(data.length());
	string typ = "TEXT";
	cout << typ << " : " << size << " : " << data << endl;
	int sendtyp = sendto(out, typ.c_str(), typ.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	int sendpre = sendto(out, size.c_str(), size.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	int senddur = sendto(out, data.c_str(), data.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendpre == SOCKET_ERROR || senddur == SOCKET_ERROR || sendtyp == SOCKET_ERROR)
	{
		cout << "Error: " << WSAGetLastError() << endl;
	}
}

void send_file(string filename, SOCKET out, SOCKADDR_IN server) {
	if (is_file_alive(filename)) {
		cout << "Filename: " << filename << endl;
	}
	else {
		cout << "Filename: " << filename << "does not exist!";
		return;
	}
	const clock_t begin_time = clock();
	cout << "Spliting File ";
	string typ = "DATA";
	string data = encode64(filename);
	cout << "Took " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
	int ssize = data.length();
	int split = 0;
	cout << "Base64 Size: ";
	int i = 1;
	while (i <= ssize) {
		if (ssize / i <= 60000 && ssize % i == 0)
		{
			cout << i << " * " << (ssize / i) << " = " << i * (ssize / i) << endl;
			split = i;
			break;
		}
		i++;

	}
	vector<string> datafile;
	for (auto i = 0; i < data.length(); i += (ssize / split)) {
		datafile.push_back(data.substr(i, (ssize / split)));
	}
	string size = to_string((ssize / split));
	string split_st = to_string(split);

	int sendtyp = sendto(out, typ.c_str(), typ.size() + 1, 0, (sockaddr*)&server, sizeof(server)); // type
	if (sendtyp == SOCKET_ERROR) {
		cout << "send_typ Error: " << WSAGetLastError() << endl;
	}
	int sendfile = sendto(out, filename.c_str(), filename.size() + 1, 0, (sockaddr*)&server, sizeof(server)); // filename	
	if (sendfile == SOCKET_ERROR) {
		cout << "send_file Error: " << WSAGetLastError() << endl;
	}
	int sendhash = sendto(out, sha512::file(filename).c_str(), sha512::file(filename).size() + 1, 0, (sockaddr*)&server, sizeof(server)); // hash
	if (sendhash == SOCKET_ERROR) {
		cout << "sendhash Error: " << WSAGetLastError() << endl;
	}
	int sendpre = sendto(out, size.c_str(), size.size() + 1, 0, (sockaddr*)&server, sizeof(server)); // per split size
	if (sendpre == SOCKET_ERROR) {
		cout << "sendpre Error: " << WSAGetLastError() << endl;
	}
	int sendsplit = sendto(out, split_st.c_str(), split_st.size(), 0, (sockaddr*)&server, sizeof(server)); // # of splits
	if (sendsplit == SOCKET_ERROR) {
		cout << "sendsplit Error: " << WSAGetLastError() << endl;
	}
	for (auto i = datafile.begin(); i != datafile.end(); ++i) {
		string is = *i;
		Sleep(50); //make sure this loop slows down to clients percent loop
		int sendkys = sendto(out, is.c_str(), stoi(size), 0, (sockaddr*)&server, sizeof(server));
		if (sendkys == SOCKET_ERROR) {
			cout << "sendsplit Error: " << WSAGetLastError() << endl;
		}
	}
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

void print_vector(vector<string> v) {
	for (auto i = v.begin(); i != v.end(); ++i) {
		cout << *i << endl;
	}
}
