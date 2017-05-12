#ifndef _IRMAINWINDOW_H
#define _IRMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

#include "ui_irmainwindow.h"
#include "IRSDK.h"
#include "cmdwidget.h"

class IrMainWindow : public QMainWindow,public Ui_IrMainWindow
{
	Q_OBJECT

public:

	
    IrMainWindow(QWidget *parent = 0);
    ~IrMainWindow();
	friend long CmdCallBack(long lData, long lParam);
	CBF_IR pCBFcmd;
	CBF_IR pCBFframe;
    CBF_IR pCBFconfig;
    CmdWidget cmdWidget;

public slots:
	int Connect();
    int Disconnect();
    int Calibrate();
	int DevSet();
    int Record();
private:

	QString ir_ip;
	
   

};
#endif
