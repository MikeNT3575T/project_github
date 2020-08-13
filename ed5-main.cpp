#include"Header.h"
/*******************************************************************************
/* ODBCSQL: a sample program that implements an ODBC command line interpreter.
/*
/* USAGE:   ODBCSQL DSN=<dsn name>   or
/*          ODBCSQL FILEDSN=<file dsn> or
/*          ODBCSQL DRIVER={driver name}
/*
/*
/* Copyright(c) Microsoft Corporation.   This is a WDAC sample program and
/* is not suitable for use in production environments.
/*
/******************************************************************************/
/* Modules:
/*      Main                Main driver loop, executes queries.
/*      DisplayResults      Display the results of the query if any
/*      AllocateBindings    Bind column data
/*      DisplayTitles       Print column titles
/*      SetConsole          Set console display mode
/*      HandleError         Show ODBC error messages
/******************************************************************************/

#include <windows.h> 
#include <sql.h> 
#include <sqlext.h> 
#include <stdio.h> 
#include <conio.h> 
#include <tchar.h> 
#include <stdlib.h> 
#include <sal.h> 
//#include <iostream>


/*******************************************/
/* Macro to call ODBC functions and        */
/* report an error on failure.             */
/* Takes handle, handle type, and stmt     */
/*******************************************/


#define TRYODBC(h, ht, x)   {   RETCODE rcc = x; \
								if (rcc != SQL_SUCCESS) \
								{ \
								HandleDiagnosticRecord(h, ht, rcc); \
								} \
								if (rcc == SQL_ERROR) \
								{ \
								fwprintf(stderr, L"Error in " L#x L"\n"); \
								goto Exit;  \
								}  \
							}
//#define TRYODBC(h, ht, x) {}
							/******************************************/
							/* Structure to store information about   */
							/* a column.
							/******************************************/

typedef struct STR_BINDING {
	SQLSMALLINT         cDisplaySize;           /* size to display  */
	WCHAR* wszBuffer;             /* display buffer   */
	SQLLEN              indPtr;                 /* size or null     */
	BOOL                fChar;                  /* character col?   */
	struct STR_BINDING* sNext;                 /* linked list      */
} BINDING;


void syslogtest(wstring& syslog1, wstring& syslog2);
/******************************************/
/* Forward references                     */
/******************************************/

void HandleDiagnosticRecord(SQLHANDLE      hHandle,
	SQLSMALLINT    hType,
	RETCODE        RetCode);

void DisplayResults(HSTMT       hStmt,
	SQLSMALLINT cCols);

void AllocateBindings(HSTMT         hStmt,
	SQLSMALLINT   cCols,
	BINDING** ppBinding,
	SQLSMALLINT* pDisplay);


void DisplayTitles(HSTMT    hStmt,
	DWORD    cDisplaySize,
	BINDING* pBinding);

void SetConsole(DWORD   cDisplaySize,
	BOOL    fInvert);

/*****************************************/
/* Some constants                        */
/*****************************************/


#define DISPLAY_MAX 50          // Arbitrary limit on column width to display 
#define DISPLAY_FORMAT_EXTRA 3  // Per column extra display bytes (| <data> ) 
#define DISPLAY_FORMAT      L"%c %*.*s " 
#define DISPLAY_FORMAT_C    L"%c %-*.*s " 
#define NULL_SIZE           6   // <NULL> 
#define SQL_QUERY_SIZE      1000 // Max. Num characters for SQL Query passed in. 

#define PIPE                L'|' 

SHORT   gHeight = 80;       // Users screen height 


int __cdecl wmain(int argc, _In_reads_(argc) WCHAR** argv)
{
	std::cout << "wmain\n";
	RETCODE		rc = 0;
	SQLHENV     hEnv = NULL;
	SQLHDBC     hDbc = NULL;
	SQLHSTMT    hStmt = NULL;
	WCHAR* pwszConnStr;
	WCHAR       wszInput[SQL_QUERY_SIZE];

	// Allocate an environment 

	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) == SQL_ERROR)
	{
		fwprintf(stderr, L"Unable to allocate an environment handle\n");
		exit(-1);
	}

	// Register this as an application that expects 3.x behavior, 
	// you must register something if you use AllocHandle 
	rc = SQLSetEnvAttr(hEnv,
		SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3,
		0);
	TRYODBC(hEnv,
		SQL_HANDLE_ENV,
		rc);

	// Allocate a connection 
	TRYODBC(hEnv,
		SQL_HANDLE_ENV,
		SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc));

	if (argc > 1)
	{
		pwszConnStr = (WCHAR*)*++argv;
	}
	else
	{
		pwszConnStr = (WCHAR*)" ";
	}

	// Connect to the driver.  Use the connection string if supplied 
	// on the input, otherwise let the driver manager prompt for input. 
	rc = SQLDriverConnect(hDbc,
		GetDesktopWindow(),
		(SQLWCHAR*)pwszConnStr,
		SQL_NTS,
		NULL,
		0,
		NULL,
		SQL_DRIVER_COMPLETE);
	TRYODBC(hDbc,
		SQL_HANDLE_DBC,
		rc);

	fwprintf(stderr, L"Connected!\n");

	TRYODBC(hDbc,
		SQL_HANDLE_DBC,
		SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt));

	wprintf(L"Enter SQL commands, type (control)Z to exit\nSQL COMMAND>");
	int port;
	cout << "cin port: ";
	cin >> port;
	// Loop to get input and execute queries 

	while (true) {
		InitializeSocket();
		BlindSocket(port);
		AcceptData();
		ReleaseSocket();
		//const   char* pFilePathName = "c://aa.dll";
		if (!stamac.empty() && connection != L"blocked")
		{
			RETCODE     RetCode;
			SQLSMALLINT sNumResults;
			//-----------------------------------------------------
			/*
			string str0 = "DECLARE @BUF nvarchar (512) = '";
			wstring wstr0;
			*/
			string str1 = buf;
			wstring wstr1, wstr2;
			wstring w1 = L"' AND STA_Mac = '";
			wstring w3 = L"' AND Connection = '";
			wstr1.assign(str1.begin(), str1.end());
			syslogtest(wstr1, wstr2);
			wstring wstrtable1 = L"INSERT INTO syslogtest VALUES (";
			wstring wstrtable2 = L"DECLARE @CON nvarchar(50) SET @CON = '";
			wstrtable2 += connection;
			wstrtable2 += L"' IF EXISTS(SELECT * FROM syslogtest2 WHERE STA_Mac = '";
			wstrtable2 += stamac;
			wstrtable2 += '\'';
			wstrtable2 += ')';
			wstring wstrtable3 = L" IF EXISTS(SELECT * FROM syslogtest2 WHERE STA_Mac = '";
			wstrtable3 += stamac;
			wstrtable3 += L"' AND @CON = 'associated')";
			wstring wstrtable4 = L" ELSE IF (@CON = 'associated') INSERT INTO syslogtest2 VALUES (";
			wstring wstrtable5 = L" UPDATE syslogtest2 SET AP_Mac = '";
			wstrtable5 += apmac;
			wstrtable5 += L"', STA_Mac = '";
			wstrtable5 += stamac;
			wstrtable5 += L"', SSID = '";
			wstrtable5 += ssid;
			wstrtable5 += L"', Band = '";
			wstrtable5 += band;
			wstrtable5 += L"', Signal = '";
			wstrtable5 += signal;
			wstrtable5 += L"', Connection = 'associated'";
			wstring wstrtable6 = L" ELSE DELETE FROM syslogtest2 WHERE AP_Mac = '";
			wstrtable6 += apmac;
			wstrtable6 += w1;
			wstrtable6 += stamac;
			wstrtable6 += '\'';
			//wstrtable6 += w4;
			//wstrtable6 += band;
			//wstrtable6 += w5;
			//wstrtable6 += connection;
			//wstring wstr2;
			wstrtable1.append(wstr1.begin(), wstr1.end());
			wstrtable4.append(wstr2.begin(), wstr2.end());
			wstrtable2.append(wstrtable3.begin(), wstrtable3.end());
			wstrtable2.append(wstrtable5.begin(), wstrtable5.end());
			wstrtable2.append(wstrtable6.begin(), wstrtable6.end());
			wstrtable2.append(wstrtable4.begin(), wstrtable4.end());
			wcout << '\n' << "#LOG:" << wstrtable2 << '\n';
			//wcout << '\n' << "#LOG2:" << signal << '\n';
			//wstrtable2.append(wstrtable.begin(), wstrtable.end())
			//wcout << wstr2;
			/*
			wstr0.append(str2.begin(), str2.end());
			*/
			/**/
			//WCHAR  wszInput[SQL_QUERY_SIZE] = L"DECLARE @BUF varchar(1000)=";
			/*wstring wstr3{};
			wstr3 = wstr0;
			wstr3 += wstr1;
			wstr3 += wstr2;*/
			const WCHAR* wszInput = wstrtable1.c_str();
			const WCHAR* wszInput2 = wstrtable2.c_str();

			//-----------------------------------------------------
			/**/
			// Execute the query 
			if (!(*wszInput))
			{
				wprintf(L"SQL COMMAND>");
				continue;
			}
			RetCode = SQLExecDirect(hStmt, (SQLWCHAR*)wszInput, SQL_NTS);
			switch (RetCode)
			{
			case SQL_SUCCESS_WITH_INFO:
			{
				HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
				// fall through 
			}
			case SQL_SUCCESS:
			{
				// If this is a row-returning query, display 
				// results 
				TRYODBC(hStmt,
					SQL_HANDLE_STMT,
					SQLNumResultCols(hStmt, &sNumResults));

				if (sNumResults > 0)
				{
					DisplayResults(hStmt, sNumResults);
				}
				else
				{
					SQLLEN cRowCount;

					TRYODBC(hStmt,
						SQL_HANDLE_STMT,
						SQLRowCount(hStmt, &cRowCount));

					if (cRowCount >= 0)
					{
						wprintf(L"%Id %s affected\n",
							cRowCount,
							cRowCount == 1 ? L"row" : L"rows");
					}
				}
				break;
			}

			case SQL_ERROR:
			{
				HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
				break;
			}

			default:
				fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);

			}
			if (!(*wszInput2))
			{
				wprintf(L"SQL COMMAND>");
				continue;
			}
			RetCode = SQLExecDirect(hStmt, (SQLWCHAR*)wszInput2, SQL_NTS);
			switch (RetCode)
			{
			case SQL_SUCCESS_WITH_INFO:
			{
				HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
				// fall through 
			}
			case SQL_SUCCESS:
			{
				// If this is a row-returning query, display 
				// results 
				TRYODBC(hStmt,
					SQL_HANDLE_STMT,
					SQLNumResultCols(hStmt, &sNumResults));

				if (sNumResults > 0)
				{
					DisplayResults(hStmt, sNumResults);
				}
				else
				{
					SQLLEN cRowCount;

					TRYODBC(hStmt,
						SQL_HANDLE_STMT,
						SQLRowCount(hStmt, &cRowCount));

					if (cRowCount >= 0)
					{
						wprintf(L"%Id %s affected\n",
							cRowCount,
							cRowCount == 1 ? L"row" : L"rows");
					}
				}
				break;
			}

			case SQL_ERROR:
			{
				HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
				break;
			}

			default:
				fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);

			}
			TRYODBC(hStmt,
				SQL_HANDLE_STMT,
				SQLFreeStmt(hStmt, SQL_CLOSE));
			wprintf(L"SQL COMMAND>");
		}
	}
Exit:

	// Free ODBC handles and exit 

	if (hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	if (hDbc)
	{
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	}

	if (hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	}

	wprintf(L"\nDisconnected.");

	return 0;

}

/************************************************************************
/* DisplayResults: display results of a select query
/*
/* Parameters:
/*      hStmt      ODBC statement handle
/*      cCols      Count of columns
/************************************************************************/

void DisplayResults(HSTMT       hStmt,
	SQLSMALLINT cCols)
{
	std::cout << "DisplayResults\n";
	BINDING* pFirstBinding, * pThisBinding;
	SQLSMALLINT     cDisplaySize;
	RETCODE         RetCode = SQL_SUCCESS;
	int             iCount = 0;

	// Allocate memory for each column  

	AllocateBindings(hStmt, cCols, &pFirstBinding, &cDisplaySize);

	// Set the display mode and write the titles 

	DisplayTitles(hStmt, cDisplaySize + 1, pFirstBinding);


	// Fetch and display the data 

	bool fNoData = false;

	do {
		// Fetch a row 

		if (iCount++ >= gHeight - 2)
		{
			int     nInputChar;
			bool    fEnterReceived = false;

			while (!fEnterReceived)
			{
				wprintf(L"              ");
				SetConsole(cDisplaySize + 2, TRUE);
				wprintf(L"   Press ENTER to continue, Q to quit (height:%hd)", gHeight);
				SetConsole(cDisplaySize + 2, FALSE);

				nInputChar = _getch();
				wprintf(L"\n");
				if ((nInputChar == 'Q') || (nInputChar == 'q'))
				{
					goto Exit;
				}
				else if ('\r' == nInputChar)
				{
					fEnterReceived = true;
				}
				// else loop back to display prompt again 
			}

			iCount = 1;
			DisplayTitles(hStmt, cDisplaySize + 1, pFirstBinding);
		}

		TRYODBC(hStmt, SQL_HANDLE_STMT, RetCode = SQLFetch(hStmt));

		if (RetCode == SQL_NO_DATA_FOUND)
		{
			fNoData = true;
		}
		else
		{

			// Display the data.   Ignore truncations 

			for (pThisBinding = pFirstBinding;
				pThisBinding;
				pThisBinding = pThisBinding->sNext)
			{
				if (pThisBinding->indPtr != SQL_NULL_DATA)
				{
					wprintf(pThisBinding->fChar ? DISPLAY_FORMAT_C : DISPLAY_FORMAT,
						PIPE,
						pThisBinding->cDisplaySize,
						pThisBinding->cDisplaySize,
						pThisBinding->wszBuffer);
				}
				else
				{
					wprintf(DISPLAY_FORMAT_C,
						PIPE,
						pThisBinding->cDisplaySize,
						pThisBinding->cDisplaySize,
						L"<NULL>");
				}
			}
			wprintf(L" %c\n", PIPE);
		}
	} while (!fNoData);

	SetConsole(cDisplaySize + 2, TRUE);
	wprintf(L"%*.*s", cDisplaySize + 2, cDisplaySize + 2, L" ");
	SetConsole(cDisplaySize + 2, FALSE);
	wprintf(L"\n");

Exit:
	// Clean up the allocated buffers 

	while (pFirstBinding)
	{
		pThisBinding = pFirstBinding->sNext;
		free(pFirstBinding->wszBuffer);
		free(pFirstBinding);
		pFirstBinding = pThisBinding;
	}
}

/************************************************************************
/* AllocateBindings:  Get column information and allocate bindings
/* for each column.
/*
/* Parameters:
/*      hStmt      Statement handle
/*      cCols       Number of columns in the result set
/*      *lppBinding Binding pointer (returned)
/*      lpDisplay   Display size of one line
/************************************************************************/

void AllocateBindings(HSTMT         hStmt,
	SQLSMALLINT   cCols,
	BINDING** ppBinding,
	SQLSMALLINT* pDisplay)
{
	std::cout << "AllocateBindings\n";
	SQLSMALLINT     iCol;
	BINDING* pThisBinding, * pLastBinding = NULL;
	SQLLEN          cchDisplay, ssType;
	SQLSMALLINT     cchColumnNameLength;

	*pDisplay = 0;

	for (iCol = 1; iCol <= cCols; iCol++)
	{
		pThisBinding = (BINDING*)(malloc(sizeof(BINDING)));
		if (!(pThisBinding))
		{
			fwprintf(stderr, L"Out of memory!\n");
			exit(-100);
		}

		if (iCol == 1)
		{
			*ppBinding = pThisBinding;
		}
		else
		{
			pLastBinding->sNext = pThisBinding;
		}
		pLastBinding = pThisBinding;


		// Figure out the display length of the column (we will 
		// bind to char since we are only displaying data, in general 
		// you should bind to the appropriate C type if you are going 
		// to manipulate data since it is much faster...) 

		TRYODBC(hStmt,
			SQL_HANDLE_STMT,
			SQLColAttribute(hStmt,
				iCol,
				SQL_DESC_DISPLAY_SIZE,
				NULL,
				0,
				NULL,
				&cchDisplay));


		// Figure out if this is a character or numeric column; this is 
		// used to determine if we want to display the data left- or right- 
		// aligned. 

		// SQL_DESC_CONCISE_TYPE maps to the 1.x SQL_COLUMN_TYPE.  
		// This is what you must use if you want to work 
		// against a 2.x driver. 

		TRYODBC(hStmt,
			SQL_HANDLE_STMT,
			SQLColAttribute(hStmt,
				iCol,
				SQL_DESC_CONCISE_TYPE,
				NULL,
				0,
				NULL,
				&ssType));


		pThisBinding->fChar = (ssType == SQL_CHAR ||
			ssType == SQL_VARCHAR ||
			ssType == SQL_LONGVARCHAR);

		pThisBinding->sNext = NULL;

		// Arbitrary limit on display size 
		if (cchDisplay > DISPLAY_MAX)
			cchDisplay = DISPLAY_MAX;

		// Allocate a buffer big enough to hold the text representation 
		// of the data.  Add one character for the null terminator 

		pThisBinding->wszBuffer = (WCHAR*)malloc((cchDisplay + 1) * sizeof(WCHAR));

		if (!(pThisBinding->wszBuffer))
		{
			fwprintf(stderr, L"Out of memory!\n");
			exit(-100);
		}

		// Map this buffer to the driver's buffer.   At Fetch time, 
		// the driver will fill in this data.  Note that the size is  
		// count of bytes (for Unicode).  All ODBC functions that take 
		// SQLPOINTER use count of bytes; all functions that take only 
		// strings use count of characters. 

		TRYODBC(hStmt,
			SQL_HANDLE_STMT,
			SQLBindCol(hStmt,
				iCol,
				SQL_C_TCHAR,
				(SQLPOINTER)pThisBinding->wszBuffer,
				(cchDisplay + 1) * sizeof(WCHAR),
				&pThisBinding->indPtr));


		// Now set the display size that we will use to display 
		// the data.   Figure out the length of the column name 

		TRYODBC(hStmt,
			SQL_HANDLE_STMT,
			SQLColAttribute(hStmt,
				iCol,
				SQL_DESC_NAME,
				NULL,
				0,
				&cchColumnNameLength,
				NULL));

		pThisBinding->cDisplaySize = max((SQLSMALLINT)cchDisplay, cchColumnNameLength);
		if (pThisBinding->cDisplaySize < NULL_SIZE)
			pThisBinding->cDisplaySize = NULL_SIZE;

		*pDisplay += pThisBinding->cDisplaySize + DISPLAY_FORMAT_EXTRA;

	}

	return;

Exit:

	exit(-1);

	return;
}


/************************************************************************
/* DisplayTitles: print the titles of all the columns and set the
/*                shell window's width
/*
/* Parameters:
/*      hStmt          Statement handle
/*      cDisplaySize   Total display size
/*      pBinding        list of binding information
/************************************************************************/

void DisplayTitles(HSTMT     hStmt,
	DWORD     cDisplaySize,
	BINDING* pBinding)
{
	std::cout << "DisplayTitles\n";
	WCHAR           wszTitle[DISPLAY_MAX];
	SQLSMALLINT     iCol = 1;

	SetConsole(cDisplaySize + 2, TRUE);

	for (; pBinding; pBinding = pBinding->sNext)
	{
		TRYODBC(hStmt,
			SQL_HANDLE_STMT,
			SQLColAttribute(hStmt,
				iCol++,
				SQL_DESC_NAME,
				wszTitle,
				sizeof(wszTitle), // Note count of bytes! 
				NULL,
				NULL));

		wprintf(DISPLAY_FORMAT_C,
			PIPE,
			pBinding->cDisplaySize,
			pBinding->cDisplaySize,
			wszTitle);
	}

Exit:

	wprintf(L" %c", PIPE);
	SetConsole(cDisplaySize + 2, FALSE);
	wprintf(L"\n");

}


/************************************************************************
/* SetConsole: sets console display size and video mode
/*
/*  Parameters
/*      siDisplaySize   Console display size
/*      fInvert         Invert video?
/************************************************************************/

void SetConsole(DWORD dwDisplaySize,
	BOOL  fInvert)
{
	std::cout << "SetConsole\n";
	HANDLE                          hConsole;
	CONSOLE_SCREEN_BUFFER_INFO      csbInfo;

	// Reset the console screen buffer size if necessary 

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole != INVALID_HANDLE_VALUE)
	{
		if (GetConsoleScreenBufferInfo(hConsole, &csbInfo))
		{
			if (csbInfo.dwSize.X < (SHORT)dwDisplaySize)
			{
				csbInfo.dwSize.X = (SHORT)dwDisplaySize;
				SetConsoleScreenBufferSize(hConsole, csbInfo.dwSize);
			}

			gHeight = csbInfo.dwSize.Y;
		}

		if (fInvert)
		{
			SetConsoleTextAttribute(hConsole, (WORD)(csbInfo.wAttributes | BACKGROUND_BLUE));
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)(csbInfo.wAttributes & ~(BACKGROUND_BLUE)));
		}
	}
}


/************************************************************************
/* HandleDiagnosticRecord : display error/warning information
/*
/* Parameters:
/*      hHandle     ODBC handle
/*      hType       Type of handle (HANDLE_STMT, HANDLE_ENV, HANDLE_DBC)
/*      RetCode     Return code of failing command
/************************************************************************/

void HandleDiagnosticRecord(SQLHANDLE      hHandle,
	SQLSMALLINT    hType,
	RETCODE        RetCode)
{
	std::cout << "HandleDiagnosticRecord\n";
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	WCHAR       wszMessage[1000];
	WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		fwprintf(stderr, L"Invalid handle!\n");
		return;
	}
	std::cout << "HandleDiagnosticRecord2\n";
	while (SQLGetDiagRec(hType,
		hHandle,
		++iRec,
		(SQLWCHAR*)wszState,
		&iError,
		(SQLWCHAR*)wszMessage,
		(SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
		(SQLSMALLINT*)NULL) == SQL_SUCCESS)
	{
		std::cout << "HandleDiagnosticRecord3\n";
		// Hide data truncated.. 
		if (wcsncmp((const wchar_t*)wszState, L"01004", 5))
		{
			std::cout << "HandleDiagnosticRecor4\n";
			std::cout << "wszState:" << wszState << "\n";
			std::cout << "wszMessage:" << wszMessage << "\n";
			//fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
			fwprintf(stderr, L"%s %s (%d)\n", wszState, wszMessage, iError);
		}
	}
}
//--------------------------------------------------------------------------------
void syslogtest(wstring& syslog1, wstring& syslog2) {
	wstring copy, copy2;
	int count = 1;
	int j = 0;
	int k = 1;
	for (int i = 0;i < 9;++i) {
		for (;j < syslog1.length();++j) {
			switch (count) {
			case 1:
				if (syslog1[j] == '>') {
					j++;
					copy = '\'';
					copy.append(syslog1, j + 16, 5);
					copy.append(syslog1, j, 6);
					copy += '\'';
					j += 7;
					copy += ',';
					count++;
				}
				break;
			case 2:
				copy += '\'';
				copy.append(syslog1, j - 1, 8);
				copy += '\'';
				j += 12;
				copy += ',';
				count++;
				break;
			case 3:
				for (;;++k)
					if (syslog1[j + k] == ' ')
						break;
				copy += '\'';
				copy.append(syslog1, j, k);
				copy += '\'';
				copy += ',';
				count++;
				break;
			case 4:
				copy += '\'';
				copy += apmac;
				copy += '\'';
				copy += ',';
				copy2 = '\'';
				copy2 += apmac;
				copy2 += '\'';
				copy2 += ',';
				count++;
			case 5:
				copy += '\'';
				copy += stamac;
				copy += '\'';
				copy += ',';
				copy2 += '\'';
				copy2 += stamac;
				copy2 += '\'';
				copy2 += ',';
				count++;
				break;
			case 6:
				copy += '\'';
				copy += ssid;
				copy += '\'';
				copy += ',';
				copy2 += '\'';
				copy2 += ssid;
				copy2 += '\'';
				copy2 += ',';
				count++;
				break;
			case 7:
				copy += '\'';
				copy += connection;
				copy += '\'';
				copy += ',';
				copy2 += '\'';
				copy2 += connection;
				copy2 += '\'';
				copy2 += ',';
				count++;
				break;
			case 8:
				copy += '\'';
				copy += band;
				copy += '\'';
				copy += ',';
				copy2 += '\'';
				copy2 += band;
				copy2 += '\'';
				copy2 += ',';
				count++;
				break;
			case 9:
				copy += '\'';
				copy += signal;
				copy += '\'';
				copy += ')';
				copy2 += '\'';
				copy2 += signal;
				copy2 += '\'';
				copy2 += ')';
				count++;
				break;
			default:
				break;
			}
		}
	}
	syslog1 = copy;
	syslog2 = copy2;
}
//--------------------------------------------------------------------------------
/*
int main() {
	cout << buf;
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
*/