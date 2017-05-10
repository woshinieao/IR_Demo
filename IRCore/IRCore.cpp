#include "IRCore.h"

#define DEVICE_COUNT 16
long m_hIRStream[DEVICE_COUNT] = { 0 };



IR_API long IR_Create(long handle, int port, char* ip, CBF_IR cbf_stm, CBF_IR cbf_cmd, CBF_IR cbf_cfg, long param)
{
	unsigned int rvalue = 0;
	if (handle >= DEVICE_COUNT)	return 0;
	if (m_hIRStream[handle]) 
	{
		rvalue = 2;
		IR_Destroy(handle);
	}
	CIRStream* pIRStream = CreateIRStream();
    pIRStream->Init(port, ip, cbf_stm, cbf_cmd, cbf_cfg, param);

	m_hIRStream[handle] = (long)pIRStream;
	if (rvalue == 2)
		return 2;
	else
		return 1;
}
IR_API long IR_Destroy(long handle)
{
	if (!m_hIRStream[handle]) return 0;
	CIRStream* pIRStream = (CIRStream*)m_hIRStream[handle];
	DestroyIRStream(pIRStream);
	m_hIRStream[handle] = 0;
	return true;
}

IR_API long IR_Send(long handle,char *command, int len)
{
	if (!m_hIRStream[handle]) return 0;
	if (command == NULL) return -1;
	CIRStream* pIRStream = (CIRStream*)m_hIRStream[handle];
    return pIRStream->Send(command,len);
}

IR_API long IR_Command(long handle, int cmd, int param)
{
    if (!m_hIRStream[handle]) return 0;
    CIRStream* pIRStream = (CIRStream*)m_hIRStream[handle];
    return pIRStream->Command(cmd, param);
}

IR_API CIRStream* CreateIRStream()
{
	CIRStream* pIRStream = new CIRStream;
	return pIRStream;
}
IR_API void DestroyIRStream(CIRStream* pIRStream)
{
	delete pIRStream;
	pIRStream = NULL;
} 

IR_API long IR_Inqure(long handle)
{
	if (!m_hIRStream[handle]) 
		return 0;
	else
		return 1;
}
