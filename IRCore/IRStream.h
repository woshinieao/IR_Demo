
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

//#pragma once

#include "IRConnect.h"

#define IR_API 

#define MAX_COUNT	(640*500*2)


#define NEED_CHECKSUM	1

/*
1字节     uint8_t
2字节     uint16_t
4字节     uint32_t
8字节     uint64_t
*/

typedef	unsigned short USHORT;
typedef unsigned char  UCHAR;
typedef unsigned int UINT;
typedef uint8_t  UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;



typedef struct tagFrame
{
    USHORT buffer[MAX_COUNT];
	USHORT width;
	USHORT height;
	USHORT u16FpaTemp; //焦面温度随图像数据一起上传
	UINT8  u8SensorType; //探测器类型随图像数据一起上传
} Frame;

typedef struct tagIpAddr
{
	UCHAR *DeviceIp;
	UCHAR *ServerIp;
} IpAddr;

typedef long (*CBF_IR)(long lData, long lParam);

class CIRStream
{
public:
	CIRStream(void);
	virtual ~CIRStream(void);
	virtual bool Init(int port, CBF_IR cbf, long param = 0);
    virtual bool Init(int port, char* ip, CBF_IR cbf_stm, CBF_IR cbf_cmd, CBF_IR cbf_cfg, long param = 0);
    virtual bool Command( int cmd, int param);
    virtual bool Send( char* command, int length);
   virtual bool Config( char* command, int length);
	virtual IpAddr IpAddrInqure();

	UINT8  u8SensorType;
	Frame* pFrame;
	CBF_IR StreamCallback;
	CBF_IR CommandCallback;
    CBF_IR ConfigCallback;
	long parameter;
	IpAddr		ipAddrInfo;
protected:
	CIRConnect* pIRConnect;
	CIRConnect* pIRCommand;
    CIRConnect* pIRConfig;
};

