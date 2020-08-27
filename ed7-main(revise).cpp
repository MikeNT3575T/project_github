#include <WinSock2.h>
#include <fstream>
#include<string>
#include"Header.h"
#pragma  comment(lib,"wsock32.lib")
#pragma warning( disable : 4996 )
WSADATA wsd;
SOCKET s;
SOCKADDR_IN servAddr;
SOCKADDR_IN clientAddr;
char buf[BUF_SIZE];
int proreq{};
wstring date{};
wstring times{};
wstring apname{};
wstring apmac{};
wstring stamac{};
wstring mesg{};
wstring ssid{};
wstring connection{};
wstring band{};
wstring signal{};

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
	stamac = {};
	proreq = 0;
	int temp = 0, pos = 0, pos2 = 0, pos3 = 0, count = 0;
	string mac1, mac2, amac;
	string pro, dat, tim, nam, ssd, con, ban, sig;
	int nClientLen = sizeof(clientAddr);
	ZeroMemory(buf, BUF_SIZE);
	if (recvfrom(s, buf, BUF_SIZE, 0, (SOCKADDR*)&clientAddr, &nClientLen) == SOCKET_ERROR)
	{
		std::cout << "recvfrom() fail" << std::endl;
		closesocket(s);
		WSACleanup();
	}
	string str = buf;
	pos = str.find("Station:");
	pos3 = str.find("RSSI:");
	if (pos != str.npos) {
		pos = str.find(">") + 1;
		pos2 = pos + 16;
		dat.assign(str, pos2, 5);
		dat.append(str, pos, 6);
		pos += 7;
		tim.assign(str, pos, 8);
		pos += 14;
		pos2 = str.find(" ", pos);
		nam.assign(str, pos, pos2 - pos);
		pos = str.find("devID=\"") + 7;
		mac1.assign(str, pos, 12);
		amac = mac1;
		for (int i = 1;i < 6;i++)
			mac1.insert(i * 2 + i - 1, ":");
		pos = str.find("Station:") + 9;
		mac2.assign(str, pos, 17);
		pos += 22;
		pos2 = str.find(" ", pos);
		con.assign(str, pos, pos2 - pos);
		if (con == "deauth")
			con = "disassoc";
		else if (con == "reassociated")
			con = "associated";
		pos = str.find("SSID:") + 6;
		pos2 = str.find(",", pos);
		ssd.assign(str, pos, pos2 - pos);
		pos = pos2 + 2;
		pos2 = str.find(" ", pos) - 1;
		ban.assign(str, pos, pos2 - pos);
		if (str[pos2 + 2] != '.') {
			pos = pos2 + 10;
			pos2 = str.find("d", pos);
			sig.assign(str, pos, pos2 - pos);
		}
		date.assign(dat.begin(), dat.end());
		times.assign(tim.begin(), tim.end());
		apname.assign(nam.begin(), nam.end());
		apmac.assign(mac1.begin(), mac1.end());
		stamac.assign(mac2.begin(), mac2.end());
		ssid.assign(ssd.begin(), ssd.end());
		connection.assign(con.begin(), con.end());
		band.assign(ban.begin(), ban.end());
		signal.assign(sig.begin(), sig.end());
		cout << str << '\n';
		ofstream output(amac, ios::app);
		output << str;
	}
	else if (pos3 != str.npos) {
		pos = str.find("RSSI:") + 5;
		pos2 = str.find(" ", pos) - 1;
		pro.assign(str, pos, pos2 - pos);
		while (!pro.empty()) {
			if (pro.back() == '-')
				temp *= 1; //no meaning
			else
				temp += (pro.back() - 48) * pow(10, count);
			pro.pop_back();
			++count;
		}
		proreq = temp;
		//cout << str << '\n';
		ofstream output(amac, ios::app);
		output << str;
	}
}

void ReleaseSocket(void)
{
	closesocket(s);
	WSACleanup();
}
