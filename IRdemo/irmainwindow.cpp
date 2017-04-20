#include "irmainwindow.h"


long CmdCallBack(long lData, long lParam)
{

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
	connect(btn_calibrate,SIGNAL(clicked()),this,SLOT(Calibrate()));
	connect(btn_set,SIGNAL(clicked()),this,SLOT(DevSet()));
//	connect(btn_video,SIGNAL(clicked()),this,SLOT(Record()));

	
	connect(btn_play,SIGNAL(clicked()),playwidget,SLOT(Play()));
	connect(btn_stop,SIGNAL(clicked()),playwidget,SLOT(Stop()));
	connect(btn_pic,SIGNAL(clicked()),playwidget,SLOT(GrapPicture()));
	connect(this,SIGNAL(sigRecord(bool)),playwidget,SLOT(RecordIng(bool)));

	

	connect(cbox_palette,SIGNAL(currentIndexChanged(int)),playwidget,SLOT(FramePalette(int)));
	connect(brn_draw,SIGNAL(clicked()),playwidget,SLOT(DrawRect()));

	connect(btn_point,SIGNAL(clicked()),playwidget,SLOT(PointTemperature()));
	connect(btn_rectClear,SIGNAL(clicked()),playwidget,SLOT(CleanRect()));
    connect(btn_save,SIGNAL(clicked()),playwidget,SLOT(SaveRect()));

	connect(toolBox,SIGNAL(currentChanged(int)),playwidget,SLOT(ContrlMode(int)));
	
	
}

int IrMainWindow::Connect()
{
	ir_ip=le_ip->text();
	QByteArray ipbyte = ir_ip.toLocal8Bit();
	char*ip = ipbyte.data();
    IR_Create(0, 30245, ip,pCBFframe, pCBFcmd, (long)(playwidget));
	printf("IR_Create over !\n");
    return 0;
}




int IrMainWindow::Disconnect()
{

	return 0;
}

int IrMainWindow::Calibrate()
{
   return  IR_Command(0,COMMAND_CALIBRATE);
}




int IrMainWindow::Record()
{
	bool state = btn_video->isChecked();

	 emit sigRecord(state);
	 return 0;
}


int IrMainWindow::DevSet()
{
//	cmdWidget.show();
	return 0;

}


IrMainWindow::~IrMainWindow()
{

}
