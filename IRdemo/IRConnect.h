#ifndef _IRCONNECT_H
#define _IRCONNECT_H
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// Create Date:		09:49:25 06/08/2016 
// Design Name: 
// Description: 
// Revision:		1.100 - File Created
// Additional Comments: 
// 
//////////////////////////////////////////////////////////////////////////////////


/*
#pragma once;

#include <Winsock2.h>
#include <Windows.h>
#include <intrin.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
*/


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

typedef unsigned long DWORD;
typedef int BOOL;
typedef  char BYTE;
typedef unsigned short WORD;


#define BUFF_LEN	1400

typedef long (*CBF_IRConnect)(char recvbuffer[], long lParameter);

class CIRConnect
{
public:
	CIRConnect(void);
	virtual ~CIRConnect(void);
	int CreateConnect(SOCKET* pSocket, int port, struct sockaddr_in* address);
	virtual	bool Bind(short port, char* ip = NULL);
	virtual	bool Bind(short port, CBF_IRConnect cbf, long param = 0);
	virtual	bool Bind(short port, char* ip , CBF_IRConnect cbf, long param = 0);
	bool Send( char* command, int length);
	bool Close();
	bool run;
	CBF_IRConnect callback;
	long parameter;
	SOCKET socket;
	struct sockaddr_in addrfrom;
    struct sockaddr_in	addSrv;

		
private:
	HANDLE handle;

};
#endif
