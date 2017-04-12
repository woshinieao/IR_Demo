#ifndef _PLAYWIDGET_H
#define _PLAYWIDGET_H

#include <QtWidgets>
#include <QPaintEvent>
#include <QThread>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QDebug>
#include <QMutex>
#include <string.h>
#include "IRCore.h"
#include "IRPalette.h"

#define HIST_SIZE 32768
#define MAX_OBJ_NUM 9
#define DRAW_MODE 1

typedef enum enumDrawMode
{
	DRAW_NO = 0,
	DRAW_RECT = 1,
	DRAW_POINT = 2,
	DRAW_MOVE = 3,
	
} eDrawMode;



typedef struct BITMAPFILEHEADER  
{   
	u_int16_t bfReserved0; //额外加的两字节，为了消除结构体四字节对齐导致的多出两个字节，文件写入时，需要除去开头两字节
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
    BITMAPINFOHEADER bmiHeader; //指定了一个BITMAPINFOHEADER结构，包含了有关设备相关位图的度量和颜色格式的信息
    RGBQUAD          bmiColors[256]; //指定了一个RGBQUAD或DWORD数据类型的数组，定义了位图中的颜色。
} BITMAPINFO; 

typedef struct tagBMPFILE {	
	BITMAPFILEHEADER fileheader;
	BITMAPINFO       info;
	BYTE buffer[MAX_COUNT];	
}BMPFLIE;



typedef enum enumParameter
{
	PARAM_FPA_TEMP=0,
	PARAM_CEN_TEMP,
	PARAM_MAX_TEMP,
	PARAM_MIN_TEMP,
	PARAM_MAX_X,
	PARAM_MAX_Y,
	PARAM_MIN_X,
	PARAM_MIN_Y,
	PARAM_COUNT
} eParameter;


typedef struct tagCovertFrame
{
	BYTE buffer[MAX_COUNT];
	USHORT iParam[PARAM_COUNT];
} CovertFrame;


typedef struct tagRectInfo
{
	int x;
	int y;
	int h;
	int w;
	int max;
	int min;
} tRectInfo;






typedef long (*CBF_IR)(long lData, long lParam);

class PlayWidget : public QWidget
{
	Q_OBJECT

public:
	PlayWidget(QWidget *parent = 0);
	~PlayWidget();
	QMutex mutex_bmp;
    CBF_IR pCBFframe;
	BMPFLIE m_Bmpfile;
    CovertFrame m_Covertframe;
    BMPFLIE m_FileInfoheader;
    Frame *pFrame;
	bool m_play;
	bool m_grap;
	
	QString m_file;
    QTimer timer;
    int iframnum;
    friend long FrameCallBack(long lData, long lParam);

public slots:
	int Play();
    int Stop();
	int FrameHeader();
    int FramePalette(int index);
    int FrameConvert();
    int FrameRecv(Frame *pframe);

       void TimeSecond();
	int ContrlMode(int );
	int GrapPicture();
	int PointTemperature();
	int DrawRect();
	int SaveRect();
	int CleanRect();
	int SetHistParam(short Param1, short Param2, short Param3, short Param4, short Param5);
	int Histogram(UINT16 *p, UINT16 u16Max, UINT16 u16Min, UINT16 u16Width, UINT16 u16Hight, UINT16 *QuanMax, UINT16 *QuanMin, UINT16 *NrBins, UINT16 u16Param4, UINT16 u16Param5);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent* event);		//将画图或者是改变大小及移动的rect坐标调整为正数
	void paintEvent(QPaintEvent *event);


private:
	short u16HistParam1;
	short u16HistParam2;
	short u16HistParam3;
	short u16HistParam4;
	short u16HistParam5;
	UINT8 u8HistMethod;
	UINT m_iParam[PARAM_COUNT];
	UINT m_iSum[PARAM_COUNT];
	UINT8	u8SensorType;

	QPen pen;
	QLabel lb_point;
	QLabel *label_rect[MAX_OBJ_NUM];
    QLabel *lbFrameNum;
	QRect  m_rectObjTemp[MAX_OBJ_NUM];
	QRect  m_rectObj[MAX_OBJ_NUM];
	QPoint before_pos; 		     //记录鼠标初始位置
	QPoint current_pos; 		  //记录鼠标当前位置
	tRectInfo  m_rectInfo[MAX_OBJ_NUM];
	eDrawMode flag_draw;//用来标记什么时候开始画矩形
	int flag_findnum;//用来标记移动、改变大小的矩形
	int  m_iObjNum;	//用来记录图形框的数量，以判断图形数量是否达到最大值
	int flag_width;		//记录图形改变前的宽度
	int flag_height;		//记录图形改变前的高度
	int ctrl_mode;
    int ttt;
};

#endif
