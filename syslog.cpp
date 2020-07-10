#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string>
//#include <sqlext.h>
//#include <sqltypes.h>
//#include <sql.h>

using namespace std;
#pragma  comment(lib,"wsock32.lib")
#define BUF_SIZE 514
char buf[BUF_SIZE];
WSADATA wsd;
SOCKET s;
SOCKADDR_IN servAddr;
SOCKADDR_IN clientAddr;
ofstream output("socket.txt", ios::out);
void InitializeSocket(void)
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

void BlindSocket(int)
{
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons((short)514);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "bind Fail" << std::endl;
		closesocket(s);
		WSACleanup();
	}
}

void AcceptData(void)
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
	for (int i = 0; i < BUF_SIZE && temp == 0; ++i) {
		if (buf[i] == 'd') {
			if (buf[i + 1] == 'e') {
				if (buf[i + 2] == 'v') {
					strncpy_s(mac1, buf + i + 7, 12);
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

int main()
{
	int port;
	cout << "cin port: ";
	cin >> port;
	while (true) {
		InitializeSocket();
		BlindSocket(port);
		AcceptData();
		ReleaseSocket();
	}
	return 0;
}

//int main() {
//#define SQL_RESULT_LEN 240
//#define SQL_RETURN_CODE_LEN 1000
//	//define handles and variables
//	SQLHANDLE sqlConnHandle;
//	SQLHANDLE sqlStmtHandle;
//	SQLHANDLE sqlEnvHandle;
//	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
//	//initializations
//	sqlConnHandle = NULL;
//	sqlStmtHandle = NULL;
//	//allocations
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
//		goto COMPLETED;
//	//output
//	cout << "Attempting connection to SQL Server...";
//	cout << "\n";
//	//connect to SQL Server  
//	//I am using a trusted connection and port 14808
//	//it does not matter if you are using default or named instance
//	//just make sure you define the server name and the port
//	//You have the option to use a username/password instead of a trusted connection
//	//but is more secure to use a trusted connection
//	switch (SQLDriverConnect(sqlConnHandle,
//		NULL,
//		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
//		(SQLCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1457;DATABASE=master;Trusted=true;",
//		//(SQLCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=TWPCNT3575T;UID=sa;PWD=!@QWaszx3575;",
//		SQL_NTS,
//		(SQLCHAR*)retconstring,
//		1024,
//		NULL,
//		SQL_DRIVER_NOPROMPT)) {
//	case SQL_SUCCESS:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
//		break;
//	case SQL_SUCCESS_WITH_INFO:
//		cout << "Successfully connected to SQL Server";
//		cout << "\n";
//		break;
//	case SQL_INVALID_HANDLE:
//		cout << "Could not connect to SQL Server";
//		cout << "\n";
//		goto COMPLETED;
//	case SQL_ERROR:
//		cout << "Could not connect to SQL Server";
//		cout << "\n";
//		goto COMPLETED;
//	default:
//		break;
//	}
//	//if there is a problem connecting then exit application
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
//		goto COMPLETED;
//	//output
//	cout << "\n";
//	cout << "Executing T-SQL query...";
//	cout << "\n";
//	//if there is a problem executing the query then exit application
//	//else display query result
//	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)L"SELECT @@VERSION", SQL_NTS)) {
//		cout << "Error querying SQL Server";
//		cout << "\n";
//		goto COMPLETED;
//	}
//	else {
//		//declare output variable and pointer
//		SQLCHAR sqlVersion[SQL_RESULT_LEN];
//		SQLINTEGER ptrSqlVersion;
//		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
//			//display query result
//			cout << "\nQuery Result:\n\n";
//			cout << sqlVersion << endl;
//		}
//	}
//	//close connection and free resources
//COMPLETED:
//	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//	SQLDisconnect(sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
//	//pause the console window - exit when key is pressed
//	cout << "\nPress any key to exit...";
//	getchar();
//}