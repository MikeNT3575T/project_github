#ifndef BUF_SIZE
#define BUF_SIZE 512
#include <iostream>
using namespace std;
extern char buf[];
extern wstring apmac;
extern wstring stamac;
extern wstring mesg;
extern int count;
void InitializeSocket();
void BlindSocket(int p);
void AcceptData();
void ReleaseSocket(void);
#endif // !1