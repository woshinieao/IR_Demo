#ifndef __CMDWIDGET_H
#define __CMDWIDGET_H


#include "ui_cmdwidget.h"

#include "qglobal.h"
#include "IRSDK.h"




class CmdWidget:public QWidget,public Ui_CmdWidget
{
	Q_OBJECT
public:
	CmdWidget(QWidget *parent = 0);	
	~CmdWidget();
    friend long  ConfigCallBack(long lData, long lParam);
    QButtonGroup btnGroup;
    CBF_IR pCBFconfig;
signals:
    void sigRecv(QString);
public slots:
	void IRCommand(int);
    void RecvMsg(QString);
private:
	char cmdStr[14];
    BOOL IsSendFile; //send file flag
    BOOL IsFileIncDone;//send fileinc flag
    void SendCommand(quint32 Cmd, quint32 Param);
    void SendCommandEx(quint32 u32Cmd,  quint8 * pBuff);
    void SendFile(const char * FilePath);
    void Delay(quint32 u32Delayms);
    int GetNum(char* str);
};



#endif

