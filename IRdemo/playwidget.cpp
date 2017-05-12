#include "playwidget.h"
#include "palette.h"
#include<stdio.h>
#include "irmainwindow.h"


long  FrameCallBack(long lData, long lParam)
{

    PlayWidget* pIRPlayer = ((IrMainWindow *)lParam)->playwidget;
    if( pIRPlayer->m_play == false)
        return 0;
    if(pIRPlayer->mutex_bmp.tryLock())
    {
        pIRPlayer->pFrame =(Frame *)lData;
        pIRPlayer-> FrameRecv((Frame *)lData);
        pIRPlayer->mutex_bmp.unlock();
    }
    return 0;
}



TemperatureThread::TemperatureThread(void * /*arg*/)
{
    for(int it=0;it<MAX_OBJ_NUM;it++)
    {
        m_rectInfo[it].max = 0;
        m_rectInfo[it].min = 0xffffff;
        m_rectInfo[it].x = 0;
        m_rectInfo[it].y = 0;
        m_rectInfo[it].w = 0;
        m_rectInfo[it].h = 0;
    }

}

void TemperatureThread::run()
{
    while(true)
    {
        mutex.lock();
        cond.wait(&mutex);
        for(int it=0;it<m_parent->m_iObjNum;it++)
        {
         m_rectInfo[it].max = 0;
         m_rectInfo[it].min = 0xffffff;
            for (int j = m_rectInfo[it].y; j < m_rectInfo[it].y+m_rectInfo[it].h; j++)
            {
                for (int i = m_rectInfo[it].x; i < m_rectInfo[it].x+m_rectInfo[it].w; i++)
                {
                    if(m_rectInfo[it].max<thdFrame.buffer[i + thdFrame.width * j])
                            m_rectInfo[it].max =thdFrame.buffer[i + thdFrame.width * j];
                    else if(m_rectInfo[it].min>thdFrame.buffer[i + thdFrame.width * j])
                            m_rectInfo[it].min =thdFrame.buffer[i + thdFrame.width * j];
                }
            }
            QString maxT = QString::number((m_rectInfo[it].max-4000)/10,'f',2);
            QString avgT = QString::number((m_rectInfo[it].max+m_rectInfo[it].min-8000)/20,'f',2);
            QString minT = QString::number( (m_rectInfo[it].min-4000)/10.0,'f',2);
			
            m_parent->str_obj[it] = "max:"+maxT+"  "+"avg:"+avgT+"  "+"min:"+minT;
        }
        mutex.unlock();
        /*
        for(int it=0;it<parent->m_iObjNum;it++)
        {
        qDebug()<<"it:"<<it;
        qDebug()<<"m_rectInfo[it].x:"<<m_rectInfo[it].x;
         qDebug()<<"m_rectInfo[it].y:"<<m_rectInfo[it].y;
          qDebug()<<"m_rectInfo[it].w:"<<m_rectInfo[it].w;
           qDebug()<<"m_rectInfo[it].h:"<<m_rectInfo[it].h;
  qDebug()<<"m_rectInfo[it].max:"<<m_rectInfo[it].max;
   qDebug()<<"m_rectInfo[it].min:"<<m_rectInfo[it].min;
        }
        */
    }
}

void TemperatureThread::WakeUp(Frame *pTmp,eDrawMode emode)
{

     //   PlayWidget *parent = (PlayWidget *)this->parent();
    if(emode == DRAW_POINT)
    {
        QPoint position;

        float xp,yp;
        float xi,xj;
		xi = (float)(m_parent->width());
        xj = (float)(m_parent->height());

	for(int t=0;t<m_parent->m_iPointNum;t++)
	{
        position = m_parent->lb_point[t].pos();
        xp = (((float)pTmp->width)/xi);
        yp = (((float)pTmp->height)/xj);
        int i = (int)m_parent->lb_point[t].x()*xp;
        int j = (int)m_parent->lb_point[t].y()*yp ;
      	m_parent->lb_point[t].setText(QString::number(  (pTmp->buffer[i + thdFrame.width * j]-4000 )/ 10.0 ,'f', 2 ));
	}
        /*
        qDebug()<<"width: "<<pTmp->width;
        qDebug()<<"height: "<<pTmp->height;
        qDebug()<<"parent->width() :"<<parent->width();
        qDebug()<<"parent->height() :"<<parent->height();
        qDebug()<<"-------------------";
        printf("xp: %f\n",xp);
        printf("yp: %f\n",yp);
        printf("xi: %f\n",xi);
        printf("yj: %f\n",xj);
        printf("parent->lb_point.x() : %f\n",(float)position.x()*xp);
        printf("parent->lb_point.y() : %f\n",(float)position.y()*yp);
        qDebug()<<"i: "<<i;
        qDebug()<<"j: "<<j;
        */
        return ;
    }
    else if( m_parent->bRectTemp == 1)
    {
         if(mutex.tryLock())
		{
			memcpy(&thdFrame,pTmp,sizeof(Frame));
			mode = emode;
            mutex.unlock();
		}
       cond.wakeOne();
    }


}


TemperatureThread::~TemperatureThread()
{

}


void RecordThread::run()
{

    /*
    int i=0;
    avi_t *out_fd = NULL;
    QString video_file = QDate::currentDate().toString("yyyy.MM.dd")+"-"+ QTime::currentTime().toString("hh.mm.ss")+".avi";
    QByteArray cpath = video_file.toLocal8Bit();

    char*p = cpath.data();
    out_fd = AVI_open_output_file(p);
    if(out_fd!=NULL)
    {
        AVI_set_video(out_fd, 640, 480, 50, "MJPG");
}






    while(m_start)
    {




        USHORT p[MAX_COUNT];
        int  max = HIST_SIZE - 1, min = 0;
        memcpy(p, videoFrame.buffer, sizeof(videoFrame.buffer) );
        int hist[HIST_SIZE];
        long sum = 0;
        memset(hist, 0, sizeof(int) * HIST_SIZE);
        for (int i = 0; i < videoFrame.width * videoFrame.height; i++)
        {
            hist[p[i]]++;
        }
        for (int i = 0; i < HIST_SIZE; i++)
        {
            sum += hist[i];
            if (sum <= videoFrame.width * videoFrame.height * 0.01)
                min = i;
            if (sum <= videoFrame.width * videoFrame.height * 0.99)
                max = i;
            else
                break;
        }
        if (hist[min] > 32) hist[min] = 32;
        else if (hist[min] < 1) hist[min] = 1;
        for (int i = min + 1; i <= max; i++)
        {
            if (hist[i] > 32) hist[i] = hist[i-1] + 32;
            else if (hist[i] <	1) hist[i] = hist[i-1] + 1;
            else hist[i] += hist[i-1];
        }
        BYTE v = 232;
        if (max - min < 232) v = max - min;
        if (max - min < 128) v = 128;

        BYTE table[HIST_SIZE];
        for (int i = min; i <= max; i++)
        {
            table[i] = (BYTE)(hist[i] * v / hist[max]);
        }
        for (int i = 0; i < videoFrame.width * videoFrame.height; i++)
        {
            if (p[i] > max)
                m_frame.buffer[i] = table[max] - v / 2 + 128;
            else if (p[i] < min)
                m_frame.buffer[i] = table[min] - v / 2 + 128;
            else
                m_frame.buffer[i] = table[p[i]] - v / 2 + 128;
        }

    i++;
        qDebug()<<" recording :"<<i;

    memset(m_frame.buffer,i,MAX_COUNT);
    memcpy((void *)framefile.buffer,(void *)m_frame.buffer,MAX_COUNT);

    AVI_write_frame(out_fd, (char *)framefile.info.bmiColors,MAX_COUNT+sizeof(RGBQUAD),0);
    if(i>50)
        break;
    }
    AVI_close(out_fd);
*/
}





PlayWidget::PlayWidget(QWidget *parent)
    : QWidget(parent)
{

    connect(&timer,SIGNAL(timeout()),this,SLOT(TimeSecond()));
    flag_draw  =DRAW_NO;
    ctrl_mode = 0;
    bRectTemp = 0;
    iFps = 0;
    m_iObjNum = 0;
	m_iPointNum =0;
    m_record = false;
    times = 0;
	m_width=640;
	m_height=480;

    pen.setWidth(3);
    pen.setColor(Qt::red);
    pFrame = new Frame;
    pCBFframe = &FrameCallBack;
    char R[10];
    for(int num=0;num< MAX_OBJ_NUM;num++)
    {
        sprintf(R,"R:%d",num);
        label_rect[num] = new  QLabel(R,this,0);
        label_rect[num]->setAttribute(Qt::WA_TranslucentBackground);
        label_rect[num]->hide();
        lb_obj[num].setParent(this);
        lb_obj[num].hide();
        str_obj[num] =" ";
		 lb_point[num].setParent(this);
    	lb_point[num].setAttribute(Qt::WA_TranslucentBackground);
    	lb_point[num].hide();
    }
   

    lbFrameNum = new  QLabel(this);
    lbFrameNum->setAttribute(Qt::WA_TranslucentBackground);
    lbFrameNum->hide();

   //tempThread.setParent(this);
    FrameHeader();
    FramePalette(0);
    tempThread.m_parent = this;



}

int PlayWidget::FrameHeader()
{

    m_FileInfoheader.fileheader.bfType = 'M' << 8 | 'B';
    m_FileInfoheader.fileheader.bfSize = 0;
    m_FileInfoheader.fileheader.bfReserved1 = 0;
    m_FileInfoheader.fileheader.bfReserved2 = 0;
    m_FileInfoheader.fileheader.bfOffBits = sizeof(BITMAPFILEHEADER)-2 + sizeof(BITMAPINFO); //��ȥ2����Ϊ�ṹ��BITMAPFILEHEADER �п�ͷ���������ֽ�
    m_FileInfoheader.info.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
    m_FileInfoheader.info.bmiHeader.biWidth         = 0;
    m_FileInfoheader.info.bmiHeader.biHeight        = 0;
    m_FileInfoheader.info.bmiHeader.biPlanes        = 1;
    m_FileInfoheader.info.bmiHeader.biBitCount      = 8;
    m_FileInfoheader.info.bmiHeader.biCompression   = 0;
    m_FileInfoheader.info.bmiHeader.biSizeImage     = 0;
    m_FileInfoheader.info.bmiHeader.biXPelsPerMeter = 0;
    m_FileInfoheader.info.bmiHeader.biYPelsPerMeter = 0;
    m_FileInfoheader.info.bmiHeader.biClrUsed       = 256;
    m_FileInfoheader.info.bmiHeader.biClrImportant  = 0;

/*
printf("BITMAPFILEHEADER:\n");
printf("bfSize:	  %d\n",m_FileInfoheader.fileheader.bfSize);
printf("bfReserved1: %d\n",m_FileInfoheader.fileheader.bfReserved1);
printf("bfReserved2: %d\n",m_FileInfoheader.fileheader.bfReserved2);
printf("bfOffBits:   %d\n",m_FileInfoheader.fileheader.bfOffBits);
printf("BITMAPINFODEADER:\n");
printf("biSize:		   %d\n",m_FileInfoheader.info.bmiHeader.biSize);
printf("biWidth: 	   %d\n",m_FileInfoheader.info.bmiHeader.biWidth);
printf("biHeight:	   %d\n",m_FileInfoheader.info.bmiHeader.biHeight);
printf("biPlanes:	   %d\n",m_FileInfoheader.info.bmiHeader.biPlanes);
printf("biBitCount:	   %d\n",m_FileInfoheader.info.bmiHeader.biBitCount);
printf("biCompression:  %d\n",m_FileInfoheader.info.bmiHeader.biCompression);
printf("biSizeImage:    %d\n",m_FileInfoheader.info.bmiHeader.biSizeImage);
printf("biSizeImage:    %d\n",m_FileInfoheader.info.bmiHeader.biXPelsPerMeter);
printf("biYPelsPerMeter:%d\n",m_FileInfoheader.info.bmiHeader.biYPelsPerMeter);
printf("biClrUsed:	   %d\n",m_FileInfoheader.info.bmiHeader.biClrUsed);
printf("biClrImportant: %d\n",m_FileInfoheader.info.bmiHeader.biClrImportant);
printf("sizeof(BITMAPFILEHEADER)%ld	sizeof(BITMAPINFODEADER):%ld \n",sizeof(BITMAPFILEHEADER),sizeof(BITMAPINFODEADER));
*/
    return 0;
}



int PlayWidget::FramePalette(int index)
{
    if(index >8)
        return -1;
    for (int i = 0; i <= 255; i++)
    {
        m_FileInfoheader.info.bmiColors[i].rgbRed   = paletteList[(index * 256 + i) * 3 + 0];
        m_FileInfoheader.info.bmiColors[i].rgbGreen = paletteList[(index * 256 + i) * 3 + 1];
        m_FileInfoheader.info.bmiColors[i].rgbBlue  = paletteList[(index * 256 + i) * 3 + 2];
    }

    return 0;
}

int PlayWidget::SetHistParam(short Param1, short Param2, short Param3, short Param4, short Param5)
{
    u16HistParam1 = Param1;
    u16HistParam2 = Param2;
    u16HistParam3 = Param3;
    u16HistParam4 = Param4;
    u16HistParam5 = Param5;
    return 1;
}


int PlayWidget::Histogram(UINT16 *p, UINT16 u16Max, UINT16 u16Min, UINT16 u16Width, UINT16 u16Hight, UINT16 *QuanMax, UINT16 *QuanMin, UINT16 *NrBins, UINT16 u16Param4, UINT16 u16Param5)
{
    USHORT max = HIST_SIZE - 1, min = 0;
    static int hist[HIST_SIZE];
    static short y8_eq[MAX_COUNT];
    long sum = 0;

    memset(hist, 0, sizeof(int) * HIST_SIZE);
    for (int i = 0; i < u16Width * u16Hight; i++)
    {
        hist[p[i]]++;
    }
    for (int i = 0; i < HIST_SIZE; i++)
    {
        sum += hist[i];
        if (sum <= u16Width * u16Hight * 0.01)
            min = i;
        if (sum <= u16Width * u16Hight * 0.99)
            max = i;
        else
            break;
    }
    if (hist[min] > 32) hist[min] = 32;
    else if (hist[min] < 1) hist[min] = 1;
    for (int i = min + 1; i <= max; i++)
    {
        if (hist[i] > 32) hist[i] = hist[i-1] + 32;
        else if (hist[i] <	1) hist[i] = hist[i-1] + 1;
        else hist[i] += hist[i-1];
    }
    UINT v = 232;
    if (max - min < 232) v = max - min;
    if (max - min < 16) v = 16;

    v = v * u16Param5 /128.0;
    if (v > 255) v = 255;

    BYTE table[HIST_SIZE];
    for (int i = min; i <= max; i++)
    {
        table[i] = (BYTE)(hist[i] * v / hist[max]);
    }
    for (int i = 0; i < u16Width * u16Hight; i++)
    {
        if (p[i] > max)
            y8_eq[i] = table[max] - v / 2 + u16Param4;
        else if (p[i] < min)
            y8_eq[i] = table[min] - v / 2 + u16Param4;
        else
            y8_eq[i] = table[p[i]] - v / 2 + u16Param4;

        if (y8_eq[i] > 255) y8_eq[i] = 255;
        if (y8_eq[i] < 0)	y8_eq[i] = 0;
        p[i] = y8_eq[i];
    }


    //static int hist[HIST_SIZE];
    //static SHORT y8_eq[MAX_COUNT];

    //memset(hist, 0, sizeof(int) * HIST_SIZE);
    //for (int i = 0; i < u16Width * u16Hight; i++)
    //{
    //	hist[pFrame[i]]++;
    //}
    //
    //for (int i = u16Min + 1; i <= u16Max; i++)
    //{
    //	if (hist[i] > 32) hist[i] = hist[i-1] + 32;
    //	else if (hist[i] <	1) hist[i] = hist[i-1] + 1;
    //	else hist[i] += hist[i-1];
    //}
    //BYTE v = 232;
    //if (u16Max - u16Min < 232) v = u16Max - u16Min;
    //if (u16Max - u16Min < 16) v = 16;

    //if (v > 255) v = 255;

    //BYTE table[HIST_SIZE];
    //for (int i = u16Min; i <= u16Max; i++)
    //{
    //	table[i] = (BYTE)(hist[i] * v / hist[u16Max]);
    //}
    //for (int i = 0; i < u16Width * u16Hight; i++)
    //{
    //	if (pFrame[i] > u16Max)
    //		y8_eq[i] = table[u16Max];
    //	else if (pFrame[i] < u16Min)
    //		y8_eq[i] = table[u16Min];
    //	else
    //		y8_eq[i] = table[pFrame[i]];

    //	if (y8_eq[i] > 255) y8_eq[i] = 255;
    //	if (y8_eq[i] < 0)	y8_eq[i] = 0;
    //	pFrame[i] = y8_eq[i];
    //}

    for (int j = 0; j < u16Hight; j++)
    {
        for (int i = 0; i < u16Width; i++)
        {
            if (*QuanMax < p[i + u16Width * j])
            {
                *QuanMax = p[i + u16Width * j];
            }
            if (*QuanMin > p[i + u16Width * j])
            {
                *QuanMin = p[i + u16Width * j];
            }
        }
    }
    return 0;
}

#if 0
int PlayWidget::FrameConvert()
{


    static UINT32 u32Cnt = 0;

    USHORT p[MAX_COUNT], max = HIST_SIZE - 1, min = 0, y16_max = HIST_SIZE - 1, y16_min = 0, y16_avg = 0, y16_diff = 0;
    //USHORT n = 16383, m = 0, u16FpaTemp = 0;
    static short y8_linear[MAX_COUNT];
    static short y8_eq[MAX_COUNT];

    memcpy(p, pFrame->buffer, MAX_COUNT * 2);

    u8SensorType = pFrame->u8SensorType;
    u32Cnt++;
    if (u8HistMethod == 0)
    {

        int hist[HIST_SIZE];
        long sum = 0;
        memset(hist, 0, sizeof(int) * HIST_SIZE);
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            hist[p[i]]++;
        }
        for (int i = 0; i < HIST_SIZE; i++)
        {
            sum += hist[i];
            if (sum <= pFrame->width * pFrame->height * 0.01)
                min = i;
            if (sum <= pFrame->width * pFrame->height * 0.99)
                max = i;
            else
                break;
        }
        if (hist[min] > 32) hist[min] = 32;
        else if (hist[min] < 1) hist[min] = 1;
        for (int i = min + 1; i <= max; i++)
        {
            if (hist[i] > 32) hist[i] = hist[i-1] + 32;
            else if (hist[i] <	1) hist[i] = hist[i-1] + 1;
            else hist[i] += hist[i-1];
        }
        UINT16 v = 232;
        if (max - min < 232) v = max - min;
        if (max - min < 16) v = 16;

        v = v * u16HistParam5 / 64.0;
        if (v > 255) v = 255;

        UINT16 table[HIST_SIZE];
        for (int i = min; i <= max; i++)
        {
            table[i] = (hist[i] * v / hist[max]);
        }
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            if (p[i] > max)
                y8_eq[i] = table[max] - v / 2 + u16HistParam4;
            else if (p[i] < min)
                y8_eq[i] = table[min] - v / 2 + u16HistParam4;
            else
                y8_eq[i] = table[p[i]] - v / 2 + u16HistParam4;

            if (y8_eq[i] > 255) y8_eq[i] = 255;
            if (y8_eq[i] < 0)	y8_eq[i] = 0;
            m_Covertframe.buffer[i] = y8_eq[i];
        }

    }
    else if (u8HistMethod == 3)
    {
        UINT16 u16NrBins = 128;
        float clipLimit ;
        UINT16	u16QuanMax = 0;;
        UINT16	u16QuanMin = 256;

        clipLimit = u16HistParam1;

        Histogram(p, m_iParam[PARAM_MAX_TEMP], m_iParam[PARAM_MIN_TEMP], pFrame->width, pFrame->height, &u16QuanMax, &u16QuanMin, &u16NrBins, u16HistParam2, u16HistParam3);
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            m_Covertframe.buffer[i] = p[i];
        }
        u16NrBins = 255;
    //	CLAHE(m_Covertframe.buffer, pFrame->width, pFrame->height,u16QuanMin, u16QuanMax, u8NrX, u8NrY, u16NrBins, clipLimit);

    }
    else if (u8HistMethod == 1)
    {
        int hist[HIST_SIZE];
        long sum = 0;
        memset(hist, 0, sizeof(int) * HIST_SIZE);
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            hist[p[i]]++;
        }
        for (int i = 0; i < HIST_SIZE; i++)
        {
            sum += hist[i];
            if (sum <= pFrame->width * pFrame->height * 0.01)
                min = i;
            if (sum <= pFrame->width * pFrame->height * 0.99)
                max = i;
            else
                break;
        }
        if (hist[min] > 32) hist[min] = 32;
        else if (hist[min] < 1) hist[min] = 1;
        for (int i = min + 1; i <= max; i++)
        {
            if (hist[i] > 32) hist[i] = hist[i-1] + 32;
            else if (hist[i] <	1) hist[i] = hist[i-1] + 0;
            else hist[i] += hist[i-1];
        }
        BYTE v = 232;

        BYTE table[HIST_SIZE];
        for (int i = min; i <= max; i++)
        {
            table[i] = (BYTE)((hist[i] - hist[min]) * v / (hist[max] - hist[min]));
        }
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            if (p[i] > max)
                m_Covertframe.buffer[i] = table[max] - v / 2 + 127;
            else if (p[i] < min)
                m_Covertframe.buffer[i] = table[min] - v / 2 + 127;
            else
                m_Covertframe.buffer[i] = table[p[i]] - v / 2 + 127;
        }
    }
    else if (u8HistMethod == 2)
    {
        int hist[HIST_SIZE];
        long sum = 0;
        memset(hist, 0, sizeof(int) * HIST_SIZE);
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            hist[p[i]]++;
        }
        for (int i = 0; i < HIST_SIZE; i++)
        {
            sum += hist[i];
            if (sum <= pFrame->width * pFrame->height * 0.01)
                min = i;
            if (sum <= pFrame->width * pFrame->height * 0.2)
                y16_min = i;
            if (sum <= pFrame->width * pFrame->height * 0.8)
                y16_max = i;
            if (sum <= pFrame->width * pFrame->height * 0.99)
                max = i;
            else
                break;
        }
        //���Ե���
        y16_diff = (y16_max - y16_min) + 64;
        y16_avg = (y16_max + y16_min) /2 ;

        UINT16 k;
        UINT16 c;

        k = u16HistParam1 * 8192 / y16_diff;
        c = u16HistParam2 - k * y16_avg / 8192;

        if (hist[min] > 32) hist[min] = 32;
        else if (hist[min] < 1) hist[min] = 1;
        for (int i = min + 1; i <= max; i++)
        {
            if (hist[i] > 32) hist[i] = hist[i-1] + 32;
            else if (hist[i] <	1) hist[i] = hist[i-1] + 1;
            else hist[i] += hist[i-1];
        }
        UINT v = 232;
        if (max - min < 232) v = max - min;
        if (max - min < 16) v = 16;

        v = v * u16HistParam5 /128.0;
        if(v > 255)
           v = 255;

        BYTE table[HIST_SIZE];
        for (int i = min; i <= max; i++)
        {
            table[i] = (BYTE)(hist[i] * v / hist[max]);
        }
        for (int i = 0; i < pFrame->width * pFrame->height; i++)
        {
            if (p[i] > max)
                y8_eq[i] = table[max] - v / 2 + u16HistParam4;
            else if (p[i] < min)
                y8_eq[i] = table[min] - v / 2 + u16HistParam4;
            else
                y8_eq[i] = table[p[i]] - v / 2 + u16HistParam4;

            y8_linear[i] = p[i] * k / 8192 + c;

            if (y8_eq[i] > 255) y8_eq[i] = 255;
            if (y8_eq[i] < 0)	y8_eq[i] = 0;
            if (y8_linear[i] > 255) y8_linear[i] = 255;
            if (y8_linear[i] < 0)	y8_linear[i] = 0;

            m_Covertframe.buffer[i] =  (u16HistParam3 * y8_eq[i] + (1024 - u16HistParam3) * y8_linear[i]) / 1024;
        }
    }
    return 0;
}

#endif
#if 1
int PlayWidget::FrameConvert()
{
    USHORT p[MAX_COUNT];
    int  max = HIST_SIZE - 1, min = 0;
    if(pFrame ==NULL)
    {
        return -1;
    }
    memcpy(p, pFrame->buffer, sizeof(pFrame->buffer) );


/*
    for (int i = 5; i < pFrame->width - 4; i++)
    {
        for (int j = 5; j < pFrame->height - 4; j++)
        {
            if (m < p[i + pFrame->width * j])
            {
                m = p[i + pFrame->width * j];
                m_Covertframe.iParam[PARAM_MAX_X] = i;
                m_Covertframe.iParam[PARAM_MAX_Y] = j;
            }
            if(l>p[i + pFrame->width * j])
            {
                l = p[i + pFrame->width * j];
                m_Covertframe.iParam[PARAM_MIN_X] = i;
                m_Covertframe.iParam[PARAM_MIN_Y] = j;

            }
        }
    }
*/
    int hist[HIST_SIZE];
    long sum = 0;
    memset(hist, 0, sizeof(int) * HIST_SIZE);
    for (int i = 0; i < pFrame->width * pFrame->height; i++)
    {
        hist[p[i]]++;
    }
    for (int i = 0; i < HIST_SIZE; i++)
    {
        sum += hist[i];
        if (sum <= pFrame->width * pFrame->height * 0.01)
            min = i;
        if (sum <= pFrame->width * pFrame->height * 0.99)
            max = i;
        else
            break;
    }
    if (hist[min] > 32) hist[min] = 32;
    else if (hist[min] < 1) hist[min] = 1;
    for (int i = min + 1; i <= max; i++)
    {
        if (hist[i] > 32) hist[i] = hist[i-1] + 32;
        else if (hist[i] <  1) hist[i] = hist[i-1] + 1;
        else hist[i] += hist[i-1];
    }
    BYTE v = 232;
    if (max - min < 232) v = max - min;
    if (max - min < 128) v = 128;

    BYTE table[HIST_SIZE];
    for (int i = min; i <= max; i++)
    {
        table[i] = (BYTE)(hist[i] * v / hist[max]);
    }
    for (int i = 0; i < pFrame->width * pFrame->height; i++)
    {
        if (p[i] > max)
            m_Covertframe.buffer[i] = table[max] - v / 2 + 128;
        else if (p[i] < min)
            m_Covertframe.buffer[i] = table[min] - v / 2 + 128;
        else
            m_Covertframe.buffer[i] = table[p[i]] - v / 2 + 128;
    }
    return 0;
}
#endif

void PlayWidget::TimeSecond()
{
	xi = (float)(this->width());
    xj = (float)(this->height());
    xp = (((float)m_width)/xi);
    yp = (((float)m_height)/xj);
       times++;
    if(times == 4)
    {
     lbFrameNum->setText(QString::number(iFps)+" FPS");
         iFps = 0;
         times=0;
    }
    for(int i=0;i<m_iObjNum;i++)
        lb_obj[i].setText(str_obj[i]);

}




void PlayWidget::TimeSecondTTTTT()
{

//	FrameRecv(&pTmptttt);
//	update();

}


int PlayWidget::FrameRecv(Frame* pTmp)
{

    if(pTmp == NULL)
        return -1;
    iFps++;
    memcpy(pFrame,pTmp,sizeof(Frame));
	m_width=pFrame->width;
	m_height=pFrame->height;
    if( iFps%5 == 0 &&( bRectTemp == 1 || flag_draw == DRAW_POINT))
    {

        tempThread.WakeUp(pTmp,flag_draw);
    }
    USHORT m = 0, n = 16383;
    for (int j = 0; j < pFrame->height; j++)
    {
        for (int i = 0; i < pFrame->width; i++)
        {
            if (m < pFrame->buffer[i + pFrame->width * j])
            {
                m = pFrame->buffer[i + pFrame->width * j];
                m_Covertframe.iParam[PARAM_MAX_X] = i;
                m_Covertframe.iParam[PARAM_MAX_Y] = j;
                m_iParam[PARAM_MAX_TEMP] = m;
            }
            if (n > pFrame->buffer[i + pFrame->width * j])
            {
                n = pFrame->buffer[i + pFrame->width * j];
                m_iParam[PARAM_MIN_TEMP] = pFrame->buffer[i + pFrame->width * j];
                m_Covertframe.iParam[PARAM_MIN_X] = i;
                m_Covertframe.iParam[PARAM_MIN_Y] = j;
            }
         }
    }

        m_iParam[PARAM_FPA_TEMP] = pFrame->u16FpaTemp;
        m_iParam[PARAM_CEN_TEMP] = pFrame->buffer[(pFrame->height/2 - 1)*pFrame->width + pFrame->width/2];
        m_iSum[PARAM_FPA_TEMP] = m_iParam[PARAM_FPA_TEMP];
        m_iSum[PARAM_CEN_TEMP] = m_iParam[PARAM_CEN_TEMP];
        m_iSum[PARAM_MAX_TEMP] = m_iParam[PARAM_MAX_TEMP];
        m_iSum[PARAM_MIN_TEMP] = m_iParam[PARAM_MIN_TEMP];


    FrameConvert();
	m_FileInfoheader.fileheader.bfSize = 54 + 256 * 4 +m_width* m_height;
	m_FileInfoheader.info.bmiHeader.biWidth         = m_width;
    m_FileInfoheader.info.bmiHeader.biHeight        = -m_height;
    memcpy((char*)&m_Bmpfile+2,(char *)(&m_FileInfoheader)+2,sizeof(BITMAPINFO)-2);
    memcpy((void *)m_Bmpfile.buffer,(void *)m_Covertframe.buffer,MAX_COUNT);

    update();
    return 0;

}


int PlayWidget::GrapPicture()
{
    m_file = QDate::currentDate().toString("yyyy.MM.dd")+"-"+ QTime::currentTime().toString("hh.mm.ss")+".jpg";
    m_grap = true;
    qDebug()<<m_file;
    return 0;
}


int PlayWidget::RecordIng(bool starting)
{
 //   videoThread.m_start= m_record =starting;
//    memcpy((void *)&videoThread.framefile,(char *)&m_FileInfoheader+2,sizeof(BMPFLIE));
//    if(starting)
//       videoThread.start();

}


int PlayWidget::Play()
{
    IRSDK_Command(0, USR_PLAY, 1);

    m_play = true;
    lbFrameNum->setGeometry(10,5,50,30 );
    lbFrameNum->show();
    timer.start(250);
    tempThread.start();
    return 0;

}

int PlayWidget::Stop()
{
    IRSDK_Command(0, USR_PLAY, 0);
    //m_play = false;
    return 0;
}

int PlayWidget::ContrlMode(int index)
{
    flag_draw = DRAW_NO;
    return ctrl_mode =index;
}

int PlayWidget::DrawRect()
{
    if(m_iObjNum>9)
        return 0;
    flag_draw = DRAW_RECT;
    return 0;
}

int PlayWidget::SaveRect()
{
    bRectTemp = 1;
    flag_draw = DRAW_NO;


	
 
    for(int i=0;i<m_iObjNum ;i++)
    {

        lb_obj[i].show();
        lb_obj[i].setGeometry(50+220*(i%3),this->height()-(3-i/3)*20,200,20 );
        tempThread.m_rectInfo[i].x	=m_rectObjTemp[i].x()*xp;
        tempThread.m_rectInfo[i].y =m_rectObjTemp[i].y()*yp;
        tempThread.m_rectInfo[i].w =m_rectObjTemp[i].width()*xp;
        tempThread.m_rectInfo[i].h =m_rectObjTemp[i].height()*yp;

        qDebug()<<"it:"<<i;
        qDebug()<<"m_rectInfo[it].x:"<<tempThread.m_rectInfo[i].x;
        qDebug()<<"m_rectInfo[it].y:"<<tempThread.m_rectInfo[i].y;
        qDebug()<<"m_rectInfo[it].w:"<<tempThread.m_rectInfo[i].w;
        qDebug()<<"m_rectInfo[it].h:"<<tempThread.m_rectInfo[i].h;
        qDebug()<<"m_rectInfo[it].max:"<<tempThread.m_rectInfo[i].max;
        qDebug()<<"m_rectInfo[it].min:"<<tempThread.m_rectInfo[i].min;
    }
    return 0;
}



int PlayWidget::CleanRect()
{
    for(int i=0;i<MAX_OBJ_NUM;i++)
    {
        m_rectObjTemp[i].setRect(0,0,0,0);
        tempThread.m_rectInfo[i].x = 0;
        tempThread.m_rectInfo[i].y = 0;
        tempThread.m_rectInfo[i].w = 0;
        tempThread.m_rectInfo[i].h = 0;
        label_rect[i]->hide();
        lb_obj[i].setText(" ");
		lb_point[i].hide();
		lb_point[i].setText(" ");
    }
    m_iObjNum = 0;
	m_iPointNum=0;
    bRectTemp = 0;
    flag_draw = DRAW_NO;
    update();
    return 0;
}

int PlayWidget::PointTemperature()
{
	if(m_iPointNum>9)
		return 0;
    flag_draw = DRAW_POINT;
    //lb_point.show();
    return 0;

}


void PlayWidget::mousePressEvent(QMouseEvent *event)
{

if(ctrl_mode != DRAW_MODE)
    return;
    before_pos = event->pos(); //��ͼ��ȡ��ʼ����
    if(event->buttons()==Qt::LeftButton)
    {
        if(flag_draw == DRAW_RECT)
        {
            m_rectObjTemp[m_iObjNum].setLeft(before_pos.x());
            m_rectObjTemp[m_iObjNum].setTop(before_pos.y());
            m_rectObjTemp[m_iObjNum].setWidth(0) ;
            m_rectObjTemp[m_iObjNum].setHeight(0) ;
            m_iObjNum++;
        }
        else if(flag_draw == DRAW_POINT)
        {

            lb_point[m_iPointNum].show();
			 m_iPointNum++;
            lb_point[m_iPointNum].setGeometry(event->pos().x() ,event->pos().y()-20 ,50,30 );
            //lb_point.setText(QString::number(event->pos().x())+":"+QString::number(event->pos().y()));

        }
        else
        {
            //ͼ�δ�С�ı䶨λ
            for(int i=0;i<m_iObjNum;i++)
            {
                if((before_pos.x()>m_rectObjTemp[i].left()) && (before_pos.x()<m_rectObjTemp[i].left()+m_rectObjTemp[i].width())
                    && (before_pos.y()>m_rectObjTemp[i].top()) && (before_pos.y()<m_rectObjTemp[i].top()+m_rectObjTemp[i].height()))
                {
                    flag_findnum = i;
                    flag_width = m_rectObjTemp[flag_findnum].width();
                    flag_height = m_rectObjTemp[flag_findnum].height();
                    return;
                }
                else
                    flag_findnum = -1;
            }
        }
    }
    else if(event->buttons()==Qt::RightButton) //ͼ���ƶ���λ
    {
        for(int i=0;i<m_iObjNum;i++)
        {
            if((before_pos.x()>m_rectObjTemp[i].left()) && (before_pos.x()<m_rectObjTemp[i].left()+m_rectObjTemp[i].width())
                && (before_pos.y()>m_rectObjTemp[i].top()) && (before_pos.y()<m_rectObjTemp[i].top()+m_rectObjTemp[i].height()))
            {
                flag_findnum = i;
                return;
            }
            else	if((before_pos.x()>m_rectObjTemp[i].left()) && (before_pos.x()<m_rectObjTemp[i].left()+m_rectObjTemp[i].width())
                && (before_pos.y()<m_rectObjTemp[i].top()) && (before_pos.y()>m_rectObjTemp[i].top()+m_rectObjTemp[i].height()))
            {
                flag_findnum = i;
                return;
            }
            else	if((before_pos.x()<m_rectObjTemp[i].left()) && (before_pos.x()>m_rectObjTemp[i].left()+m_rectObjTemp[i].width())
                && (before_pos.y()>m_rectObjTemp[i].top()) && (before_pos.y()<m_rectObjTemp[i].top()+m_rectObjTemp[i].height()))
            {
                flag_findnum = i;
                return;
            }
            else	if((before_pos.x()<m_rectObjTemp[i].left()) && (before_pos.x()>m_rectObjTemp[i].left()+m_rectObjTemp[i].width())
                && (before_pos.y()<m_rectObjTemp[i].top()) && (before_pos.y()>m_rectObjTemp[i].top()+m_rectObjTemp[i].height()))
            {
                flag_findnum = i;
                return;
            }
            else
                flag_findnum = -1;
        }
    }
}


void PlayWidget::mouseMoveEvent(QMouseEvent *event)
{

if(ctrl_mode != DRAW_MODE)
    return;
    current_pos=event->pos();
    int x,y;
    if(event->buttons()==Qt::LeftButton)
    {
        if(flag_draw == DRAW_RECT)
        {

         //   qDebug()<<"m_iObjNum:"<<m_iObjNum;

            if(current_pos.x()>0 && current_pos.x()<this->width()
                && current_pos.y()>0 && current_pos.y()<this->height())
            {
                x = current_pos.x()-before_pos.x();
                y = current_pos.y()-before_pos.y();
                int left	 = m_rectObjTemp[m_iObjNum-1].left();
                int top 	=  m_rectObjTemp[m_iObjNum-1].top();
                int width  =x;
                int height =y;
                m_rectObjTemp[m_iObjNum-1].setLeft(left) ;
                m_rectObjTemp[m_iObjNum-1].setTop(top) ;
                m_rectObjTemp[m_iObjNum-1].setWidth(width) ;
                m_rectObjTemp[m_iObjNum-1].setHeight(height) ;
                if(m_rectObjTemp[m_iObjNum-1].y()<30)
                    label_rect[m_iObjNum-1]->setGeometry(m_rectObjTemp[m_iObjNum-1].left() ,m_rectObjTemp[m_iObjNum-1].top()+m_rectObjTemp[m_iObjNum-1].height(),100,30 );
                else
                    label_rect[m_iObjNum-1]->setGeometry(m_rectObjTemp[m_iObjNum-1].left() ,m_rectObjTemp[m_iObjNum-1].top()-30 ,100,30 );
                label_rect[m_iObjNum-1]->show();
/*
                qDebug()<<"left:"<<m_rectObjTemp[flag_findnum].left();
                qDebug()<<"right:"<<m_rectObjTemp[flag_findnum].right();
                qDebug()<<"widht:"<<m_rectObjTemp[flag_findnum].width();
                qDebug()<<"height:"<<m_rectObjTemp[flag_findnum].height();

                qDebug()<<"x:"<<m_rectObjTemp[flag_findnum].x();
                qDebug()<<"y:"<<m_rectObjTemp[flag_findnum].y();
*/
            }
        }
        else if(flag_draw == DRAW_POINT)
        {
            lb_point[m_iPointNum-1].setGeometry(event->pos().x() ,event->pos().y()-20,50,30 );
        //	lb_point.setText(QString::number(event->pos().x())+":"+QString::number(event->pos().y()));

        }
        else
        {
            //�ı�ͼ�εĴ�С
            if(flag_findnum == -1)
                return;
            int x,y;
            x= current_pos.x()-before_pos.x();
            y= current_pos.y()-before_pos.y();
            int left	 = m_rectObjTemp[flag_findnum].left();
            int top 	=  m_rectObjTemp[flag_findnum].top();
            int width=m_rectObjTemp[flag_findnum].width()+x;
            int height =m_rectObjTemp[flag_findnum].height()+y;
            if(left+width<0)
                width = -left;
            if(top+height<0)
                height = -top;
            m_rectObjTemp[flag_findnum].setLeft(left);
            m_rectObjTemp[flag_findnum].setTop(top);
            m_rectObjTemp[flag_findnum].setWidth(width);
            m_rectObjTemp[flag_findnum].setHeight(height);

            if(top<30)
                label_rect[flag_findnum]->setGeometry(m_rectObjTemp[flag_findnum].left(),m_rectObjTemp[flag_findnum].top()+m_rectObjTemp[flag_findnum].height(),100,30 );
            else
                label_rect[flag_findnum]->setGeometry(m_rectObjTemp[flag_findnum].left(),m_rectObjTemp[flag_findnum].top()-30,100,30 );
            label_rect[flag_findnum]->show();
            before_pos =event->pos();
        }
    }
    else if(event->buttons()==Qt::RightButton)
    {
        if(flag_findnum == -1)
            return;
        int x,y;
        x= current_pos.x()-before_pos.x();
        y= current_pos.y()-before_pos.y();
        int left	 = m_rectObjTemp[flag_findnum].left();
        int top 	=  m_rectObjTemp[flag_findnum].top();
        int width  =m_rectObjTemp[flag_findnum].width();
        int height =m_rectObjTemp[flag_findnum].height();

        left = left+x;
        top = top+y;
        if(left<0)
            left = 0;
        if(left+width>this->width())
            left = this->width()-width;
        if(top<0)
            top = 0;
        if(top+height>this->height())
            top = this->height()-height;


        m_rectObjTemp[flag_findnum].setLeft(left) ;
        m_rectObjTemp[flag_findnum].setTop(top) ;
        m_rectObjTemp[flag_findnum].setWidth(width) ;
        m_rectObjTemp[flag_findnum].setHeight(height) ;





        if(top<30)
            label_rect[flag_findnum]->setGeometry(left ,top+height,100,30 );
        else
            label_rect[flag_findnum]->setGeometry(left ,top-30,100,30 );
        label_rect[flag_findnum]->show();
        before_pos =event->pos();
    }


}



void PlayWidget::mouseReleaseEvent(QMouseEvent* event)		//����ͼ�����Ǹı���С���ƶ���rect��������Ϊ����
{

if(ctrl_mode != DRAW_MODE)
    return;
    if(flag_draw ==DRAW_RECT)
    {//������ͼ����������
        if(m_iObjNum == 0)
            return;
        int left   = m_rectObjTemp[m_iObjNum-1].left();
        int top    = m_rectObjTemp[m_iObjNum-1].top();
        int width  = m_rectObjTemp[m_iObjNum-1].width();
        int height = m_rectObjTemp[m_iObjNum-1].height();
        if(width<0)
        {
            left = left+width;
            width=-width;
        }
        if(height<0)
        {
            top = height+top;
            height= -height;
        }

        if(width < 31)
        {

            int ret =QMessageBox::warning(this,"����","���¶����Ŀ��ȷ�Χ̫С! \n","ȷ��","ȡ��");
            if(ret == QMessageBox::AcceptRole)
            {
            width = 32;
            }
            else
            {
                m_rectObjTemp[m_iObjNum-1].setLeft(0) ;
                m_rectObjTemp[m_iObjNum-1].setTop(0) ;
                m_rectObjTemp[m_iObjNum-1].setWidth(0) ;
                m_rectObjTemp[m_iObjNum-1].setHeight(0) ;
                label_rect[m_iObjNum-1]->hide();
                m_iObjNum--;
                return;
            }
        }
        if(height < 31)
        {

            int ret =QMessageBox::warning(this,"����","���¶����ĸ߶ȷ�Χ̫С! \n","ȷ��","ȡ��");
            if(ret == QMessageBox::AcceptRole)
            {
                height = 32;
            }
            else
            {
                    m_rectObjTemp[m_iObjNum-1].setLeft(0) ;
                    m_rectObjTemp[m_iObjNum-1].setTop(0) ;
                    m_rectObjTemp[m_iObjNum-1].setWidth(0) ;
                    m_rectObjTemp[m_iObjNum-1].setHeight(0) ;
                    if(m_iObjNum>0)
                    {
                        label_rect[m_iObjNum-1]->hide();
                        m_iObjNum--;
                    }
                    return;
            }
        }

        m_rectObjTemp[m_iObjNum-1].setLeft(left) ;
        m_rectObjTemp[m_iObjNum-1].setTop(top) ;
        m_rectObjTemp[m_iObjNum-1].setWidth(width) ;
        m_rectObjTemp[m_iObjNum-1].setHeight(height) ;
        if(m_rectObjTemp[m_iObjNum-1].y()<30)
            label_rect[m_iObjNum-1]->setGeometry(m_rectObjTemp[m_iObjNum-1].left() ,m_rectObjTemp[m_iObjNum-1].top()+m_rectObjTemp[m_iObjNum-1].height(),100,30 );
        else
            label_rect[m_iObjNum-1]->setGeometry(m_rectObjTemp[m_iObjNum-1].left() ,m_rectObjTemp[m_iObjNum-1].top()-30 ,100,30 );

    }
    else if(flag_draw == DRAW_POINT)
    {
       // lb_point.setText(" ");
       // lb_point.hide();
       lb_point[m_iPointNum-1].setGeometry(event->pos().x() ,event->pos().y()-20 ,50,30 );
        m_pointObj[m_iPointNum-1].setX(event->pos().x()) ;
		m_pointObj[m_iPointNum-1].setY(event->pos().y()) ;
        update();

    }
    else
    {
        //�����ƶ��͸ı���С��ͼ����������
        if(flag_findnum ==-1)
                return;
        int left	 = m_rectObjTemp[flag_findnum].left();
        int top 	=  m_rectObjTemp[flag_findnum].top();
        int width=m_rectObjTemp[flag_findnum].width();
        int height =m_rectObjTemp[flag_findnum].height();

        if(width<0)
        {
            left = left+width;
            width = -width;
        }
        if(height<0)
        {
            top = top +height;
            height = -height;
        }

        if(left<5)
            left = 5;

        if(top<5)
            top = 5;

            if(width < 31 )
            {
                int ret =QMessageBox::warning(this,"warning","width is too small !\n","OK","cancel");
                if(ret == QMessageBox::AcceptRole)
                {
                    width = 32;
                }
                else
                {
                    width =flag_width;
                    height=flag_height ;
                }
            }
            if(height < 31 )
            {
                int ret = QMessageBox::warning(this,"warning","height is too low!\n","OK","cancel");
                if(ret == QMessageBox::AcceptRole)
                {
                    height = 32;
                }
                else
                {
                    width =flag_width;
                    height=flag_height ;
                }
            }

        /*************************���� �޸�ʱ��2013-10-24*********************************************************************/
            if(left+width>this->width() - 5)
                width = this->width()-left-5;

            if(top+height>this->height() - 5)
                height =	this->height()-top-5;

    /*************************���� �޸�ʱ��2013-10-24*********************************************************************/

        m_rectObjTemp[flag_findnum].setLeft(left);
        m_rectObjTemp[flag_findnum].setTop(top);
        m_rectObjTemp[flag_findnum].setWidth(width);
        m_rectObjTemp[flag_findnum].setHeight(height);
        if(top<30)
            label_rect[flag_findnum]->setGeometry(m_rectObjTemp[flag_findnum].left(),m_rectObjTemp[flag_findnum].top()+m_rectObjTemp[flag_findnum].height(),100,30 );
        else
            label_rect[flag_findnum]->setGeometry(m_rectObjTemp[flag_findnum].left(),m_rectObjTemp[flag_findnum].top()-30,100,30 );
    }
    flag_height = 0;
    flag_width = 0;
    flag_findnum = -1;
    flag_draw =DRAW_NO;




}


void PlayWidget::paintEvent(QPaintEvent *)
{
    if(m_play == true)
    {


        QPainter painterImage(this);
        QRect rect_image(0,0,this->width(),this->height());
        QImage pixImg;
        mutex_bmp.lock();
        pixImg.loadFromData((unsigned char *)&m_Bmpfile+2,sizeof(BMPFLIE),0);
        painterImage.drawImage(rect_image,pixImg);
        if(m_grap)
        {
            pixImg.save(m_file);
            m_grap = false;
        }

        painterImage.setPen(pen);
        painterImage.drawLine(m_Covertframe.iParam[PARAM_MAX_X]-5,m_Covertframe.iParam[PARAM_MAX_Y],m_Covertframe.iParam[PARAM_MAX_X]+5,m_Covertframe.iParam[PARAM_MAX_Y]);
        painterImage.drawLine(m_Covertframe.iParam[PARAM_MAX_X],m_Covertframe.iParam[PARAM_MAX_Y]-5,m_Covertframe.iParam[PARAM_MAX_X],m_Covertframe.iParam[PARAM_MAX_Y]+5);

        mutex_bmp.unlock();
        painterImage.end();
    }

/*
    QPainter painterImage(this);
            QRect rect_image(0,0,this->width(),this->height());
            QImage pixImg;

    pixImg.load("bmp/2.bmp");
    painterImage.drawImage(rect_image,pixImg);
*/

    QPainter painterRect(this);

    painterRect.setPen(Qt::red);

    for(int rectNum = 0;rectNum< MAX_OBJ_NUM;rectNum++)
    {

        painterRect.drawRect(m_rectObjTemp[rectNum]);
    }

    painterRect.end();                        //�ͷ���Դ��Ϊֻ��һֱ���ϻ���û���ͷţ�ʹ���Կ���
    return ;

}

PlayWidget::~PlayWidget()
{
    if(pFrame !=NULL)
        free(pFrame);
    pFrame = NULL;
}

