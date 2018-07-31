#include "dialogxingli.h"
#include "ui_dialogxingli.h"

DialogXingLi::DialogXingLi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogXingLi)
{
    ui->setupUi(this);
    setWindowTitle("星历数据编辑");
    modelXingLi =new QStandardItemModel();
    ui->tableView_XingLi->setModel(modelXingLi);
    setXingLiTableHeader();
    xingLiDataList.clear();
    xingLiTableSelectedRow = -1;

}

DialogXingLi::~DialogXingLi()
{
    delete ui;
}

void DialogXingLi::on_pushButton_ok_clicked()
{
    QList<QString> needWriteList;
    needWriteList.clear();

    QString str1 ="POD_EPH_VERS";
    QString str2 ="";
    QString str3 = "";
    QString strEqual = " = ";
    QString str3Space = "   ";
    QString str1Space = " ";
    QString str2Space = " ";
    QString str4Space = "    ";
    QString str6Space = "      ";

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

    str1 = "OBJECT_CATNUM";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->OBJECT_CATNUM->text();
    needWriteList.append(str3);

    str1 = "TIME_SYSTEM";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->TIME_SYSTEM->text();
    needWriteList.append(str3);

    str1 = "CENTER_NAME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->CENTER_NAME->text();
    needWriteList.append(str3);

    str1 = "REF_FRAME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->REF_FRAME->text();
    needWriteList.append(str3);

    str1 = "START_TIME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->START_TIME->text();
    needWriteList.append(str3);

    str1 = "END_TIME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + ui->END_TIME->text();
    needWriteList.append(str3);

    str3 = "DATA_START";
    needWriteList.append(str3);

    for(int i=0;i<xingLiDataList.size();i++)
    {
       str1 = xingLiDataList[i].time;
       str2 = strTo_n_Width_left(str1,27);
       str3 =str2+str1Space;

       str1 = xingLiDataList[i].MJD;
       str2 = strTo_n_Width_right(str1,6);
       str3 = str3 + str2 +str2Space;

       str1 = xingLiDataList[i].JS;
       str2 = strTo_n_Width_right(str1,11);
       str3 = str3 + str2 +str4Space;

       str1 = xingLiDataList[i].pos_x;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 +str3Space;

       str1 = xingLiDataList[i].pos_y;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 +str4Space;

       str1 = xingLiDataList[i].pos_z;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 +str4Space;

       str1 = xingLiDataList[i].speed_x;
       str2 = strTo_n_Width_right(str1,13);
       str3 = str3 + str2 +str6Space;

       str1 = xingLiDataList[i].speed_y;
       str2 = strTo_n_Width_right(str1,11);
       str3 = str3 + str2 +str6Space;

       str1 = xingLiDataList[i].speed_z;
       str2 = strTo_n_Width_right(str1,11);
       str3 = str3 + str2 +str1Space;

       str1 = xingLiDataList[i].accelerat_x;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 +str1Space;

       str1 = xingLiDataList[i].accelerat_y;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 +str1Space;

       str1 = xingLiDataList[i].accelerat_z;
       str2 = strTo_n_Width_right(str1,15);
       str3 = str3 + str2 ;

       needWriteList.append(str3);

    }

    str3 = "DATA_STOP";
    needWriteList.append(str3);

    emit sendXingLiData(needWriteList);
    this->close();
}

void DialogXingLi::on_pushButton_cancel_clicked()
{
    this->close();
}

void DialogXingLi::setXingLiTableHeader() //设置PLANET表格的表格头部文字
{
    QStringList list ;
    list.append("时间");
    list.append("MJD");
    list.append("日积秒");

    list.append("x");
    list.append("y");
    list.append("z");

    list.append("vx");
    list.append("vy");
    list.append("vz");

    list.append("ax");
    list.append("ay");
    list.append("az");


    modelXingLi->setHorizontalHeaderLabels(list);
    ui->tableView_XingLi->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView_PLANET->setColumnWidth(0,100);
//    ui->tableView_PLANET->setColumnWidth(1,115);
//    ui->tableView_PLANET->setColumnWidth(2,100);


}

void DialogXingLi::updateXingLiTableData()//更新星历表格数据
{
    modelXingLi->clear();
    setXingLiTableHeader();
    xingLiTableSelectedRow = -1;
    int size = xingLiDataList.size();
    for(int i=0;i<size;i++)
    {
        int j=0;
        QString str = xingLiDataList[i].time;
        QStandardItem*  tempItem0 = new QStandardItem(str);
        tempItem0->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem0);

        j=j+1;
        str = xingLiDataList[i].MJD;
        QStandardItem*  tempItem1 = new QStandardItem(str);
        tempItem1->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem1);

        j=j+1;
        str = xingLiDataList[i].JS;
        QStandardItem*  tempItem2 = new QStandardItem(str);
        tempItem2->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem2);

        j=j+1;
        str = xingLiDataList[i].pos_x;
        QStandardItem*  tempItem3 = new QStandardItem(str);
        tempItem3->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem3);

        j=j+1;
        str = xingLiDataList[i].pos_y;
        QStandardItem*  tempItem4 = new QStandardItem(str);
        tempItem4->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem4);

        j=j+1;
        str = xingLiDataList[i].pos_z;
        QStandardItem*  tempItem5 = new QStandardItem(str);
        tempItem5->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem5);

        j=j+1;
        str = xingLiDataList[i].speed_x;
        QStandardItem*  tempItem6 = new QStandardItem(str);
        tempItem6->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem6);

        j=j+1;
        str = xingLiDataList[i].speed_y;
        QStandardItem*  tempItem7 = new QStandardItem(str);
        tempItem7->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem7);

        j=j+1;
        str = xingLiDataList[i].speed_z;
        QStandardItem*  tempItem8 = new QStandardItem(str);
        tempItem8->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem8);

        j=j+1;
        str = xingLiDataList[i].accelerat_x;
        QStandardItem*  tempItem9 = new QStandardItem(str);
        tempItem9->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem9);

        j=j+1;
        str = xingLiDataList[i].accelerat_y;
        QStandardItem*  tempItem10 = new QStandardItem(str);
        tempItem10->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem10);

        j=j+1;
        str = xingLiDataList[i].accelerat_z;
        QStandardItem*  tempItem11 = new QStandardItem(str);
        tempItem11->setBackground(QColor(192,192,192));
        modelXingLi->setItem(i,j,tempItem11);


    }
}

void DialogXingLi::on_pushButton_addData_clicked()
{
    XingLiDesc  tempObj;
    tempObj.time = ui->data_time->text();
    tempObj.MJD = ui->data_MJD->text();
    tempObj.JS = ui->data_JS->text();
    tempObj.pos_x = ui->position_x->text();
    tempObj.pos_y = ui->position_y->text();
    tempObj.pos_z = ui->position_z->text();
    tempObj.speed_x = ui->speed_x->text();
    tempObj.speed_y = ui->speed_y->text();
    tempObj.speed_z = ui->speed_z->text();
    tempObj.accelerat_x = ui->accelerate_x->text();
    tempObj.accelerat_y = ui->accelerate_y->text();
    tempObj.accelerat_z = ui->accelerate_z->text();
    xingLiDataList.append(tempObj);
    updateXingLiTableData();

}

void DialogXingLi::on_tableView_XingLi_clicked(const QModelIndex &index)
{
    xingLiTableSelectedRow = index.row();
}

void DialogXingLi::on_pushButton_delData_clicked()
{
    if(xingLiTableSelectedRow>=0 && xingLiTableSelectedRow<xingLiDataList.size())
    {
        xingLiDataList.removeAt(xingLiTableSelectedRow);
        updateXingLiTableData();
    }
}

void DialogXingLi::on_pushButton_refreshData_clicked()
{
    updateXingLiTableData();
}

void DialogXingLi::on_pushButton_saveData_clicked()
{
    if(xingLiTableSelectedRow>=0 && xingLiTableSelectedRow<xingLiDataList.size())
    {
        int i=0;
        for(i=0;i<xingLiDataList.size();i++)
        {
            QModelIndex index = modelXingLi->index(i,0);
            QVariant data = modelXingLi->data(index);
            QString str = data.toString();
            xingLiDataList[i].time =str;

            index = modelXingLi->index(i,1);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].MJD = str ;

            index = modelXingLi->index(i,2);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].JS = str ;

            index = modelXingLi->index(i,3);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].pos_x = str ;

            index = modelXingLi->index(i,4);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].pos_y = str ;

            index = modelXingLi->index(i,5);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].pos_z = str ;

            index = modelXingLi->index(i,6);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].speed_x = str ;

            index = modelXingLi->index(i,7);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].speed_y = str ;

            index = modelXingLi->index(i,8);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].speed_z = str ;

            index = modelXingLi->index(i,9);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].accelerat_x = str ;

            index = modelXingLi->index(i,10);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].accelerat_y = str ;

            index = modelXingLi->index(i,11);
            data = modelXingLi->data(index);
            str = data.toString();
            xingLiDataList[i].accelerat_z = str ;

        }

        updateXingLiTableData();
    }
}

QString  DialogXingLi::strTo_19_Width(QString strConvert)//将一个字符串变成长度为19的字符串，右补空格
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

QString  DialogXingLi::strTo_n_Width_left(QString strConvert, int n)
{
    QString str1=strConvert;
    int len = str1.length();
    int firstWidth = n;
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

QString  DialogXingLi::strTo_n_Width_right(QString strConvert, int n)
{
    QString str1=strConvert;
    int len = str1.length();
    int firstWidth = n;
    if(len<firstWidth)
    {
        for(int i=0;i<(firstWidth-len);i++)
        {
            str1=" "+str1;
        }

        return str1;
    }else
    {
        return str1;
    }


}
