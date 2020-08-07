#include <WinSock2.h>
//#include <iostream>
#include <fstream>
#include<string>
#include"Header.h"
//using namespace std;
#pragma  comment(lib,"wsock32.lib")
WSADATA wsd;
SOCKET s;
SOCKADDR_IN servAddr;
SOCKADDR_IN clientAddr;
#pragma warning( disable : 4996 )
char buf[BUF_SIZE];
//
wstring apmac{};
wstring stamac{};
wstring mesg{};
//
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
	string mac1;
	string mac2;
	string msg;
	string str = buf;
	//char mac1[17] = {};
	int nClientLen = sizeof(clientAddr);
	ZeroMemory(buf, BUF_SIZE);
	if (recvfrom(s, buf, BUF_SIZE, 0, (SOCKADDR*)&clientAddr, &nClientLen) == SOCKET_ERROR)
	{
		std::cout << "recvfrom() fail" << std::endl;
		closesocket(s);
		WSACleanup();
	}
	for (int i = 0;i < BUF_SIZE;++i) {
		if (buf[i] == 'd') {
			if (buf[i + 1] == 'e') {
				if (buf[i + 2] == 'v') {
					mac1.assign(buf, i + 7, 12);
					for (int j = 1;j < 6;j++)
						mac1.insert(j * 2 + j - 1, ":");
					//strncpy(mac1, buf + i + 7, 2);
					break;
				}
			}
		}
	}
	for (int i = 0;i < BUF_SIZE;++i) {
		if (buf[i] == 'S') {
			if (buf[i + 1] == 'T') {
				if (buf[i + 2] == 'A') {
					if (buf[i + 3] == '(') {
						mac2.assign(buf, i + 4, 17);
						break;
					}
				}
			}
		}
	}
	if (mac2.empty())
		for (int i = 0;i < BUF_SIZE;++i) {
			if (buf[i] == 'S') {
				if (buf[i + 1] == 't') {
					if (buf[i + 6] == 'n') {
						if (buf[i + 7] == ':') {
							mac2.assign(buf, i + 9, 17);
							break;
						}
					}
				}
			}
		}
	for (int i = 0;i < BUF_SIZE;++i) {
		if (buf[i] == 'm') {
			if (buf[i + 1] == 's') {
				if (buf[i + 2] == 'g') {
					msg.assign(buf, i + 5, str.length() - (i + 5));
					break;
				}
			}
		}
	}
	apmac.assign(mac1.begin(), mac1.end());
	stamac.assign(mac2.begin(), mac2.end());
	mesg.assign(msg.begin(), msg.end());
	//cout << mac2;
	std::cout << buf << std::endl;
	ofstream output(buf, ios::app);
	output << buf;
}

void ReleaseSocket(void)
{
	closesocket(s);
	WSACleanup();
}
