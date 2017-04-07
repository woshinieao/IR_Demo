#include "IRStream.h"
#include "stdio.h"
#include "math.h"
/*
void _trace(TCHAR* format, ...)
{
	TCHAR buffer[1000];
	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);
	OutputDebugString(buffer);
}
*/
UINT16 LineAck(UINT16 Linenum, UINT32 Framenum, long lParameter)
{
	CIRStream* pIRStream = (CIRStream*)lParameter;
	char command[14] = {'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x41', '\x43', '\x4b', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',};
	UINT16 i;

	command[8] = Linenum & 0xff;
	command[9] = (Linenum >> 8) & 0xff;
	command[10] = Framenum & 0xff;
	command[11] = (Framenum >> 8) & 0xff;
	command[12] = (Framenum >> 16) & 0xff;
	command[13] = (Framenum >> 24) & 0xff;

	for(i=0; i<1; i++)
	{
		command[4] = i+1;
		pIRStream->Command((char*)(&(command[0])), 14);
	}
	return 0;
}

long LineCheckSum(UINT8 *recvbuffer, USHORT length)
{
	UINT32 sum_check = 0;
	UINT32 pos_check = 0;
	UINT32 check = 0;
	UINT32 local_check = 0;
	UINT16 i;

	for(i=0; i < length - 5; i += 2)
	{
		sum_check += (UINT16)((recvbuffer[i] << 8) | recvbuffer[i+1]);
		pos_check += ((UINT16)(((recvbuffer[i] << 8) | recvbuffer[i+1]) ^ i));
	}

	sum_check = (sum_check & 0xffff);
	pos_check = (pos_check & 0xffff);
	local_check = (sum_check << 16) | pos_check;

	check = (recvbuffer[length-4] << 16) | (recvbuffer[length-3] << 24) | (recvbuffer[length-2] << 0) | (recvbuffer[length-1] << 8);

	if (local_check + check == 0xffffffff)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
#if 1

long LineReceive(char recvbuffer[], long lParameter)
{
#define BUFFER_NUM	5

	CIRStream* pIRStream = (CIRStream*)lParameter;
	WORD line = ((WORD)((BYTE)recvbuffer[0] | (BYTE)recvbuffer[1] << 8));
	UINT32 CurframeNum = (UINT32)((BYTE)recvbuffer[9] | ((BYTE)recvbuffer[10] << 8) | ((BYTE)recvbuffer[11] << 16) | ((BYTE)recvbuffer[12] << 24));
	UINT16 u16Width = ((WORD)((BYTE)recvbuffer[4] | (BYTE)recvbuffer[5] << 8));
//	UINT16 u16Hight = ((WORD)((BYTE)recvbuffer[6] | (BYTE)recvbuffer[7] << 8));

	static UINT32 FrameNum[BUFFER_NUM] = {0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,}; //存帧号
	static UINT16 LineCnt[BUFFER_NUM] = {0x0,0x0,0x0,0x0,0x0,};		//行计数
	static Frame *FrameBuf[BUFFER_NUM] = {NULL,NULL,NULL,NULL,NULL,};
	UINT8  u8Index;
	UINT8  u8SendIndex = 0xff;
	UINT32 FrameLast1Num;
	UINT32 FrameLast2Num;
	UINT32 FrameLast3Num;
	UINT32 FrameLast1Index;
	UINT32 FrameLast2Index;
	UINT32 FrameLast3Index;
	static UINT32 LastSendFrame = 0xffffffff;

	FILE *filelog;
	char Str[100] = {'\0',};

#if NEED_CHECKSUM
	if (0 == LineCheckSum((UINT8 *)(&recvbuffer[0]),86+ u16Width*sizeof(UINT16)+ 4))
	{
		//filelog = fopen("C:\\Demo_log.txt","a+");
		//fwrite("SUM CHECK ERR!\n", sizeof(CHAR), strlen("SUM CHECK ERR!\n"), filelog);
		//fclose(filelog);
		return 1;
	}
#endif
	u8Index = CurframeNum % BUFFER_NUM;

	if (FrameNum[u8Index] != CurframeNum) //新的一帧
	{
		LineCnt[u8Index] = 0;
		FrameNum[u8Index] = CurframeNum;
		if (FrameBuf[u8Index] != NULL)
		{
			delete FrameBuf[u8Index];
			FrameBuf[u8Index] = NULL;
		}
		FrameBuf[u8Index] = new Frame;
		FrameBuf[u8Index]->u16FpaTemp = (WORD)((BYTE)recvbuffer[2] | ((BYTE)recvbuffer[3] << 8));
		FrameBuf[u8Index]->width  = (WORD)((BYTE)recvbuffer[4] | ((BYTE)recvbuffer[5] << 8));
		FrameBuf[u8Index]->height = (WORD)((BYTE)recvbuffer[6] | ((BYTE)recvbuffer[7] << 8));
		FrameBuf[u8Index]->u8SensorType = recvbuffer[8];
	}

	LineCnt[u8Index]++;

	memmove(&(FrameBuf[u8Index]->buffer[line * FrameBuf[u8Index]->width]), &recvbuffer[86], sizeof(USHORT) * FrameBuf[u8Index]->width);

	if ((LineCnt[u8Index] == FrameBuf[u8Index]->height) && (CurframeNum >= 2))
	{
		FrameLast1Num = CurframeNum - 1;
		FrameLast2Num = CurframeNum - 2;
		FrameLast1Index = FrameLast1Num % BUFFER_NUM;
		FrameLast2Index = FrameLast2Num % BUFFER_NUM;

		if ((FrameNum[FrameLast2Index] == 0xffffffff) || ((FrameNum[FrameLast2Index] == FrameLast2Num) && (LineCnt[FrameLast2Index] != FrameBuf[FrameLast2Index]->height))) //如果前面第2帧还未存满，则删掉
		{
			if ((FrameNum[FrameLast2Index] == FrameLast2Num) && (LineCnt[FrameLast2Index] != FrameBuf[FrameLast2Index]->height)) //帧未存满
			{
				delete FrameBuf[FrameLast2Index];
				FrameBuf[FrameLast2Index] = NULL;
				FrameNum[FrameLast2Index] = 0xffffffff;
			}
			if ((FrameNum[FrameLast1Index] == FrameLast1Num) && (LineCnt[FrameLast1Index] == FrameBuf[FrameLast1Index]->height))//如果上一帧已经装满，则发送上一帧
			{
				CurframeNum = FrameLast1Num;
				u8SendIndex = FrameLast1Index;
			}
			else if (FrameNum[FrameLast1Index] == FrameLast1Num) //上一帧未满，等待
			{
				return 1;
			}
			else if (FrameNum[FrameLast1Index] == 0xffffffff) //上一帧已发送
			{
				u8SendIndex = u8Index;
			}
		}
		else if ((FrameNum[FrameLast2Index] == FrameLast2Num) && (LineCnt[FrameLast2Index] == FrameBuf[FrameLast2Index]->height))//如果前面第2帧存满，则发送
		{
			CurframeNum = FrameLast2Num;
			u8SendIndex = FrameLast2Index;
		}
	}
	else if (CurframeNum >= 3) //当新的一帧到来时，看前面第三帧是否满，不满的话就丢掉，满的话则发送出去
	{
		FrameLast3Num = CurframeNum - 3;
		FrameLast3Index = FrameLast3Num % BUFFER_NUM;
		if ((FrameNum[FrameLast3Index] == FrameLast3Num) && (LineCnt[FrameLast3Index] == FrameBuf[FrameLast3Index]->height))//如果前面第三帧已满，则先发送出去
		{
			CurframeNum = FrameLast3Num;
			u8SendIndex = FrameLast3Index;
		}
		else if (FrameNum[FrameLast3Index] == FrameLast3Num)
		{
			delete FrameBuf[FrameLast3Index];
			FrameBuf[FrameLast3Index] = NULL;
			FrameNum[FrameLast3Index] = 0xffffffff;
			return 1;
		}
	}

	if (u8SendIndex != 0xff)//发送
	{
		//log 
		if (CurframeNum != LastSendFrame + 1)
		{
            filelog = fopen("Demo_log.txt","a+");
			sprintf(Str,"lastFrameNum = %d  currFrameNum = %d\n", LastSendFrame, CurframeNum);
			fwrite(Str, sizeof(char), strlen(Str), filelog);
			fclose(filelog);
		}

		LastSendFrame = CurframeNum;

		pIRStream->pFrame = FrameBuf[u8SendIndex];
		pIRStream->StreamCallback((long)pIRStream->pFrame, pIRStream->parameter);
		delete pIRStream->pFrame;
		pIRStream->pFrame = NULL;
		FrameBuf[u8SendIndex] = NULL;
		FrameNum[u8SendIndex] = 0xffffffff;
		LineCnt[u8SendIndex] = 0;
	}

	return 1;
}
#else
long LineReceive(char recvbuffer[], long lParameter)
{
	static WORD lastline = 0;
	CIRStream* pIRStream = (CIRStream*)lParameter;
	WORD line = ((WORD)((BYTE)recvbuffer[0] | (BYTE)recvbuffer[1] << 8));
	UINT32 CurframeNum = (UINT32)((BYTE)recvbuffer[9] | ((BYTE)recvbuffer[10] << 8) | ((BYTE)recvbuffer[11] << 16) | ((BYTE)recvbuffer[12] << 24));
	UINT16 u16Width = ((WORD)((BYTE)recvbuffer[4] | (BYTE)recvbuffer[5] << 8));

	if (line >= 0)
	{
		if (line == 0)
		{
			pIRStream->pFrame = new Frame;
			pIRStream->pFrame->u16FpaTemp = (WORD)((BYTE)recvbuffer[2] | ((BYTE)recvbuffer[3] << 8));
			pIRStream->pFrame->width  = (WORD)((BYTE)recvbuffer[4] | ((BYTE)recvbuffer[5] << 8));
			pIRStream->pFrame->height = (WORD)((BYTE)recvbuffer[6] | ((BYTE)recvbuffer[7] << 8));
			pIRStream->pFrame->u8SensorType = recvbuffer[8];
		}

		else if (line - lastline != 1)
		{
			delete pIRStream->pFrame;
			pIRStream->pFrame = NULL;
		}

		if (pIRStream->pFrame)
		{
			memmove(&(pIRStream->pFrame->buffer[line * pIRStream->pFrame->width]), &recvbuffer[86], sizeof(USHORT) * pIRStream->pFrame->width);

			if (line == pIRStream->pFrame->height - 1)
			{
				pIRStream->StreamCallback((long)pIRStream->pFrame, pIRStream->parameter);
				delete pIRStream->pFrame;
				pIRStream->pFrame = NULL;
			}
		}
		lastline = line;
	}
	return 1;
}
#endif

long CommandReceive(char recvbuffer[], long lParameter)
{
	CIRStream* pIRStream = (CIRStream*)lParameter;
    printf("tttttttttttttttttttttt          \n");
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
printf(" 1111111111111 aaaaaaaaaaaaaaaaaaa\n");
        printf("CIRStream    port:%d\n",port);
		pIRConnect = new CIRConnect;
		pIRConnect->Bind(port, ip, LineReceive, (long)this);
		StreamCallback = cbf_stm;
	}
	if (ip)
	{
        printf(" 1111111111111 bbbbbbbbbbbbbbbbbbbb\n");
		pIRCommand = new CIRConnect;
        pIRCommand->Bind(port+1, ip, CommandReceive, (long)this);
		CommandCallback = cbf_cmd;

	}
	parameter = param;
	return true;
}
bool CIRStream::Command(eCommand command)
{
	char COMMAND[][14] = {
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x11', '\x96', '\x00', '\x04', '\x00', '\x00', '\x00', '\x01'},//数字视频开
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x11', '\x96', '\x00', '\x04', '\x00', '\x00', '\x00', '\x00'},//数字视频关
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x10', '\x3f', '\x00', '\x04','\x00', '\x00','\x00', '\x01'}, //快门
		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x11', '\x75', '\x00', '\x04', '\x43', '\x4f', '\x4e', '\x4e'}//链接命令

	};
	return Command(COMMAND[command], 14);
}
bool CIRStream::Command(char* command, int length)
{
	return pIRCommand ? pIRCommand->Send(command, length) : false;
}
IpAddr CIRStream::IpAddrInqure()
{
	ipAddrInfo.DeviceIp = (UCHAR *)inet_ntoa(pIRConnect->addrfrom.sin_addr);

	return ipAddrInfo; 
}
//bool CIRStream::CfgIpAddr(int ipaddr)
//
//	char COMMAND[14] = 
//		{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x00', '\xca', '\x00', '\x04',};
//
//	COMMAND[13] = ipaddr & 0xff;
//	COMMAND[12] = (ipaddr >> 8) & 0xff;
//	COMMAND[11] = (ipaddr >> 16) & 0xff;
//	COMMAND[10] = (ipaddr >> 24) & 0xff;
//	return pIRCommand ? pIRCommand->Send(COMMAND, 14) : false;
//}
//
//bool CIRStream::SaveIpAddr(void)
//{
//	char COMMAND[14] = 
//	{'\xaa', '\xaa', '\xaa', '\xaa', '\x00', '\x00', '\x00', '\xca', '\x00', '\x04','\x00', '\x00','\x00', '\x04',};
//
//	return pIRCommand ? pIRCommand->Send(COMMAND, 14) : false;
//}


