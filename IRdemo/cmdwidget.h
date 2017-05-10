#ifndef __CMDWIDGET_H
#define __CMDWIDGET_H


#include "ui_cmdwidget.h"
#include "IRCore.h"
#include "qglobal.h"

#pragma execution_character_set("utf-8")

typedef enum Command{
 msgAutoCal               = 10, //自动补偿
 msgSetBpPos              = 11, //设置坏点位置
 msgAddBp                 = 12, //增加坏点
 msgSearchBpSwitch        = 13, //找坏点
 msgSetBpThresh           = 14, //坏点门限
 msgClrBpList             = 15, //清坏点
 msgGetAdPPvalue          = 35, 
 msgGetADMaxMin           = 36, 
 msgGetFpaTemp            = 38, 
 msgSetGskIndex           = 20, 
 msgSyncTest              = 21,
 msgSyncSwitch            = 22,

 msgSetDeltFpaTemp        = 34, //焦面温度灵敏度
 msgSetAutoKBMode         = 35, //KB模式
 msgSetNucKIndex          = 36,
 msgSetNucBIndex          = 37,
 msgSetFinalBSeg          = 38,
 msgSetFinalKSeg          = 39,

 msgSetClkShift           = 50,
 msgSetFpaTmpOffse        = 51, //焦面温度偏移
 msgADAdjVaule            = 52, //AD调整目标

 msgSetVBUS               = 61, //VBUS
 msgSetVDET               = 62, //VDET
 msgSetMirror             = 63, //镜像
 msgTestImageSel          = 64, //测试图像
 msgSetGFID               = 65, //GFID
 msgSetGSK                = 66, //GSK
 msgSetIntTime            = 67, //积分时间
 msgSetGain               = 68, //增益
 msgSetSADDelay           = 69, //AD延时
 msgGetFpgaTemp            = 70, //
 msgSetAutoGSKSwitch      = 71, //自动调整GSK
 msgVideoSrcSel           = 72, //输出图像
 msgCal                   = 73, //校准
 msgInitK                 = 74, //初K
 msgSave                  = 75, //保存
 msgSetFilterTCoef        = 76, //时域滤波
 msgSetBpSwitch           = 77, //坏点开关
 msgShowDebug             = 78, //调试
 msgGammaSwitch           = 79, 
 msgSetPalette            = 80, 
 msgSetGrayGain           = 81,
 msgSetGrayiBrightness    = 82,
 msgSetHistHighThre       = 83,
 msgSetHistLowThre        = 84,
 msgSetHistDecCoef        = 85,
 msgSetHistTotalPix       = 86,
 msgSetSharpSwitch        = 87,
 msgSetSharpCoef          = 88,
 msgSetTransparence       = 89,
 msgSetZoomFactor         = 90,
 msgSetAGCMode            = 91,
 msgSaveCfg               = 100,//保存
 msgSampleADData          = 101,//AD采样

 msgSetSensorOffsetHighThre     = 133,
 msgSetSensorOffsetLowThre      = 134,
 msgSetSensorOffsetLimit        = 135,
 msgSetSensorOffsetSwitch       = 136,
 msgSetGskAdjMethod             = 137,//GSK调整方法
 msgSetSaveGskTemp              = 138,
 msgSetGskFinalIndex            = 139,

 msgMeasureFlag           = 150,//测温开关
 msgManualAdjB            = 151,//手动调整B
 msgUpLimitK              = 152,//K上限
 msgDownLimitK            = 153,//K下限 
 msgSetDeltAD             = 154,
 msgManualAdjGeK          = 155,//手动调整GeK
 msgManualAdjGeB          = 156,//手动调整GeB
 msgManualAdjK            = 157,//手动调整K

 msgSetCaliWorkMode       = 160,//工作模式
 msgGskUpdate             = 161,
 
 msgBadCol                 = 170,//坏竖线
 msgTempFloatIndex         = 171,//温漂索引
 msgTempFloatHigh          = 172,//温漂高温
 msgTempFloatLow           = 173,//温漂低温
 msgTempFloatFinalSeg      = 174,//最后温酒段

 msgBadRow                 = 175,//坏线
 msgSetMonitorThresh       = 176,//快门监控门限

 msgSetMinShutterInter     = 177,//快门最小时间
 msgSetMaxShutterInter     = 178,//快门最大时间

 msgSetTempFilterSwitch    = 180,//温度滤波开关
 msgSetTempFilterThresh    = 181,//温度滤波门限

 msgRemoveVLineSw          = 180,
 msgRemoveVLineThresh      = 181,

 msgTempEdition           = 191,//温度版本
 msgLogicEdition          = 192,//逻辑版本
 msgAppEdition            = 193,//应用版本
 msgSendFileBegin         = 194,//发送文件开始
 msgSendFileInc           = 195,//发送文件 
 msgSendFileEnd           = 196,//发送文件结束
 msgSendFileAck           = 197,
 msgUbootMode             = 198,//进入uboot
 msgUpdateWaitAck         = 199,
 msgUpdateTime            = 200,
 msgReboot                = 201,
 msgSetIp                 = 202,//设置IP
 msgInqureIp              = 203,//查询IP
 msgSetMacLow             = 204,//设置MAC低位
 msgInqureMac             = 205,//查询MAC
 msgEthRxBroadcastEn      = 206,//
 msgInqureServerIp        = 207,//查询主机IP
 msgInqureServerPort      = 208,//查询主机端口
 msgSetServerIpPort       = 209,//连接
 msgSetMacHigh            = 210,//设置MAC高位

 msgDigitalVideoSw        = 1000,//数字视频开关



 user_msgMenuDisable      = 0x0192,
 user_msgCal              = 0x0202,
 user_msgAGCMode          = 0x011F,
 user_msgZoom             = 0x0240,
 user_msgPalette          = 0x0242,
 user_msgShowCurse        = 0x0243,
 user_msgSetContrast      = 0x0122,
 user_msgSetBrightness    = 0x0123,
 user_msgMenuShowAndSel   = 0x0292,
 user_msgMenuValueInc     = 0x0295,
 user_msgMenuValueDec     = 0x0296,
 FILE_TYPE_TYPEHEAD       = 1,
 FILE_TYPE_POWERON_IMAGE  = 2,
 FILE_TYPE_CODE_BIT       = 3,
 FILE_TYPE_K              = 4,
 FILE_TYPE_B              = 5,
 FILE_TYPE_BPLIST         = 6,
 FILE_TYPE_FILTER_COEF    = 7,
 FILE_TYPE_CODE_SREC      = 8,
 FILE_TYPE_TEMP_DATA      = 9,
 FILE_TYPE_SREC_DNA       = 10,

}eCmd;


typedef enum eButton{
    //user define
    msgSendCmd = 8000,
    msgView = 8001,
    msgSend = 8002,
    msgRecFileInc = 8003,
}eBtn;

class CmdWidget:public QWidget,public Ui_CmdWidget
{
	Q_OBJECT
public:
	CmdWidget(QWidget *parent = 0);	
	~CmdWidget();
    friend long  ConfigCallBack(long lData, long lParam);
    QButtonGroup btnGroup;
    CBF_IR pCBFconfig;
signals:
    void sigRecv(QString);
public slots:
	void IRCommand(int);
    void RecvMsg(QString);
private:
	char cmdStr[14];
    BOOL IsSendFile; //send file flag
    BOOL IsFileIncDone;//send fileinc flag
    void SendCommand(quint32 Cmd, quint32 Param);
    void SendCommandEx(quint32 u32Cmd,  quint8 * pBuff);
    void SendFile(const char * FilePath);
    void Delay(quint32 u32Delayms);
    int GetNum(char* str);
};



#endif

