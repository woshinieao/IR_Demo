#ifndef _PLAYWIDGET_H
#define _PLAYWIDGET_H

#include <QtWidgets>
#include <QPaintEvent>
#include <QThread>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QMutex>

#include "IRCore.h"
#include "IRPalette.h"
typedef struct BITMAPFILEHEADER  
{   
    u_int16_t bfType;   
    u_int32_t bfSize;   
    u_int16_t bfReserved1;   
    u_int16_t bfReserved2;   
    u_int32_t bfOffBits;   
}BITMAPFILEHEADER;   
  
typedef struct BITMAPINFOHEADER  
{   
    u_int32_t biSize;   
    u_int32_t biWidth;   
    u_int32_t biHeight;   
    u_int16_t biPlanes;   
    u_int16_t biBitCount;   
    u_int32_t biCompression;   
    u_int32_t biSizeImage;   
    u_int32_t biXPelsPerMeter;   
    u_int32_t biYPelsPerMeter;   
    u_int32_t biClrUsed;   
    u_int32_t biClrImportant;   
}BITMAPINFODEADER;  

typedef struct tagRGBQUAD {
        u_int8_t    rgbBlue;
        u_int8_t    rgbGreen;
        u_int8_t    rgbRed;
        u_int8_t    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO { 
	BITMAPFILEHEADER bmpfileheader;
    BITMAPINFOHEADER bmiHeader; //指定了一个BITMAPINFOHEADER结构，包含了有关设备相关位图的度量和颜色格式的信息
    RGBQUAD          bmiColors[256]; //指定了一个RGBQUAD或DWORD数据类型的数组，定义了位图中的颜色。
} BITMAPINFO; 



typedef struct tagBMPFILE {

	BITMAPFILEHEADER fileheader;
	BITMAPINFO       info;
	BYTE buffer[MAX_COUNT];
	struct tagBMPFILE *pre;
	struct tagBMPFILE *next;
	
}BMPFLIE;





typedef enum enumParameter
{
	PARAM_FPA_TEMP=0,
	PARAM_CEN_TEMP,
	PARAM_MAX_TEMP,
	PARAM_MAX_X,
	PARAM_MAX_Y,
	PARAM_COUNT
} eParameter;


typedef struct tagCovertFrame
{
	BYTE buffer[MAX_COUNT];
	USHORT iParam[PARAM_COUNT];
} CovertFrame;



#define HIST_SIZE 32768
#define BITMAPINFO_SIZE sizeof(BITMAPINFO) + (256 - 1) * sizeof(RGBQUAD)




typedef long (*CBF_IR)(long lData, long lParam);

class PlayWidget;

class FrameRcvThread : public QThread
{
	Q_OBJECT
public:
	FrameRcvThread();
	int FrameHeader();
	int FramePalette(int index);
	int FrameConvert();
	int FrameSave();
	void run();
	PlayWidget *m_Parent;
	QMutex mutex_frame;
	Frame *pFrame;
	CovertFrame m_Covertframe;
	BITMAPINFO m_FileInfoheader;

public slots:

	int FrameRecv(Frame *pframe);
private:
	

};



class PlayWidget : public QWidget
{
	Q_OBJECT

public:
	PlayWidget(QWidget *parent = 0);
	~PlayWidget();
	friend long FrameCallBack(long lData, long lParam);

	QMutex mutex_bmp;
	CBF_IR pCBFframe;
	BMPFLIE m_Bmpfile;

	
public slots:
	int Play();
	int Stop();
	void paintEvent(QPaintEvent *event);
signals: 
	void sigFrame(Frame *pframe);
	
private:
	FrameRcvThread frameThread;
	bool playing;









	
};

#endif
