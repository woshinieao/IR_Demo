//#pragma once;

#include "IRStream.h"

IR_API long IR_Create(long handle, int port, char* ip , CBF_IR cbf_stm , CBF_IR cbf_cmd , long param );
IR_API long IR_Command(long handle, eCommand command);
IR_API long IR_Destroy(long handle);

IR_API CIRStream* CreateIRStream();
IR_API void DestroyIRStream(CIRStream* pIRStream);