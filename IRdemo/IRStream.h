//#pragma once


#ifndef _IRSTREAM_H
#define _IRSTREAM_H

#include "IRConnect.h"
#ifdef WIN32
#define IR_API extern "C" _declspec(dllexport)
#else
#define IR_API 
#endif

#define MAX_WIDTH	640
#define MAX_HEIGHT	480
#define MAX_COUNT	MAX_WIDTH * MAX_HEIGHT


typedef enum enumCommand
{
	COMMAND_PLAY,
	COMMAND_STOP,
	COMMAND_CALIBRATE,
} eCommand;

typedef struct tagFrame
{
	USHORT buffer[MAX_COUNT];
	USHORT width;
	USHORT height;
} Frame;

typedef long (*CBF_IR)(long lData, long lParam);

class CIRStream
{
public:
	CIRStream(void);
	virtual ~CIRStream(void);
	virtual bool Init(int port, CBF_IR cbf, long param = 0);
	virtual bool Init(int port, char* ip, CBF_IR cbf_stm, CBF_IR cbf_cmd, long param = 0);
	virtual bool Command(eCommand command);
	virtual bool Command(char* command, int length);

	Frame* pFrame;
	CBF_IR StreamCallback;
	CBF_IR CommandCallback;
	long parameter;
protected:
	CIRConnect* pIRConnect;
	CIRConnect* pIRCommand;
};


#endif
