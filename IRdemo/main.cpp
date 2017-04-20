#include <QTextCodec>
#include <QtGui/QGuiApplication>
#include "irmainwindow.h"
int main(int argc, char *argv[])
{
	//QGuiApplication app(argc, argv); 
	QApplication app(argc, argv); 
	QTextCodec *codec = QTextCodec::codecForName("GBK");

	IrMainWindow w;
	w.show();
	return app.exec();
}
