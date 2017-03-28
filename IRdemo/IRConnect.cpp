#include "IRConnect.h"




int CreateConnect(SOCKET* pSocket, int port)
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



	*pSocket = socket(AF_INET, SOCK_DGRAM, 0);
	printf("+++++++++++++	%d\n",*pSocket);

	struct sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(*pSocket, (struct sockaddr *)&addrSrv, sizeof(struct sockaddr_in)) == -1)
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
	memset(recvbuffer, 0 , BUFF_LEN);
	while (pIRConnect->run == true)
	{
	printf("111111111111111111111111111  %d\n",pIRConnect->socket);
	struct sockaddr_in	addressl;
	socklen_t len = sizeof(struct sockaddr);
	int ret = recvfrom(pIRConnect->socket,recvbuffer,BUFF_LEN,0, (struct sockaddr *)&addressl, &len);
	perror("recvfrom err:");
	if(ret>=0)
	//	if (recv(pIRConnect->socket, recvbuffer, BUFF_LEN, 0) >=0)
		{
		printf("aaaaaaaaaaaaa %s \n",recvbuffer);	
			if (pIRConnect->run == true) pIRConnect->callback(recvbuffer, pIRConnect->parameter);
		}
		else sleep(1);
	}
	return (void *)0;
}

CIRConnect::CIRConnect(void)
	: run(false)
	, parameter(0)
{
	callback = NULL;
	handle = NULL;
	memset(&address, 0, sizeof(struct sockaddr_in));
}
CIRConnect::~CIRConnect(void)
{
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

	if (!CreateConnect(&socket, port)) return false;
	if (ip)
	{
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = inet_addr(ip);
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
printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
	pthread_create(&ThreadID,NULL,ReceiveProcess,(void *)this);
	printf("bbbbbbbbbbbbbbbbb\n");
#endif	
	}
	return true;
}
bool CIRConnect::Send(char* command, int length)
{
	if (!address.sin_family) return false;
	int sockflag = sizeof(struct sockaddr_in);
	sendto(socket, command, length, 0, (struct sockaddr *)&address, sockflag);
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
