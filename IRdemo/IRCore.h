
#ifndef _IRCORE_H
#define _IRCORE_H

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

//#pragma once;



#include "IRStream.h"

IR_API long IR_Create(long handle, int port, char* ip = NULL, CBF_IR cbf_stm = NULL, CBF_IR cbf_cmd = NULL, CBF_IR cbf_cfg = NULL, long param = 0);
IR_API long IR_Command(long handle, int command, int param);
IR_API long IR_Send(long handle,char *command, int len);
IR_API long IR_Destroy(long handle);
IR_API long IR_Inqure(long handle);

IR_API CIRStream* CreateIRStream();
IR_API void DestroyIRStream(CIRStream* pIRStream);
#endif
