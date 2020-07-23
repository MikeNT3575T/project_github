#ifndef BUF_SIZE
#define BUF_SIZE 512
extern char buf[];
extern int count;
void InitializeSocket();
void BlindSocket(int p);
void AcceptData();
void ReleaseSocket(void);
#endif // !1
#include <iostream>
using namespace std;
