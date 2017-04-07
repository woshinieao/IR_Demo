#include "irmainwindow.h"


long CmdCallBack(long lData, long lParam)
{

    printf("yyyyyyyyyyyyyyyyyyyyyyyyy\n");
	return 0;
}

IrMainWindow::IrMainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this); 

	
	pCBFcmd = &CmdCallBack;
    pCBFframe = playwidget->pCBFframe;
	cbox_palette->setIconSize(QSize(90,20));
    cbox_palette->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	
	connect(btn_connect,SIGNAL(clicked()),this,SLOT(Connect()));
	connect(btn_disconnect,SIGNAL(clicked()),this,SLOT(Disconnect()));
	connect(btn_play,SIGNAL(clicked()),playwidget,SLOT(Play()));
	connect(btn_stop,SIGNAL(clicked()),playwidget,SLOT(Stop()));
    connect(btn_calibrate,SIGNAL(clicked()),this,SLOT(Calibrate()));
	connect(btn_pic,SIGNAL(clicked()),playwidget,SLOT(GrapPicture()));
	connect(cbox_palette,SIGNAL(currentIndexChanged(int)),playwidget,SLOT(FramePalette(int)));
	
}

int IrMainWindow::Connect()
{
	ir_ip=le_ip->text();
	QByteArray ipbyte = ir_ip.toLocal8Bit();
	char*ip = ipbyte.data();
    IR_Create(0, 30245, ip,pCBFframe, pCBFcmd, (long)(playwidget));
   // IR_Command(0, COMMAND_PLAY);
	printf("IR_Create over !\n");
    return 0;
}




int IrMainWindow::Disconnect()
{

	return 0;
}

int IrMainWindow::Calibrate()
{
qDebug()<<"aaaaaaaaaaa tttttttttttttttt";
   return  IR_Command(0,COMMAND_CALIBRATE);

}




IrMainWindow::~IrMainWindow()
{

}
