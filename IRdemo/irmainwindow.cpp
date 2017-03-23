#include "irmainwindow.h"


long CmdCallBack(long lData, long lParam)
{
	return 0;
}

IrMainWindow::IrMainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this); 
	connect(btn_connect,SIGNAL(clicked()),this,SLOT(ir_connect()));
	connect(btn_disconnect,SIGNAL(clicked()),this,SLOT(ir_disconnect()));
	connect(btn_play,SIGNAL(clicked()),playwidget,SLOT(Play()));
	connect(btn_stop,SIGNAL(clicked()),playwidget,SLOT(Stop()));	
	pCBFcmd = &CmdCallBack;
}

int IrMainWindow::ir_connect()
{
	ir_ip=le_ip->text();
	QByteArray ipbyte = ir_ip.toLocal8Bit();
	char*ip = ipbyte.data();
	IR_Create(0, 10000, ip,playwidget->pCBFframe, 0, 0);
    return 0;

}

int IrMainWindow::ir_disconnect()
{

	return 0;
}


IrMainWindow::~IrMainWindow()
{

}
