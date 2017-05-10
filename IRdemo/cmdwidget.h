#ifndef __CMDWIDGET_H
#define __CMDWIDGET_H


#include "ui_cmdwidget.h"
#include "IRCore.h"
#include "qglobal.h"

#pragma execution_character_set("utf-8")

typedef enum Command{
 msgAutoCal               = 10, //�Զ�����
 msgSetBpPos              = 11, //���û���λ��
 msgAddBp                 = 12, //���ӻ���
 msgSearchBpSwitch        = 13, //�һ���
 msgSetBpThresh           = 14, //��������
 msgClrBpList             = 15, //�廵��
 msgGetAdPPvalue          = 35, 
 msgGetADMaxMin           = 36, 
 msgGetFpaTemp            = 38, 
 msgSetGskIndex           = 20, 
 msgSyncTest              = 21,
 msgSyncSwitch            = 22,

 msgSetDeltFpaTemp        = 34, //�����¶�������
 msgSetAutoKBMode         = 35, //KBģʽ
 msgSetNucKIndex          = 36,
 msgSetNucBIndex          = 37,
 msgSetFinalBSeg          = 38,
 msgSetFinalKSeg          = 39,

 msgSetClkShift           = 50,
 msgSetFpaTmpOffse        = 51, //�����¶�ƫ��
 msgADAdjVaule            = 52, //AD����Ŀ��

 msgSetVBUS               = 61, //VBUS
 msgSetVDET               = 62, //VDET
 msgSetMirror             = 63, //����
 msgTestImageSel          = 64, //����ͼ��
 msgSetGFID               = 65, //GFID
 msgSetGSK                = 66, //GSK
 msgSetIntTime            = 67, //����ʱ��
 msgSetGain               = 68, //����
 msgSetSADDelay           = 69, //AD��ʱ
 msgGetFpgaTemp            = 70, //
 msgSetAutoGSKSwitch      = 71, //�Զ�����GSK
 msgVideoSrcSel           = 72, //���ͼ��
 msgCal                   = 73, //У׼
 msgInitK                 = 74, //��K
 msgSave                  = 75, //����
 msgSetFilterTCoef        = 76, //ʱ���˲�
 msgSetBpSwitch           = 77, //���㿪��
 msgShowDebug             = 78, //����
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
 msgSaveCfg               = 100,//����
 msgSampleADData          = 101,//AD����

 msgSetSensorOffsetHighThre     = 133,
 msgSetSensorOffsetLowThre      = 134,
 msgSetSensorOffsetLimit        = 135,
 msgSetSensorOffsetSwitch       = 136,
 msgSetGskAdjMethod             = 137,//GSK��������
 msgSetSaveGskTemp              = 138,
 msgSetGskFinalIndex            = 139,

 msgMeasureFlag           = 150,//���¿���
 msgManualAdjB            = 151,//�ֶ�����B
 msgUpLimitK              = 152,//K����
 msgDownLimitK            = 153,//K���� 
 msgSetDeltAD             = 154,
 msgManualAdjGeK          = 155,//�ֶ�����GeK
 msgManualAdjGeB          = 156,//�ֶ�����GeB
 msgManualAdjK            = 157,//�ֶ�����K

 msgSetCaliWorkMode       = 160,//����ģʽ
 msgGskUpdate             = 161,
 
 msgBadCol                 = 170,//������
 msgTempFloatIndex         = 171,//��Ư����
 msgTempFloatHigh          = 172,//��Ư����
 msgTempFloatLow           = 173,//��Ư����
 msgTempFloatFinalSeg      = 174,//����¾ƶ�

 msgBadRow                 = 175,//����
 msgSetMonitorThresh       = 176,//���ż������

 msgSetMinShutterInter     = 177,//������Сʱ��
 msgSetMaxShutterInter     = 178,//�������ʱ��

 msgSetTempFilterSwitch    = 180,//�¶��˲�����
 msgSetTempFilterThresh    = 181,//�¶��˲�����

 msgRemoveVLineSw          = 180,
 msgRemoveVLineThresh      = 181,

 msgTempEdition           = 191,//�¶Ȱ汾
 msgLogicEdition          = 192,//�߼��汾
 msgAppEdition            = 193,//Ӧ�ð汾
 msgSendFileBegin         = 194,//�����ļ���ʼ
 msgSendFileInc           = 195,//�����ļ� 
 msgSendFileEnd           = 196,//�����ļ�����
 msgSendFileAck           = 197,
 msgUbootMode             = 198,//����uboot
 msgUpdateWaitAck         = 199,
 msgUpdateTime            = 200,
 msgReboot                = 201,
 msgSetIp                 = 202,//����IP
 msgInqureIp              = 203,//��ѯIP
 msgSetMacLow             = 204,//����MAC��λ
 msgInqureMac             = 205,//��ѯMAC
 msgEthRxBroadcastEn      = 206,//
 msgInqureServerIp        = 207,//��ѯ����IP
 msgInqureServerPort      = 208,//��ѯ�����˿�
 msgSetServerIpPort       = 209,//����
 msgSetMacHigh            = 210,//����MAC��λ

 msgDigitalVideoSw        = 1000,//������Ƶ����



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

