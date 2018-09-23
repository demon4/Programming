//server
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
using namespace std;

int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "winsock_startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET nConnection;
	nConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	if (nConnection == 0) {
		std:cout << "Failed to accept new client's connection." << std::endl;
	}
	else {
		std::cout << "Client Connected!" << std::endl;
	}
	cin.get();

	return 0;
}
