#include "dialogttcdata.h"
#include "ui_dialogttcdata.h"

DialogTTCData::DialogTTCData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTTCData)
{
    ui->setupUi(this);
    this->setWindowTitle("测量数据编辑");
    modelStation =new QStandardItemModel();
    ui->tableView_station->setModel(modelStation);
    setStationTableHeader();
    stationSelectedRow = -1;
    ttcStationList.clear();

    modelFile = new QStandardItemModel();
    ui->tableView_fileList->setModel(modelFile);
    setFileTableHeader();
    fileSelectedRow = -1;
    ttcFileList.clear();
}

DialogTTCData::~DialogTTCData()
{
    delete ui;
}

void DialogTTCData::on_pushButton_ok_clicked()
{
    QList<QString> needWriteList;
    needWriteList.clear();

    QString str1 ="POD_OBS_VERS";
    QString str2 ="";
    QString str3 = "";
    QString strEqual = " = ";
    QString str3Space = "   ";

    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + "1.0";
    needWriteList.append(str3);

    str1 = "CREATION_DATA";
    str2 = strTo_19_Width(str1);
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-ddThh:mm:ss.zzz");
    str3 = str2 + strEqual + current_date;
    needWriteList.append(str3);

    str1 = "ORIGINATOR";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + "XingYi";
    needWriteList.append(str3);

    str3 = "META_START";
    needWriteList.append(str3);

    str1 = "OBJECT_NAME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBJECT_NAME->text();
    needWriteList.append(str3);

    str1 = "OBJECT_ID";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBJECT_ID->text();
    needWriteList.append(str3);

    str1 = "OBJECT_CATNUM";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBJECT_CATNUM->text();
    needWriteList.append(str3);

    str1 = "TIME_SYSTEM";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->TIME_SYSTEM->text();
    needWriteList.append(str3);

    str1 = "OBS_START_TIME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBS_START_TIME->text();
    needWriteList.append(str3);

    str1 = "OBS_END_TIME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBS_END_TIME->text();
    needWriteList.append(str3);

    str1 = "SC_TRANS_FRE";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->SC_TRANS_FRE->text();
    needWriteList.append(str3);

    for(int i=0;i<ttcStationList.size();i++)
    {
        str1 = "TTC_FAC_ID";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + ttcStationList[i].TTC_FAC_ID;
        needWriteList.append(str3);

        if( !ttcStationList[i].REC_REF_FRE.isEmpty() )
        {
            str1 = "REC_REF_FRE";
            str2 = strTo_19_Width(str1);
            str3 = str2 + strEqual + ttcStationList[i].REC_REF_FRE;
            needWriteList.append(str3);
        }


        if( !ttcStationList[i].TTC_TRANS_FRE.isEmpty() )
        {
            str1 = "TTC_TRANS_FRE";
            str2 = strTo_19_Width(str1);
            str3 = str2 + strEqual + ttcStationList[i].TTC_TRANS_FRE;
            needWriteList.append(str3);

            str1 = "TURN_RATIO";
            str2 = strTo_19_Width(str1);
            str3 = str2 + strEqual + ttcStationList[i].TURN_RATIO;
            needWriteList.append(str3);

            str1 = "TRS_START_TIME";
            str2 = strTo_19_Width(str1);
            str3 = str2 + strEqual + ttcStationList[i].TRS_START_TIME;
            needWriteList.append(str3);

            str1 = "TRS_END_TIME";
            str2 = strTo_19_Width(str1);
            str3 = str2 + strEqual + ttcStationList[i].TRS_END_TIME;
            needWriteList.append(str3);
        }

    }

    str3 = "META_STOP";
    needWriteList.append(str3);

    str3 = "DATA_START";
    needWriteList.append(str3);

    ////增加数据处理部分，核心部分

    str3 = "DATA_STOP";
    needWriteList.append(str3);

    emit sendTTCData(needWriteList);
    this->close();
}

void DialogTTCData::on_pushButton_cancel_clicked()
{
    this->close();
}

void DialogTTCData::setStationTableHeader() //设置station表格的表格头部文字
{

    QStringList list ;
    list.append("测站编号");
    list.append("接收参考频率");
    list.append("测站发射频率");
    list.append("信号转发比");
    list.append("使用此发射频率的开始时间");
    list.append("使用此发射频率的结束时间");


    modelStation->setHorizontalHeaderLabels(list);
    ui->tableView_station->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_station->setColumnWidth(0,100);
//    ui->tableView_station->setColumnWidth(1,115);
//    ui->tableView_station->setColumnWidth(2,100);


}

void  DialogTTCData::updateStationTableData()//更新station表格数据
{
    modelStation->clear();
    setStationTableHeader();
    stationSelectedRow = -1;
    int size = ttcStationList.size();
    for(int i=0;i<size;i++)
    {
        int j=0;
        QString str = ttcStationList[i].TTC_FAC_ID;
        QStandardItem*  tempItem0 = new QStandardItem(str);
        tempItem0->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem0);

        j=j+1;
        str = ttcStationList[i].REC_REF_FRE;
        QStandardItem*  tempItem1 = new QStandardItem(str);
        tempItem1->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem1);

        j=j+1;
        str = ttcStationList[i].TTC_TRANS_FRE;
        QStandardItem*  tempItem2 = new QStandardItem(str);
        tempItem2->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem2);

        j=j+1;
        str = ttcStationList[i].TURN_RATIO;
        QStandardItem*  tempItem3 = new QStandardItem(str);
        tempItem3->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem3);

        j=j+1;
        str = ttcStationList[i].TRS_START_TIME;
        QStandardItem*  tempItem4 = new QStandardItem(str);
        tempItem4->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem4);

        j=j+1;
        str = ttcStationList[i].TRS_END_TIME;
        QStandardItem*  tempItem5 = new QStandardItem(str);
        tempItem5->setBackground(QColor(192,192,192));
        modelStation->setItem(i,j,tempItem5);

    }

}



void DialogTTCData::on_pushButton_addStation_clicked()
{
    ttcStationDesc tempObj;
    tempObj.TTC_FAC_ID = ui->TTC_FAC_ID->text();
    if(ui->checkBox_REC_REF_FRE->isChecked())
    {
        tempObj.REC_REF_FRE = ui->REC_REF_FRE->text();
    }else
    {
        tempObj.REC_REF_FRE = "" ;
    }

    if(ui->checkBox_TTC_TRANS_FRE->isChecked())
    {
        tempObj.TTC_TRANS_FRE = ui->TTC_TRANS_FRE->text();
        tempObj.TURN_RATIO = ui->TURN_RATIO->text();
        tempObj.TRS_START_TIME = ui->TRS_START_TIME->text();
        tempObj.TRS_END_TIME = ui->TRS_END_TIME->text();
    }else
    {
        tempObj.TTC_TRANS_FRE = "" ;
        tempObj.TURN_RATIO ="" ;
        tempObj.TRS_START_TIME = "" ;
        tempObj.TRS_END_TIME = "" ;

    }
    ttcStationList.append(tempObj);

    updateStationTableData();
}


void DialogTTCData::on_pushButton_refreshStation_clicked()
{
    qDebug()<<stationSelectedRow;
    if(stationSelectedRow>=0 && stationSelectedRow<ttcStationList.size())
    {
        updateStationTableData();
    }
}

void DialogTTCData::on_tableView_station_clicked(const QModelIndex &index)
{
    stationSelectedRow = index.row();

}

void DialogTTCData::on_pushButton_delStation_clicked()
{
    qDebug()<<stationSelectedRow;
    if(stationSelectedRow>=0 && stationSelectedRow<ttcStationList.size())
    {
        ttcStationList.removeAt(stationSelectedRow);
        updateStationTableData();
    }
}

void DialogTTCData::on_pushButton_saveStation_clicked()
{
    if(stationSelectedRow>=0 && stationSelectedRow<ttcStationList.size())
    {
        int i=0;
        for(i=0;i<ttcStationList.size();i++)
        {
            QModelIndex index = modelStation->index(i,0);
            QVariant data = modelStation->data(index);
            QString str = data.toString();
            ttcStationList[i].TTC_FAC_ID =str;

            index = modelStation->index(i,1);
            data = modelStation->data(index);
            str = data.toString();
            ttcStationList[i].REC_REF_FRE = str ;

            index = modelStation->index(i,2);
            data = modelStation->data(index);
            str = data.toString();
            ttcStationList[i].TTC_TRANS_FRE = str ;

            index = modelStation->index(i,3);
            data = modelStation->data(index);
            str = data.toString();
            ttcStationList[i].TURN_RATIO = str ;

            index = modelStation->index(i,4);
            data = modelStation->data(index);
            str = data.toString();
            ttcStationList[i].TRS_START_TIME = str ;

            index = modelStation->index(i,5);
            data = modelStation->data(index);
            str = data.toString();
            ttcStationList[i].TRS_END_TIME = str ;

        }

        updateStationTableData();
    }
}

void DialogTTCData::on_checkBox_TTC_TRANS_FRE_clicked()
{
    bool ok = ui->checkBox_TTC_TRANS_FRE->isChecked();
    ui->checkBox_TURN_RATIO->setChecked(ok);
    ui->checkBox_TRS_START_TIME->setChecked(ok);
    ui->checkBox_TRS_END_TIME->setChecked(ok);

}

QString  DialogTTCData::strTo_19_Width(QString strConvert)
{
    QString str1=strConvert;
    int len = str1.length();
    int firstWidth =19;
    if(len<firstWidth)
    {
        for(int i=0;i<(firstWidth-len);i++)
        {
            str1=str1+" ";
        }

        return str1;
    }else
    {
        return str1;
    }

}

void  DialogTTCData::setFileTableHeader() //设置file表格的表格头部文字
{
    QStringList list ;
    list.append("文件名称");
    list.append("测站编码");
    list.append("卫星编码");


    modelFile->setHorizontalHeaderLabels(list);
    ui->tableView_fileList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_station->setColumnWidth(0,100);
//    ui->tableView_station->setColumnWidth(1,115);
//    ui->tableView_station->setColumnWidth(2,100);

}

void DialogTTCData::on_pushButton_selectFile_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"open file dialog","","");

    if(!fileName.isEmpty())
    {
        ui->lineEdit_newFilePath->setText(fileName);
    }
}

void DialogTTCData::on_pushButton_addFile_clicked()
{
    ttcDataFileDesc  tempObj;
    QString fileName = ui->lineEdit_newFilePath->text();
    QString id = ui->lineEdit_newStationID->text();
    QString num = ui->lineEdit_newSatNum->text();
    if(!fileName.isEmpty() && !id.isEmpty())
    {
        tempObj.fileName = fileName;
        tempObj.stationID = id ;
        tempObj.satNum = num;
        ttcFileList.append(tempObj);
        updateFileTableData();
    }else
    {
        QMessageBox::information(this,"warning","file name or id is empty,give up add");
    }
}

void  DialogTTCData::updateFileTableData()
{
    modelFile->clear();
    setFileTableHeader();
    fileSelectedRow = -1;
    int size = ttcFileList.size();
    for(int i=0;i<size;i++)
    {
        int j=0;
        QString str = ttcFileList[i].fileName;
        QStandardItem*  tempItem0 = new QStandardItem(str);
        tempItem0->setBackground(QColor(192,192,192));
        modelFile->setItem(i,j,tempItem0);

        j=j+1;
        str = ttcFileList[i].stationID;
        QStandardItem*  tempItem1 = new QStandardItem(str);
        tempItem1->setBackground(QColor(192,192,192));
        modelFile->setItem(i,j,tempItem1);

        j=j+1;
        str = ttcFileList[i].satNum;
        QStandardItem*  tempItem2 = new QStandardItem(str);
        tempItem2->setBackground(QColor(192,192,192));
        modelFile->setItem(i,j,tempItem2);
    }

}



void DialogTTCData::on_tableView_fileList_clicked(const QModelIndex &index)
{
    fileSelectedRow = index.row();
}

void DialogTTCData::on_pushButton_delFile_clicked()
{
    if(fileSelectedRow>=0 && fileSelectedRow<ttcFileList.size())
    {
        ttcFileList.removeAt(fileSelectedRow);
        updateFileTableData();
    }
}


QList<QString>   DialogTTCData::anlyseAllTTCFile()
{
    int size = ttcFileList.size();
    QList<QString> needWriteList;
    needWriteList.clear();

    for(int i=0;i<size;i++)
    {
        QString fileName = ttcFileList[i].fileName;
        QString id = ttcFileList[i].stationID;
        QString num = ttcFileList[i].satNum;
        QList<QString> thisFileList;
        thisFileList.clear();
        thisFileList = getEffectLineList(fileName);
        QList<QString> singleFileData;
        singleFileData.clear();

        singleFileData =  creatData(thisFileList,id,num);
        int sizeData = singleFileData.size();
        for(int j=0;j<sizeData;j++)
        {
            needWriteList.append(singleFileData[j]);

        }

    }
    return needWriteList;

}

QString  DialogTTCData::removeMoreSpace(QString str) //将每行连续的空格变为单个空格
{
    int size = str.length();
    QChar  a;
    QString strOut="";
    bool pastIsSpace=false;
    bool nowIsSpace=false;
    for(int i=0 ;i<size;i++)
    {

        a=str[i];
        if(a==' ')
        {
            nowIsSpace = true;
        }else
        {
            nowIsSpace = false;
        }

        if(nowIsSpace && pastIsSpace)
        {

        }else
        {
           strOut=strOut + a;
        }

        pastIsSpace = nowIsSpace ;
    }
    qDebug()<<strOut;
    return strOut;

}

QList<QString>  DialogTTCData::readFile(QString fileName)
{
    QFile file(fileName);
    QList<QString> dataList;
    dataList.clear();

    if(!file.open(QIODevice::ReadOnly))
    {
         return dataList;
    }
    QTextStream in(&file);

    int i=0;
    while(!in.atEnd())
    {
        QString onecount = in.readLine();
        i=i+1;
        dataList.append(onecount);
        //qDebug() << i <<"  "<< onecount;
    }
    file.close();
    return dataList;

}

QList<QString>  DialogTTCData::getEffectLineList(QString selectFile)
{
    QList<QString> resaultList;
    QList<QString> effectDataList;
    effectDataList.clear();

    resaultList =  readFile(selectFile);
    if(resaultList.size()>0)
    {
        for(int i=0;i<resaultList.size();i++)
        {
            QString strTemp = resaultList[i].trimmed();
            if(!strTemp.isEmpty()&& !strTemp.contains("------") && !strTemp.contains("Azimuth"))
            {
                if(strTemp.size() > 70)//测试文件每行97个字符
                {
                    qDebug()<<strTemp;
                    effectDataList.append(strTemp);
                }
            }


        }
    }

    return  effectDataList;

}

QList<QString>  DialogTTCData::creatData(QList<QString> dataList,QString stationNum,QString sateNum)//单个数据文件产生的数据集合
{

    QList<QString> reasultList;
    reasultList.clear();

    QString startTimeStr;
    QString endTimeStr;


    if(dataList.size() > 0)
    {
        for(int i=0;i<dataList.size();i++)
        //for(int i=0;i<1;i++)  //test use
        {
            QString strLine = dataList[i] ;
            strLine = removeMoreSpace(strLine);
            QStringList ttcDataList;
            ttcDataList.clear();
            ttcDataList = strLine.split(" ");
            //qDebug()<<ttcDataList.size();
            if(ttcDataList.size()>=8)
            {
                // "19 06 2018 07:24:15.560 62.176 0.000 2664.335687 -1.548055"
                //  0   1  2     3           4      5       6           7
                //   date        time        A      E       R          V
                float tE=0;
                QString str_tE=ttcDataList.at(5);
                tE = str_tE.toFloat();

                QString yearStr = ttcDataList.at(2);
                int year = yearStr.toInt();

                QString monthStr = ttcDataList.at(1);
                int     month = monthStr.toInt();

                QString dayStr = ttcDataList.at(0);
                int     day = dayStr.toInt();

                QDate dateTemp;
                dateTemp.setDate(year,month,day);

                qint64 JDdata = dateTemp.toJulianDay();

                dateTemp.setDate(1950,1,1);
                qint64 JD1950 = dateTemp.toJulianDay();

                qint64 MJD= JDdata - JD1950 ;
                qDebug()<<"简约儒略日："<<MJD<<JDdata<<JD1950;


//                QString timeStr;
//                timeStr = formatTime(ttcDataList);
//                //QDate dateObj()


//                QString cejuLine;
//                QString stk_ceju;
//                stk_ceju = ttcDataList.at(6);
//                cejuLine = makeCeJu(timeStr,stationNum,sateNum,stk_ceju);

//                QString cesuLine;
//                QString stk_cesu;
//                stk_cesu = ttcDataList.at(7);
//                cesuLine = makeCeSu(timeStr,stationNum,sateNum,stk_cesu);

//                QString strA;
//                QString strE;
//                QString cejiaoLine;
//                strA = ttcDataList.at(4);
//                strE = ttcDataList.at(5);
//                cejiaoLine = makeCeJiao(timeStr,stationNum,sateNum,strA,strE);

//                if(tE >= 5)
//                {
//                    reasultList.append(cejuLine);

//                    reasultList.append(cesuLine);

//                    reasultList.append(cejiaoLine);


//                }

            }

        }
    }

    return reasultList;
}

void DialogTTCData::on_pushButton_analyseFile_clicked()
{
    anlyseAllTTCFile();
}

double DialogTTCData::jde(int Y,int M,int D,int hour,int min,float sec)
{
    long int f,g,mid1,mid2;
    double J,JDE,A;

    if(M>=3)
    {
        f=Y;
        g=M;
    }

    if(M==1||M==2)
    {
        f=Y-1;
        g=M=12;
    }

    mid1=floor(365.25*f);
    mid2=floor(30.6001*(g+1));
    A=2-floor(f/100.0)+floor(f/400.0);
    J=mid1+mid2+D+A+1720994.5;
    JDE=J+hour/24.0+min/1440.0+sec/86400.0;
    return JDE;
}
