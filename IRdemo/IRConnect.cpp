#include "IRConnect.h"

int CIRConnect::CreateConnect(SOCKET* pSocket, int port, struct sockaddr_in* addr)
{

#ifdef WIN32
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return false;
	}
	if (*pSocket)
	{
		closesocket(*pSocket);
		*pSocket = NULL;
	}
#else
	if (*pSocket)
	{
		close(*pSocket);
		*pSocket = -1;
	}
#endif	



	*pSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);

    printf("2222222222222  CreateConnect      Socket :%d  port:%d\n",*pSocket,addr->sin_port );

	addr->sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(*pSocket, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) == -1)
		return false;
	else
	{
		int nRecvBuf = 1024 * 1024 * 512;
		setsockopt(*pSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
#ifdef WIN32
		DWORD flag = 0;
		if (ioctlsocket(*pSocket, FIONBIO, &flag) != 0)
		{
			closesocket(*pSocket);
			return false;
		}
#else
		int flags=0;
		flags = fcntl(*pSocket, F_GETFL);
		flags |= O_NONBLOCK;
		if (fcntl(*pSocket, F_SETFL, flags) == -1)
		{
			close(*pSocket);
			return false;
		}
#endif	
	
	}
	return true;
}
void *ReceiveProcess(void *lpParameter)
{
	CIRConnect* pIRConnect = (CIRConnect*)lpParameter;
	char recvbuffer[BUFF_LEN];
	sockaddr_in addrRev;
	int len = sizeof(sockaddr);

	memset(recvbuffer, 0 , BUFF_LEN);
	while (pIRConnect->run == true)
	{
		int retRcv = recvfrom(pIRConnect->socket, recvbuffer, BUFF_LEN, 0, (struct sockaddr *)(&addrRev), (socklen_t*)&len);

		if(retRcv >= 0)
		{
            if(addrRev.sin_addr.s_addr == pIRConnect->addrfrom.sin_addr.s_addr)//¹ýÂËIP
			{
				if (pIRConnect->run == true) pIRConnect->callback(recvbuffer, pIRConnect->parameter);
			}
            else sleep(2);
		}
		
	}
	return (void *)0;
}
CIRConnect::CIRConnect(void )
	: run(false)
	, parameter(0)
{
	callback = NULL;
	handle = NULL;
	memset(&addrfrom, 0, sizeof(struct sockaddr_in));
}
CIRConnect::~CIRConnect(void)
{
	;
}

bool CIRConnect::Bind(short port, char* ip)
{
	return Bind(port, ip, NULL, 0);
}
bool CIRConnect::Bind(short port, CBF_IRConnect cbf, long param)
{
	return Bind(port, NULL, cbf, param);
}
bool CIRConnect::Bind(short port, char* ip, CBF_IRConnect cbf, long param)
{
	if (!CreateConnect(&socket, port,&addSrv)) return false;
	if (ip)
	{
        addrfrom.sin_family = AF_INET;
        addrfrom.sin_port = htons(port);
       printf(" 333333333333333  CIRConnect socket:%d bind :%d\n ",socket,addrfrom.sin_port);
        addrfrom.sin_addr.s_addr = inet_addr(ip);
	}
	if (cbf)
	{
		callback = cbf;
		parameter = param;
		run = true;
		
#ifdef WIN32
		DWORD ThreadID;
		handle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ReceiveProcess, (LPVOID)this, 1, &ThreadID);
		CloseHandle(handle);
#else	
		pthread_t ThreadID;
    pthread_create(&ThreadID,NULL,ReceiveProcess,this);
#endif	
	}
    //addrfrom = address;
	return true;
}
bool CIRConnect::Send(unsigned char* command, int length)
{
	if (!addrfrom.sin_family) return false;
	int sockflag = sizeof(struct sockaddr_in);
    printf(" 444444444444444      send  socket:%d :port:%d address:%s  command:%s\n",socket,addrfrom.sin_port,inet_ntoa(addrfrom.sin_addr),command);
	sendto(socket, command, length, 0, (struct sockaddr *)&addrfrom, sockflag);
	return true;
}
bool CIRConnect::Close()
{
	run = false;
#ifdef WIN32	
	closesocket(socket);
	socket = NULL;
	if (handle) WaitForSingleObject(handle, 100);
#else
	close(socket);
	socket = -1;
#endif	
	return true;
}
