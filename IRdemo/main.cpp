#include <QTextCodec>
#include <QtGui/QGuiApplication>
#include "irmainwindow.h"
int main(int argc, char *argv[])
{
	//QGuiApplication app(argc, argv); 
	QApplication app(argc, argv); 
	//QTextCodec *codec = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	IrMainWindow w;
	w.show();
	return app.exec();
}
