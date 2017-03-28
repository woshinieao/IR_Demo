#include "IRCore.h"

#define DEVICE_COUNT 16
long m_hIRStream[DEVICE_COUNT] = { 0 };

IR_API long IR_Create(long handle, int port, char* ip, CBF_IR cbf_stm, CBF_IR cbf_cmd, long param)
{
	if (handle >= DEVICE_COUNT)	return 0;
	if (m_hIRStream[handle])
		IR_Destroy(handle);
	CIRStream* pIRStream = CreateIRStream();
	pIRStream->Init(port, ip, cbf_stm, cbf_cmd, param);
	m_hIRStream[handle] = (long)pIRStream;
	printf("33333333333333333333333333\n");
	return true;
}
IR_API long IR_Destroy(long handle)
{
	if (!m_hIRStream[handle]) return 0;
	CIRStream* pIRStream = (CIRStream*)m_hIRStream[handle];
	DestroyIRStream(pIRStream);
	m_hIRStream[handle] = 0;
	return true;
}
IR_API long IR_Command(long handle, eCommand command)
{
	if (!m_hIRStream[handle]) return 0;
	CIRStream* pIRStream = (CIRStream*)m_hIRStream[handle];
	return pIRStream->Command(command);
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
