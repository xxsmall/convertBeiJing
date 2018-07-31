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
