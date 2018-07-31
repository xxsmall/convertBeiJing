#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("北京方向数据转换工具");
    //QStandardItemModel *   model   =   new   QStandardItemModel (ui->tableView_qiXiang );
    strEqual = " = ";
    firstWidth =19;
    strSpace2 = "  ";
    qiXiangObj = NULL ;
    orbitObj = NULL;
    xingLiObj =NULL ;
    ttcDataObj = NULL ;

    initStation();

    //初始化气象表格
    modelQiXiang = new QStandardItemModel();
    ui->tableView_qiXiang->setModel(modelQiXiang);
    setQiXiangTableHeader();
    qiXiangDataList.clear();
    qiXiangTableSelectedRow = -1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    CRDGEODETIC a1;
    a1.latitude = 35.3183;
    a1.longitude = 109.4 ;
    a1.altitude = 5.40822e-13;
    CRDCARTESIAN d2;
    XYZClass converObj;
    d2 = converObj.BLH_to_XYZ(a1);

    CRDGEODETIC a2;
    a2 = converObj.XYZ_to_BHL(d2);

    qDebug()<<a1.latitude<<a1.longitude<<a1.altitude;
    qDebug()<<d2.x<<d2.y<<d2.z;
    qDebug()<<a2.latitude<<a2.longitude<<a2.altitude;

    double x,y,z;
    gpsPoint2DescartesPoint(35.3183,109.4,5.40822e-13,x,y,z);
    qDebug()<<x<<y<<z;

    createStationFile();

    createQiXiangFile();

    createOrbitFile();

    createXingLiFile();

    createTTCFile();
}

void MainWindow::gpsPoint2DescartesPoint(const double latitude, const double longitude, const double altitude, double &x, double &y, double &z)
{
        //wgs84 WGS84 Earth Constants

        double wgs84a = 6378.137;

        double wgs84f = 1.0 / 298.257223563;

        double wgs84b = wgs84a * (1.0 - wgs84f);



        //earthcon

        double f = 1 - wgs84b / wgs84a;

        double eccsq = 1 - (wgs84b* wgs84b) / (wgs84a * wgs84a);

        double ecc = sqrt(eccsq);

        double esq = ecc * ecc;



        //llhxyz

        double dtr = M_PI / 180.0;

        //qDebug() << dtr << gpsPoint.latitude << endl;

        double clat = cos(dtr * latitude);

        double slat = sin(dtr * latitude);

        double clon = cos(dtr * longitude);

        double slon = sin(dtr * longitude);

        //qDebug() << clat << slon << endl;



        //radcur compute the radii at the geodetic latitude lat (in degrees)

        double dsq = 1.0 - eccsq * slat *slat;

        double d = sqrt(dsq);

        //qDebug() << d;

        double rn = wgs84a / d;

        double rm = rn * (1.0 - eccsq) / dsq;



        double rho = rn * clat;

        double zz = (1.0 - eccsq) * rn *slat;

        double rsq = rho * rho + zz*zz;

        double r = sqrt(rsq);



        x = (rn + altitude) * clat * clon;

        y = (rn + altitude) * clat * slon;

        z = ((1 - esq)*rn + altitude) * slat;


}

void MainWindow::on_listView_station_activated(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
}

void MainWindow::initStation()
{
    QStringList strList;
    strList.append("测站名称");
    stationSelected = -1;
    QStandardItemModel * model;
    model = new QStandardItemModel(4,1);
    QStandardItem *item1 = new QStandardItem("tongChuan");
    QStandardItem *item2 = new QStandardItem("sanYa");
    QStandardItem *item3 = new QStandardItem("jiaMuSi");
    QStandardItem *item4 = new QStandardItem("kaShi");
    stationParaList.clear();
    stationDesc tempStation;

    tempStation.name = "tongChuan" ;
    tempStation.x = "1" ;
    tempStation.deltaX = "0.01" ;
    tempStation.y = "1" ;
    tempStation.deltaY = "0.01" ;
    tempStation.z = "1" ;
    tempStation.deltaZ = "0.01" ;
    tempStation.id = "1001" ;
    stationParaList.append(tempStation);

    tempStation.name = "sanYa" ;
    tempStation.x = "2" ;
    tempStation.y = "2" ;
    tempStation.z = "2" ;
    tempStation.deltaX = "0.01" ;
    tempStation.deltaY = "0.01" ;
    tempStation.deltaZ = "0.01" ;
    tempStation.id = "1002" ;
    stationParaList.append(tempStation);


    tempStation.name = "jiaMuSi" ;
    tempStation.x = "3" ;
    tempStation.y = "3" ;
    tempStation.z = "3" ;
    tempStation.deltaX = "0.01" ;
    tempStation.deltaY = "0.01" ;
    tempStation.deltaZ = "0.01" ;
    tempStation.id = "1003" ;
    stationParaList.append(tempStation);


    tempStation.name = "kaShi" ;
    tempStation.x = "4" ;
    tempStation.y = "4" ;
    tempStation.z = "4" ;
    tempStation.deltaX = "0.01" ;
    tempStation.deltaY = "0.01" ;
    tempStation.deltaZ = "0.01" ;
    tempStation.id = "1004" ;
    stationParaList.append(tempStation);


    model->setItem(0, 0, item1);
    model->setItem(1, 0, item2);
    model->setItem(2, 0, item3);
    model->setItem(3, 0, item4);
    ui->listView_station->setModel(model);

    ui->lineEdit_sName->setDisabled(true);
    ui->lineEdit_sX->setDisabled(true);
    ui->lineEdit_sY->setDisabled(true);
    ui->lineEdit_sZ->setDisabled(true);
    ui->lineEdit_sXdelta->setDisabled(true);
    ui->lineEdit_sYdelta->setDisabled(true);
    ui->lineEdit_sZdelta->setDisabled(true);
    ui->lineEdit_sID->setDisabled(true);
    ui->pushButton_SNew->setDisabled(true);
    ui->listView_station->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_listView_station_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column()<<endl;
    int i = index.row();
    stationSelected = i ;
    QPoint p;
    p.setX(index.row());
    p.setY(index.column());
    QModelIndex posIndex = ui->listView_station->indexAt(p);
    QVariant variant =  ui->listView_station->model()->data(index, Qt::DisplayRole);
    ui->lineEdit_sName->setText(stationParaList[i].name);
    ui->lineEdit_sX->setText(stationParaList[i].x);
    ui->lineEdit_sY->setText(stationParaList[i].y);
    ui->lineEdit_sZ->setText(stationParaList[i].z);
    ui->lineEdit_sXdelta->setText(stationParaList[i].deltaX);
    ui->lineEdit_sYdelta->setText(stationParaList[i].deltaY);
    ui->lineEdit_sZdelta->setText(stationParaList[i].deltaZ);
    ui->lineEdit_sID->setText(stationParaList[i].id);

    qDebug()<<variant.toString();
}

void MainWindow::on_pushButton_SFix_clicked()
{
    if(stationSelected>=0 && stationSelected<stationParaList.size())
    {
        ui->lineEdit_sName->setDisabled(false);
        ui->lineEdit_sX->setDisabled(false);
        ui->lineEdit_sY->setDisabled(false);
        ui->lineEdit_sZ->setDisabled(false);
        ui->lineEdit_sXdelta->setDisabled(false);
        ui->lineEdit_sYdelta->setDisabled(false);
        ui->lineEdit_sZdelta->setDisabled(false);
        ui->lineEdit_sID->setDisabled(false);
    }
}

void MainWindow::on_pushButton_SSave_clicked()
{
    if(stationSelected>=0 && stationSelected<stationParaList.size() )
    {
        stationParaList[stationSelected].name = ui->lineEdit_sName->text();
        stationParaList[stationSelected].x = ui->lineEdit_sX->text();
        stationParaList[stationSelected].y = ui->lineEdit_sY->text();
        stationParaList[stationSelected].z = ui->lineEdit_sZ->text();
        stationParaList[stationSelected].deltaX = ui->lineEdit_sXdelta->text();
        stationParaList[stationSelected].deltaY = ui->lineEdit_sYdelta->text();
        stationParaList[stationSelected].deltaZ = ui->lineEdit_sZdelta->text();
        stationParaList[stationSelected].id = ui->lineEdit_sID->text();

        ui->lineEdit_sName->setDisabled(true);
        ui->lineEdit_sX->setDisabled(true);
        ui->lineEdit_sY->setDisabled(true);
        ui->lineEdit_sZ->setDisabled(true);
        ui->lineEdit_sID->setDisabled(true);
        ui->lineEdit_sXdelta->setDisabled(true);
        ui->lineEdit_sYdelta->setDisabled(true);
        ui->lineEdit_sZdelta->setDisabled(true);
    }
}

void   MainWindow::createStationFile()
{
    QList<QString> needWriteList;
    needWriteList.clear();

    QString str1 ="POD_TTC_VERS";
    QString str2 ="";
    QString str3 = "";
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

    str1 = "REF_FRAME";
    str2 = strTo_19_Width(str1);
    str3 = str2 + strEqual + "ITRF2000";
    needWriteList.append(str3);

    for(int i=0;i<stationParaList.size();i++)
    {
        str1 = "TTC_START";
        needWriteList.append(str1);

        str1 ="TTC_NAME";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + stationParaList[i].name ;
        needWriteList.append(str3);

        str1 ="TTC_ID";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + stationParaList[i].id ;
        needWriteList.append(str3);

        str1 ="X";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + stationParaList[i].x+strSpace2+stationParaList[i].deltaX;
        needWriteList.append(str3);

        str1 ="Y";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + stationParaList[i].y+strSpace2+stationParaList[i].deltaY;
        needWriteList.append(str3);

        str1 ="Z";
        str2 = strTo_19_Width(str1);
        str3 = str2 + strEqual + stationParaList[i].y+strSpace2+stationParaList[i].deltaZ;
        needWriteList.append(str3);

        str1 = "TTC_STOP";
        needWriteList.append(str1);

        str1="\r\n";
        needWriteList.append(str1);

    }

    for(int j=0;j<needWriteList.size();j++)
    {
        needWriteList[j] = needWriteList[j]+"\r\n";
    }

    writeFile(needWriteList,"./address.txt");
}

QString    MainWindow::strTo_19_Width(QString strConvert)
{
    QString str1=strConvert;
    int len = str1.length();
    if(len<firstWidth)
    {
        for(int i=0;i<(firstWidth-len);i++)
        {
            str1=str1+" ";
        }

        return str1;
    }else
    {
        ui->lineEdit_log->setText("有第一列字符串长度大于19，返回空");
        str1 = "";
        return str1;
    }

}

void MainWindow::writeFile(QList<QString> textList, QString fileName)
{
    //writetext
    if(textList.size()>0)
    {
       QFile file(fileName);
       bool ok;
       //ok=file.open( QIODevice::ReadWrite | QIODevice::Append);
       if(file.exists())
       {
           if(file.isOpen())
           {
               file.close();
           }
           file.remove();
       }
       ok=file.open( QIODevice::ReadWrite );
       if(ok)
       {
           QTextStream out(&file);

           for(int i=0;i<textList.size();i++)
           {
               out << textList[i];
           }

           file.close();
           QMessageBox::information(this,"info",fileName+" create success!");
       }else
       {
            QMessageBox::information(this,"info","can not open file");
       }
    }else
    {
        QMessageBox::information(this,"info","no data need to write");
    }
}

void MainWindow::on_pushButton_qiXiang_new_clicked()
{
    initQiXiang();
    qiXiangObj->show();
}

void    MainWindow::initQiXiang()
{
    if(qiXiangObj)
    {

    }else
    {
        qiXiangObj = new DialogQiXiang(this);
        connect(qiXiangObj,SIGNAL(sendQiXiangData(QList<QString>)),
                this,SLOT(recvQiXiangData(QList<QString>)));
    }

}

void MainWindow::recvQiXiangData(QList<QString> dataList)
{
    qDebug()<<dataList;
    if(dataList.size() == 5 )
    {
        qiXiangDesc tempObj;
        tempObj.time = dataList.at(0);
        tempObj.stationNum = dataList.at(1);
        tempObj.temperature = dataList.at(2);
        tempObj.humidity = dataList.at(3);
        tempObj.pressure = dataList.at(4);

        qiXiangDataList.append(tempObj);
        updateQiXiangTableData();
    }else
    {
        QMessageBox::information(this,"info","can not open file");
    }

}

void MainWindow::setQiXiangTableHeader()
{
    QStringList list ;
    list.append("时间UTC");
    list.append("测站编号");
    list.append("温度");
    list.append("湿度");
    list.append("气压");



    modelQiXiang->setHorizontalHeaderLabels(list);
    //ui->tableView_qiXiang->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_qiXiang->setColumnWidth(0,170);
    ui->tableView_qiXiang->setColumnWidth(1,55);
    ui->tableView_qiXiang->setColumnWidth(2,45);
    ui->tableView_qiXiang->setColumnWidth(3,45);
    ui->tableView_qiXiang->setColumnWidth(4,60);
}

void   MainWindow::updateQiXiangTableData()//更新气象表格数据
{
    modelQiXiang->clear();
    setQiXiangTableHeader();
    qiXiangTableSelectedRow = -1;
    int size = qiXiangDataList.size();
    if(size > 0)
    {
        for(int i=0;i<size;i++)
        {
            int j=0;
            QString str = qiXiangDataList[i].time;
            QStandardItem*  tempItem0 = new QStandardItem(str);
            modelQiXiang->setItem(i,j,tempItem0);

            j=j+1;
            str = qiXiangDataList[i].stationNum;
            QStandardItem*  tempItem1 = new QStandardItem(str);
            modelQiXiang->setItem(i,j,tempItem1);

            j=j+1;
            str = qiXiangDataList[i].temperature;
            QStandardItem*  tempItem2 = new QStandardItem(str);
            modelQiXiang->setItem(i,j,tempItem2);

            j=j+1;
            str = qiXiangDataList[i].humidity;
            QStandardItem*  tempItem3 = new QStandardItem(str);
            modelQiXiang->setItem(i,j,tempItem3);

            j=j+1;
            str = qiXiangDataList[i].pressure;
            QStandardItem*  tempItem4 = new QStandardItem(str);
            modelQiXiang->setItem(i,j,tempItem4);

        }
    }
}

void   MainWindow::createQiXiangFile()
{
    QList<QString> needWriteList;
    needWriteList.clear();

    QString str1 ="POD_MET_VERS";
    QString str2 ="";
    QString str3 = "";
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

    str3 = "DATA_START";
    needWriteList.append(str3);

    for(int i=0;i<qiXiangDataList.size();i++)
    {
       QString strTemp ="  ";
       str1=qiXiangDataList[i].time;
       str2=str1+strTemp;

       str1=qiXiangDataList[i].stationNum;
       str2=str2+str1+strTemp;

       str1=qiXiangDataList[i].temperature;
       str2=str2+str1+strTemp;

       str1=qiXiangDataList[i].humidity;
       str2=str2+str1+strTemp;

       str1=qiXiangDataList[i].pressure;
       str2=str2+str1;

       str3 = str2;
       needWriteList.append(str3);
    }

    str3 = "DATA_STOP";
    needWriteList.append(str3);

    for(int j=0;j<needWriteList.size();j++)
    {
        needWriteList[j] = needWriteList[j]+"\r\n";
    }

    writeFile(needWriteList,"./weather.txt");
}

void MainWindow::on_tableView_qiXiang_clicked(const QModelIndex &index)
{
    qDebug()<<"test: "<<index.row()<<index.column();
    qiXiangTableSelectedRow = index.row();

}

void MainWindow::on_pushButton_qiXiang_del_clicked()
{
    if(qiXiangTableSelectedRow>=0 && qiXiangTableSelectedRow<qiXiangDataList.size())
    {
        qDebug()<<"befor del:"<<qiXiangDataList.size();
        qiXiangDataList.removeAt(qiXiangTableSelectedRow);
        updateQiXiangTableData();
        qDebug()<<"after del:"<<qiXiangDataList.size();
    }

}

void MainWindow::on_pushButton_orbit_save_clicked() //编辑轨道数据
{
    initOrbitDialog();
    orbitObj->show();

}

void  MainWindow::initOrbitDialog()//初始化轨道编辑数据框
{
    if(orbitObj)
    {

    }else
    {
        orbitObj = new DialogOrbit(this);
        connect(orbitObj,SIGNAL(sendOrbitData(QList<QString>)),
                this,SLOT(recvOrbitData(QList<QString>)));
    }


}

void MainWindow::on_pushButton_qiXiang_refresh_clicked()
{
    updateQiXiangTableData();
}

void MainWindow::on_pushButton_qiXiang_save_clicked()
{

    if(qiXiangTableSelectedRow>=0 && qiXiangTableSelectedRow<qiXiangDataList.size())
    {
        int i=0;
        for(i=0;i<qiXiangDataList.size();i++)
        {
            QModelIndex index = modelQiXiang->index(i,0);
            QVariant data = modelQiXiang->data(index);
            QString str = data.toString();
            qiXiangDataList[i].time =str;

            index = modelQiXiang->index(i,1);
            data = modelQiXiang->data(index);
            str = data.toString();
            qiXiangDataList[i].stationNum = str ;

            index = modelQiXiang->index(i,2);
            data = modelQiXiang->data(index);
            str = data.toString();
            qiXiangDataList[i].temperature = str ;

            index = modelQiXiang->index(i,3);
            data = modelQiXiang->data(index);
            str = data.toString();
            qiXiangDataList[i].humidity = str ;

            index = modelQiXiang->index(i,4);
            data = modelQiXiang->data(index);
            str = data.toString();
            qiXiangDataList[i].pressure = str ;
        }
        updateQiXiangTableData();
    }
}

void MainWindow::recvOrbitData(QList<QString> dataList)
{
    qDebug()<<dataList;
    orbitNeedWritList.clear();
    QString displayStr = "";
    for(int i=0; i<dataList.size();i++)
    {
        QString str = dataList[i]+"\r\n";
        orbitNeedWritList.append(str);
        displayStr = displayStr + str ;
    }
    ui->textEdit_orbit->setText(displayStr);
    qDebug()<<"orbit need write list:  "<<orbitNeedWritList;
}
void  MainWindow::createOrbitFile()
{
     writeFile(orbitNeedWritList,"./orbit.txt");

}

void MainWindow::on_pushButton_xiLi_save_clicked()
{
    initXingLiDialog();
    xingLiObj->show();

}

void MainWindow::initXingLiDialog()
{
    if(xingLiObj)
    {

    }else
    {
        xingLiObj = new DialogXingLi(this);
        connect(xingLiObj,SIGNAL(sendXingLiData(QList<QString>)),
                this,SLOT(recvXingLiData(QList<QString>)));
    }

}

void MainWindow::recvXingLiData(QList<QString> dataList)
{
    qDebug()<<dataList;
    xingLiNeedWritList.clear();
    QString displayStr = "";
    for(int i=0; i<dataList.size();i++)
    {
        QString str = dataList[i]+"\r\n";
        xingLiNeedWritList.append(str);
        displayStr = displayStr + str;
    }
    ui->textEdit_xingLi->setText(displayStr);
    qDebug()<<"EPH need write list:  "<<xingLiNeedWritList;


}

void   MainWindow::createXingLiFile() //生产星历接口描述文件
{
     QString str1,fileName;
     QString key = "OBJECT_CATNUM";
     bool find = false;
     for(int i=0;i<xingLiNeedWritList.size();i++)
     {
         str1 = xingLiNeedWritList[i];
         int widthMust = 6;
         if(str1.contains(key))
         {
             fileName = str1.replace("OBJECT_CATNUM","");
             fileName = fileName.replace("=","");
             fileName = fileName.trimmed();

             if(fileName.length()< widthMust)
             {
                 for(int i=0;i<=(widthMust-fileName.length());i++)
                 {
                     fileName = "0"+fileName;
                 }
             }
             fileName = "./EPH_" + fileName + ".txt" ;
             qDebug()<<fileName;
             writeFile(xingLiNeedWritList,fileName);
             find = true ;
             break ;
         }

     }

     if(!find)
     {
         QMessageBox::information(this,"info","can not find: OBJECT_CATNUM ID");
     }

}


void MainWindow::on_pushButton_TTC_EditData_clicked()
{
    initTTCDataDialog();
    ttcDataObj->show();
}


void MainWindow::initTTCDataDialog() //初始化测量数据对话框
{
    if(ttcDataObj)
    {

    }else
    {
        ttcDataObj = new DialogTTCData(this);
        connect(ttcDataObj,SIGNAL(sendTTCData(QList<QString>)),
                this,SLOT(recvTTCData(QList<QString>)));
    }

}

void MainWindow::recvTTCData(QList<QString> dataList)
{
    ttcDataNeedWritList.clear();
    qDebug()<<dataList;
    QString displayStr = "" ;
    for(int i=0; i<dataList.size();i++)
    {
        QString str = dataList[i]+"\r\n";
        ttcDataNeedWritList.append(str);
        displayStr = displayStr + str ;
    }
    ui->textEdit_ttcData->setText(displayStr);
    qDebug()<<"EPH need write list:  "<<ttcDataNeedWritList;

}

void MainWindow::createTTCFile() //生产TTC测量数据接口文件
{
    writeFile(ttcDataNeedWritList,"./ttc.txt");

}
