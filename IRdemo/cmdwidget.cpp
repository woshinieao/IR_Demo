
#include "playwidget.h"
#include "cmdwidget.h"
#include "IRCore.h"
#include <QFileDialog>
#include "irmainwindow.h"
long  ConfigCallBack(long lData, long lParam)
{
    CmdWidget* pCmdWidget =&(((IrMainWindow *)lParam)->cmdWidget);
    QString str((char *)lData);
    emit pCmdWidget->sigRecv(str);
    return 0;
}

void CmdWidget::Delay(quint32 u32Delayms)
{
    QTime t;
    t.start();
    while(t.elapsed()<u32Delayms)
        QCoreApplication::processEvents();
}

int CmdWidget::GetNum(char *str)
{
    if(!strcmp(str,"msgInqureIp"))                   return msgInqureIp;
    if(!strcmp(str,"msgInqureMac"))               return msgInqureMac;
    if(!strcmp(str,"msgInqureServerIp"))        return msgInqureServerIp;
    if(!strcmp(str,"msgInqureServerPort"))    return msgInqureServerPort;
    if(!strcmp(str,"msgSaveCfg"))                    return msgSaveCfg;
    if(!strcmp(str,"msgLogicEdition"))             return msgLogicEdition;
    if(!strcmp(str,"msgAppEdition"))               return msgAppEdition;
    if(!strcmp(str,"msgTempEdition"))            return msgTempEdition;
    if(!strcmp(str,"msgSetIp"))                         return msgSetIp;
    if(!strcmp(str,"msgSetMacLow"))              return msgSetMacLow;
    if(!strcmp(str,"msgRecFileInc"))              return msgRecFileInc;
    return 0;
}

//send len is 4
void CmdWidget::SendCommand(uint u32Cmd, uint u32Param)
{
    IR_Command(0, u32Cmd, u32Param);
}

void CmdWidget::SendCommandEx(uint u32Cmd,  quint8 * pBuff)
{
           quint16 u16Len;
           char u8Send[2048] =   {'\0'};

           u16Len = sizeof(pBuff);
           u8Send[0] = 0xaa;  u8Send[1] = 0xaa; u8Send[2] = 0xaa; u8Send[3] = 0xaa;
           u8Send[4] = (u32Cmd >> 24) & 0xff;
           u8Send[5] = (u32Cmd >> 16) & 0xff;
           u8Send[6] = (u32Cmd >> 8) & 0xff;
           u8Send[7] = (u32Cmd >> 0) & 0xff;

//           if (IsSendFile == true) //send more 2 byte,need dec
           {
               u8Send[8] = ((u16Len-2) >> 8) & 0xff;
               u8Send[9] = (u16Len-2) & 0xff;
           }

           memcpy(&(u8Send[10]), pBuff, u16Len);

          IR_Send(0, u8Send, (u16Len+10) * sizeof(char));
}

void CmdWidget::SendFile(const char * FilePath)
{
#define PACKET_LEN      1024

    QFile file(FilePath);
    quint32 u32Cmd;
    quint32 u32Param;
    quint32 u32Loc;
    quint8   u8Buff[PACKET_LEN+2];
    quint32 u32FileLen;
    quint32 u32SendLen;
    quint32 u32Index;
    QByteArray ByteSend;

    //send begin
    u32Cmd = msgSendFileBegin;
    u32Param = file.size();
    SendCommand(u32Cmd, u32Param);
    Delay(50);

    //send file
    u32Index = 1;
    IsSendFile = true;
    u32Cmd = msgSendFileInc;
    u32FileLen = file.size();
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Error"), tr("Read File Error!!!"));
    }

    do
    {
        u32Loc = file.pos();

        if ((u32FileLen - u32Loc) > PACKET_LEN) u32SendLen = PACKET_LEN;
        else u32SendLen = u32FileLen - u32Loc;

        ByteSend = file.read(u32SendLen);
        memcpy(u8Buff,ByteSend.data(),u32SendLen);
        u8Buff[u32SendLen] = u32Index/256;
        u8Buff[u32SendLen+1] = u32Index%256;

        SendCommandEx(u32Cmd, u8Buff);
        IsSendFile = false;
        if (chk_transreply->checkState() == Qt::Checked)
        {
            Delay(10);
            while(IsFileIncDone == false)
            {
                Delay(5);
            }
        }
        else
        {
            Delay(80);
        }

        } while(!(file.atEnd()));

    file.close();

    //send end
    u32Cmd = msgSendFileEnd;
    u32Param = 1;
    SendCommand(u32Cmd, u32Param);
    Delay(50);
}

CmdWidget::CmdWidget(QWidget *parent):QWidget(parent)
{
	setupUi(this);
	pCBFconfig = &ConfigCallBack;

    //---------------------------------------------net-------------------------------------------
    btnGroup.addButton(btn_SetIp,msgSetIp);
    btnGroup.addButton(btn_inqureIP,msgInqureIp);
    btnGroup.addButton(btn_changeMac,msgSetMacLow);
    btnGroup.addButton(btn_inqureMac,msgInqureMac);
    btnGroup.addButton(btn_inqureHost,msgInqureServerIp);
    btnGroup.addButton(btnSaveNet,msgSaveCfg);
    btnGroup.addButton(chk_printAll,msgSaveCfg);
    //------------------------------------------------------updata/edition---------------------------------------
    btnGroup.addButton(btn_sendcmd,msgSendCmd);
    btnGroup.addButton(btn_editionBIT,msgLogicEdition);
    btnGroup.addButton(btn_editionSREC,msgAppEdition);
    btnGroup.addButton(btn_editionTEMP,msgTempEdition);
    btnGroup.addButton(btn_uboot,msgUbootMode);
    btnGroup.addButton(btn_view,msgView);
    btnGroup.addButton(btn_sendfile,msgSend);
/*
	btnGroup.addButton(btnAutoCal,msgAutoCal);
	btnGroup.addButton(btnSetBpPos,msgSetBpPos);
	btnGroup.addButton(btnAddBp,msgAddBp);
	btnGroup.addButton(btnSearchBpSwitch,msgSearchBpSwitch);
	btnGroup.addButton(btnSetBpThresh,msgSetBpThresh);
	btnGroup.addButton(btnClrBpList,msgClrBpList);
	btnGroup.addButton(btnGetAdPPvalue,msgGetAdPPvalue);
	btnGroup.addButton(btnGetADMaxMin,msgGetADMaxMin);
	btnGroup.addButton(btnGetFpaTemp,msgGetFpaTemp);
	btnGroup.addButton(btnSetGskIndex,msgSetGskIndex);
	btnGroup.addButton(btnSyncTest,msgSyncTest);
	btnGroup.addButton(btnSyncSwitch,msgSyncSwitch);
	btnGroup.addButton(btnSetDeltFpaTemp,msgSetDeltFpaTemp);
	btnGroup.addButton(btnSetAutoKBMode,msgSetAutoKBMode);
	btnGroup.addButton(btnSetNucKIndex,msgSetNucKIndex);
	btnGroup.addButton(btnSetNucBIndex,msgSetNucBIndex);
	btnGroup.addButton(btnSetFinalBSeg,msgSetFinalBSeg);
	btnGroup.addButton(btnSetFinalKSeg,msgSetFinalKSeg);


	btnGroup.addButton(btnSetClkShift,msgSetClkShift);
	btnGroup.addButton(btnSetFpaTmpOffse,msgSetFpaTmpOffse);
	btnGroup.addButton(btnADAdjVaule,msgADAdjVaule);
	btnGroup.addButton(btnSetVBUS,msgSetVBUS);
	btnGroup.addButton(btnSetVDET,msgSetVDET);

	btnGroup.addButton(btnSetMirror,msgSetMirror);
	btnGroup.addButton(btnTestImageSel,msgTestImageSel);
	btnGroup.addButton(btnSetGFID,msgSetGFID);
	btnGroup.addButton(btnSetGSK,msgSetGSK);




	btnGroup.addButton(btnSetIntTime,msgSetIntTime);
	btnGroup.addButton(btnSetGain,msgSetGain);
	btnGroup.addButton(btnSetSADDelay,msgSetSADDelay);
	btnGroup.addButton(btnGetFpgaTemp,msgGetFpgaTemp);
	btnGroup.addButton(btnSetAutoGSKSwitch,msgSetAutoGSKSwitch);
	btnGroup.addButton(btnVideoSrcSel,msgVideoSrcSel);
	btnGroup.addButton(btnCal,msgCal);
	btnGroup.addButton(btnInitK,msgInitK);
	btnGroup.addButton(btnSave,msgSave);
	btnGroup.addButton(btnSetFilterTCoef,msgSetFilterTCoef);
	btnGroup.addButton(btnSetBpSwitch,msgSetBpSwitch);
	btnGroup.addButton(btnShowDebug,msgShowDebug);
	btnGroup.addButton(btnGammaSwitch,msgGammaSwitch);
	btnGroup.addButton(btnSetPalette,msgSetPalette);
	btnGroup.addButton(btnSetGrayGain,msgSetGrayGain);
	btnGroup.addButton(btnSetGrayiBrightness,msgSetGrayiBrightness);
	btnGroup.addButton(btnSetHistHighThre,msgSetHistHighThre);
	btnGroup.addButton(btnSetHistLowThre,msgSetHistLowThre);
	btnGroup.addButton(btnSetHistDecCoef,msgSetHistDecCoef);
	btnGroup.addButton(btnSetHistTotalPix,msgSetHistTotalPix);
	btnGroup.addButton(btnSetSharpSwitch,msgSetSharpSwitch);
	btnGroup.addButton(btnSetSharpCoef,msgSetSharpCoef);
	btnGroup.addButton(btnSetTransparence,msgSetTransparence);
	btnGroup.addButton(btnSetZoomFactor,msgSetZoomFactor);
	btnGroup.addButton(btnSetAGCMode,msgSetAGCMode);

	btnGroup.addButton(btnSaveCfg,msgSaveCfg);
	btnGroup.addButton(btnSampleADData,msgSampleADData);




	btnGroup.addButton(btnSetSensorOffsetHighThre,msgSetSensorOffsetHighThre);
	btnGroup.addButton(btnSetSensorOffsetLowThre,msgSetSensorOffsetLowThre);
	btnGroup.addButton(btnSetSensorOffsetLimit,msgSetSensorOffsetLimit);
	btnGroup.addButton(btnSetSensorOffsetSwitch,msgSetSensorOffsetSwitch);
	btnGroup.addButton(btnSetGskAdjMethod,msgSetGskAdjMethod);
	btnGroup.addButton(btnSetSaveGskTemp,msgSetSaveGskTemp);
	btnGroup.addButton(btnSetGskFinalIndex,msgSetGskFinalIndex);
	btnGroup.addButton(btnMeasureFlag,msgMeasureFlag);
	btnGroup.addButton(btnManualAdjB,msgManualAdjB);
	btnGroup.addButton(btnUpLimitK,msgUpLimitK);
	btnGroup.addButton(btnDownLimitK,msgDownLimitK);
	btnGroup.addButton(btnSetDeltAD,msgSetDeltAD);
	btnGroup.addButton(btnManualAdjGeK,msgManualAdjGeK);
	btnGroup.addButton(btnManualAdjGeB,msgManualAdjGeB);
	btnGroup.addButton(btnManualAdjK,msgManualAdjK);


	btnGroup.addButton(btnSetCaliWorkMode,msgSetCaliWorkMode);
	btnGroup.addButton(btnGskUpdate,msgGskUpdate);
	btnGroup.addButton(btnBadCol,msgBadCol);
	btnGroup.addButton(btnTempFloatIndex,msgTempFloatIndex);
	btnGroup.addButton(btnTempFloatHigh,msgTempFloatHigh);
	btnGroup.addButton(btnTempFloatLow,msgTempFloatLow);
	btnGroup.addButton(btnTempFloatFinalSeg,msgTempFloatFinalSeg);
	btnGroup.addButton(btnBadRow,msgBadRow);
	btnGroup.addButton(btnSetMonitorThresh,msgSetMonitorThresh);


	btnGroup.addButton(btnSetMinShutterInter,msgSetMinShutterInter);
	btnGroup.addButton(btnSetMaxShutterInter,msgSetMaxShutterInter);
	btnGroup.addButton(btnSetTempFilterSwitch,msgSetTempFilterSwitch);
	btnGroup.addButton(btnSetTempFilterThresh,msgSetTempFilterThresh);
	btnGroup.addButton(btnRemoveVLineSw,msgRemoveVLineSw);
	btnGroup.addButton(btnRemoveVLineThresh,msgRemoveVLineThresh);
	btnGroup.addButton(btnTempEdition,msgTempEdition);
	btnGroup.addButton(btnLogicEdition,msgLogicEdition);
	btnGroup.addButton(btnAppEdition,msgAppEdition);
	btnGroup.addButton(btnSendFileBegin,msgSendFileBegin);
	btnGroup.addButton(btnSendFileInc,msgSendFileInc);
	btnGroup.addButton(btnSendFileEnd,msgSendFileEnd);
	btnGroup.addButton(btnSendFileAck,msgSendFileAck);
	btnGroup.addButton(btnUbootMode,msgUbootMode);
	btnGroup.addButton(btnUpdateWaitAck,msgUpdateWaitAck);
	btnGroup.addButton(btnUpdateTime,msgUpdateTime);
	btnGroup.addButton(btnReboot,msgReboot);
    //btnGroup.addButton(btnSetIp,msgSetIp);
	btnGroup.addButton(btnInqureIp,msgInqureIp);
	btnGroup.addButton(btnSetMacLow,msgSetMacLow);
	btnGroup.addButton(btnInqureMac,msgInqureMac);
	btnGroup.addButton(btnEthRxBroadcastEn,msgEthRxBroadcastEn);
	btnGroup.addButton(btnInqureServerIp,msgInqureServerIp);
	btnGroup.addButton(btnInqureServerPort,msgInqureServerPort);
	btnGroup.addButton(btnSetServerIpPort,msgSetServerIpPort);
	btnGroup.addButton(btnSetMacHigh,msgSetMacHigh);

	btnGroup.addButton(btnDigitalVideoSw,msgDigitalVideoSw);

	btnGroup.addButton(btnUsrMenuDisable,user_msgMenuDisable);
	btnGroup.addButton(btnUsrCal,user_msgCal);
	btnGroup.addButton(btnUsrAGCMode,user_msgAGCMode);
	btnGroup.addButton(btnUsrZoom,user_msgZoom);
	btnGroup.addButton(btnUsrPalette,user_msgPalette);
	btnGroup.addButton(btnUsrShowCurse,user_msgShowCurse);
	btnGroup.addButton(btnUsrSetContrast,user_msgSetContrast);
	btnGroup.addButton(btnUsrSetBrightness,user_msgSetBrightness);
	btnGroup.addButton(btnUsrMenuShowAndSel,user_msgMenuShowAndSel);
	btnGroup.addButton(btnUsrMenuValueInc,user_msgMenuValueInc);
	btnGroup.addButton(btnUsrMenuValueDec,user_msgMenuValueDec);
	btnGroup.addButton(btnFILE_TYPE_TYPEHEAD,FILE_TYPE_TYPEHEAD);
	btnGroup.addButton(btnFILE_TYPE_POWERON_IMAGE,FILE_TYPE_POWERON_IMAGE);
	btnGroup.addButton(btnFILE_TYPE_CODE_BIT,FILE_TYPE_CODE_BIT);
	btnGroup.addButton(btnFILE_TYPE_K,FILE_TYPE_K);
	btnGroup.addButton(btnFILE_TYPE_B,FILE_TYPE_B);
	btnGroup.addButton(btnFILE_TYPE_BPLIST,FILE_TYPE_BPLIST);
	btnGroup.addButton(btnFILE_TYPE_FILTER_COEF,FILE_TYPE_FILTER_COEF);
	btnGroup.addButton(btnFILE_TYPE_CODE_SREC,FILE_TYPE_CODE_SREC);
	btnGroup.addButton(btnFILE_TYPE_TEMP_DATA,FILE_TYPE_TEMP_DATA);
	btnGroup.addButton(btnFILE_TYPE_SREC_DNA,FILE_TYPE_SREC_DNA);
	connect(btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(IRCommand(int)));
*/
    connect(&btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(IRCommand(int)));
    connect(this,SIGNAL(sigRecv(QString)),this,SLOT(RecvMsg(QString)));
}

void CmdWidget::RecvMsg(QString strRecv)
{
    qint8  i8Pos;
    char  sCmd[20] = {0};
    char  sValue[20] =  {0};
    const char *sRecv;
    quint8  u8Len;

    sRecv = strRecv.toStdString().data();
    u8Len = strlen(sRecv);
   // qDebug("%s\n",sRecv);
    lt_recv->append(sRecv);
    i8Pos = strRecv.indexOf('=');

    if (i8Pos > 5)
    {
        memcpy(sCmd, (strRecv.left(i8Pos - 1)).toStdString().data(), i8Pos - 1); //delete space
        memcpy(sValue, (strRecv.right(u8Len - i8Pos - 2)).toStdString().data(), u8Len - i8Pos - 2); //delete space

        switch(GetNum(sCmd))
        {
        case msgInqureIp: le_Ip->setText(sValue);break;
        case msgInqureMac: le_Mac->setText(sValue);break;
        case msgInqureServerIp: le_HostIP->setText(sValue);break;
        case msgInqureServerPort: le_HostPort->setText(sValue);break;
        case msgSaveCfg: QMessageBox::information(this,"Tips",tr("保存成功 !"));break;
        case msgLogicEdition: le_editionBIT->setText(sValue);break;
        case msgAppEdition: le_editionSREC->setText(sValue);break;
        case msgTempEdition: le_editionTEMP->setText(sValue);break;
        case msgSetIp: QMessageBox::information(this,"提示",tr("IP修改成功，请断电重启相机!"));break;
        case msgSetMacLow: QMessageBox::information(this,"提示",tr("MAC修改成功，请断电重启相机!"));break;
        case msgRecFileInc: IsSendFile = true;
        default:break;
        }
    }
}

void CmdWidget::IRCommand(int cmd)
{
     quint32 u32Cmd;
     quint32 u32Param;
     QString FileName;
     switch(cmd)
     {
     //--------------------------------------------------net----------------------------------------------------------
        case msgSetIp:
        {
           QString ip =  le_Ip->text();
            QStringList strlist = ip.split(".");
            u32Cmd = msgSetIp;
            u32Param =  (strlist.at(0).toInt() << 24) |  (strlist.at(1).toInt() << 16) |  (strlist.at(2).toInt() << 8) | (strlist.at(3).toInt() << 0);
            SendCommand(u32Cmd, u32Param);
            break;
        }
        case msgInqureIp:  u32Cmd = msgInqureIp;  u32Param =  1;   SendCommand(u32Cmd, u32Param); break;
        case msgSetMacLow:
        {
            QString ip =  le_Ip->text();
            QStringList strlist = ip.split("-");
            u32Cmd = msgSetMacHigh;
            u32Param =  (strlist.at(3).toInt() << 24) |  (strlist.at(2).toInt() << 16) |  (strlist.at(1).toInt() << 8) | (strlist.at(0).toInt() << 0);
            SendCommand(u32Cmd, u32Param);
            Delay(50);
            u32Cmd = msgSetMacLow;
            u32Param =  (strlist.at(4).toInt() << 8) |  strlist.at(5).toInt();
            SendCommand(u32Cmd, u32Param);
            break;
        }
        case msgInqureMac: u32Cmd = msgInqureMac;  u32Param =  1;   SendCommand(u32Cmd, u32Param); break;
        case msgInqureServerIp: u32Cmd = msgInqureServerIp;  u32Param =  1;   SendCommand(u32Cmd, u32Param); Delay(50);
                                                    u32Cmd = msgInqureServerPort;  u32Param =  1;   SendCommand(u32Cmd, u32Param); break;
        case msgSaveCfg: u32Cmd = msgSaveCfg;  u32Param =  4;   SendCommand(u32Cmd, u32Param); break;

//-----------------------------------------------------updata/edition----------------------------------------------------------------------------
//         case msgSendCmd: u32Cmd = le_cmd->text().toint ; u32Param = le_param->text().toint; break;
        case msgLogicEdition: u32Cmd = msgLogicEdition; u32Param = 1; SendCommand(u32Cmd,u32Param); break;
        case msgAppEdition: u32Cmd = msgAppEdition; u32Param = 1; SendCommand(u32Cmd,u32Param); break;
        case msgTempEdition: u32Cmd = msgTempEdition; u32Param = 1; SendCommand(u32Cmd,u32Param); break;
        case msgUbootMode: u32Cmd = msgUbootMode; u32Param = 1; SendCommand(u32Cmd, u32Param); break;
        case msgView:
        {
            FileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/",tr("*"));
            qDebug()<<FileName;
//            for(int i = 0; i++ i < 3)
//            {
//                box_filetype.Selectedindex = i;
//                QString ::compare(fileName.right(3), )
//            }
              break;
        }
        case msgSend:
        {
            //get the box_filetype,judge the context
            SendFile(FileName.toStdString().data());
        }
        default: break;
    }
     qDebug("%x %x \n",u32Cmd, u32Param);

}
CmdWidget::~CmdWidget()
{


}

