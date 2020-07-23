#include <WinSock2.h>
//#include <iostream>
#include <fstream>
#include"Header.h"
//using namespace std;
#pragma  comment(lib,"wsock32.lib")
WSADATA wsd;
SOCKET s;
SOCKADDR_IN servAddr;
SOCKADDR_IN clientAddr;
#pragma warning( disable : 4996 )
char buf[BUF_SIZE];

void InitializeSocket()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		std::cout << "WSAStartup fail" << std::endl;
	}
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		std::cout << "socket() fail" << std::endl;
		WSACleanup();
	}
}

void BlindSocket(int p)
{
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons((short)p);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "bind Fail" << std::endl;
		closesocket(s);
		WSACleanup();
	}
}

void AcceptData()
{
	int temp = 0;
	char mac1[17] = {};
	int nClientLen = sizeof(clientAddr);
	ZeroMemory(buf, BUF_SIZE);
	if (recvfrom(s, buf, BUF_SIZE, 0, (SOCKADDR*)&clientAddr, &nClientLen) == SOCKET_ERROR)
	{
		std::cout << "recvfrom() fail" << std::endl;
		closesocket(s);
		WSACleanup();
	}
	for (int i = 0;i < BUF_SIZE && temp == 0;++i) {
		if (buf[i] == 'd') {
			if (buf[i + 1] == 'e') {
				if (buf[i + 2] == 'v') {
					strncpy(mac1, buf + i + 7, 12);
					temp = 1;
				}
			}
		}
	}
	string mac2 = mac1;
	cout << mac2;
	std::cout << buf << std::endl;
	ofstream output(mac2, ios::out);
	output << buf;
}

void ReleaseSocket(void)
{
	closesocket(s);
	WSACleanup();
}
