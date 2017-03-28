#include "IRStream.h"

long LineReceive(char recvbuffer[], long lParameter)
{
	static long total = 0;
	CIRStream* pIRStream = (CIRStream*)lParameter;
	WORD line = (BYTE)recvbuffer[0] + (BYTE)recvbuffer[1] * 256;
	if (line >= 0)
	{
		if (line == 0)
		{
			total = 0;
			pIRStream->pFrame = new Frame;
			pIRStream->pFrame->width  = (BYTE)recvbuffer[4] + (BYTE)recvbuffer[5] * 256;
			pIRStream->pFrame->height = (BYTE)recvbuffer[6] + (BYTE)recvbuffer[7] * 256;
		}
		if (pIRStream->pFrame)
		{
			total += line;			
			memmove(&(pIRStream->pFrame->buffer[line * pIRStream->pFrame->width]), &recvbuffer[86], sizeof(USHORT) * pIRStream->pFrame->width);
			if (line == pIRStream->pFrame->height - 1)
			{
				if (total - (pIRStream->pFrame->height - 1) * pIRStream->pFrame->width / 2 == 0)
					pIRStream->StreamCallback((long)pIRStream->pFrame, pIRStream->parameter);
				else
				{
					delete pIRStream->pFrame;
					pIRStream->pFrame = NULL;
				}
			}
		}
	}
	return 1;
}
long CommandReceive(char recvbuffer[], long lParameter)
{
	CIRStream* pIRStream = (CIRStream*)lParameter;
	if (pIRStream->CommandCallback)
	{
		pIRStream->CommandCallback((long)recvbuffer, pIRStream->parameter);
	}
	return 1;
}
CIRStream::CIRStream(void)
	: parameter(0)
{
	pFrame = NULL;
	pIRConnect = NULL;
	pIRCommand = NULL;
	StreamCallback = NULL;
	CommandCallback = NULL;
}
CIRStream::~CIRStream(void)
{
	if (pIRConnect)
	{
		pIRConnect->Close();
		delete pIRConnect;
		pIRConnect = NULL;
	}
	if (pIRCommand)
	{
		pIRCommand->Close();
		delete pIRCommand;
		pIRCommand = NULL;
	}
	if (pFrame)
	{
		delete pFrame;
		pFrame = NULL;
	}
}
bool CIRStream::Init(int port, CBF_IR cbf, long param)
{
	return Init(port, NULL, cbf, NULL, param);
}
bool CIRStream::Init(int port, char* ip, CBF_IR cbf_stm, CBF_IR cbf_cmd, long param)
{
	if (port)
	{
		pIRConnect = new CIRConnect;
		pIRConnect->Bind(port, ip, LineReceive, (long)pIRConnect);
		StreamCallback = cbf_stm;
	}
	if (ip)
	{
		pIRCommand = new CIRConnect;
		pIRCommand->Bind(port + 1, ip, CommandReceive, (long)pIRConnect);
		CommandCallback = cbf_cmd;
	}
	parameter = param;
	return true;
}
bool CIRStream::Command(eCommand command)
{
	char COMMAND[][14] = {
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x03', '\xe8', '\x00', '\x04', '\x00', '\x00', '\x00', '\x01'},
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x03', '\xe8', '\x00', '\x04', '\x00', '\x00', '\x00', '\x00'},
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x00', '\x49', '\x00', '\x04', '\x00', '\x00', '\x00', '\x01'},
	};
	return Command(COMMAND[command], 14);
}
bool CIRStream::Command(char* command, int length)
{
	return pIRCommand ? pIRCommand->Send(command, length) : false;
}