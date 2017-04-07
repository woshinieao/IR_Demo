#ifndef _IRMAINWINDOW_H
#define _IRMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QPushButton>

#include "ui_irmainwindow.h"
#include "IRCore.h"


class IrMainWindow : public QMainWindow,public Ui_IrMainWindow
{
	Q_OBJECT

public:

	
    IrMainWindow(QWidget *parent = 0);
    ~IrMainWindow();
	friend long CmdCallBack(long lData, long lParam);
	CBF_IR pCBFcmd;
	CBF_IR pCBFframe;

public slots:
	int Connect();
    int Disconnect();
    int Calibrate();
private:

	QString ir_ip;
   

};
#endif
