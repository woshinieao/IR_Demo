/*
#pragma once;

#include <Winsock2.h>
#include <Windows.h>
#include <intrin.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
*/
#ifndef _IRCONNECT_T
#define _IRCONNECT_T

#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>


typedef  int	SOCKET;
typedef  void * HANDLE;

typedef	unsigned char USHORT;
typedef unsigned int DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;


#define BUFF_LEN	2048

typedef long (*CBF_IRConnect)(char recvbuffer[], long lParameter);

class CIRConnect
{
public:
	CIRConnect(void);
	virtual ~CIRConnect(void);
	virtual	bool Bind(short port, char* ip = NULL);
	virtual	bool Bind(short port, CBF_IRConnect cbf, long param );
	virtual	bool Bind(short port, char* ip , CBF_IRConnect cbf, long param );
	bool Send(char* command, int length);
	bool Close();
	bool run;
	CBF_IRConnect callback;
	long parameter;
	SOCKET socket;
private:
	HANDLE handle;
	struct sockaddr_in	address;
};

#endif