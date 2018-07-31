#include "dialogorbit.h"
#include "ui_dialogorbit.h"

DialogOrbit::DialogOrbit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOrbit)
{
    ui->setupUi(this);
    setWindowTitle("轨道根数编辑");
    modelPLANET =new QStandardItemModel();
    ui->tableView_PLANET->setModel(modelPLANET);
    setPLANETTableHeader();

    planetList.clear();
    planetTableSelectedRow=-1;

}

DialogOrbit::~DialogOrbit()
{
    delete ui;
}

void DialogOrbit::on_pushButton_save_clicked()
{
    QList<QString> needWriteList;
    needWriteList.clear();

    QString str1 ="POD_OBT_VERS";
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

    str3 = "SC_OBT";
    needWriteList.append(str3);

    str1 = "  SC_ID";
    str2 = strTo_19_Width(str1);
    str3 = str2 + str3Space + ui->SC_ID->text();
    needWriteList.append(str3);

    if(ui->checkBox_REF_FRAME->isChecked())
    {
        str1 = "  REF_FRAME";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->REF_FRAME->text();
        needWriteList.append(str3);
    }

    if(ui->checkBox_FRM_ORIGIN->isChecked())
    {
        str1 = "  FRM_ORIGIN";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->FRM_ORIGIN->text();
        needWriteList.append(str3);
    }

    if(ui->checkBox_TIME_SYSTEM->isChecked())
    {
        str1 = "  TIME_SYSTEM";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->TIME_SYSTEM->text();
        needWriteList.append(str3);
    }

    str1 = "  EPOCH";
    str2 = strTo_19_Width(str1);
    str3 = str2 + str3Space + ui->EPOCH_1->text();
    str3 = str3 + str3Space + ui->EPOCH_2->text();
    needWriteList.append(str3);


    str1 = "  OBT_PAR_PV";
    str2 = strTo_19_Width(str1);
    str3 = str2 + str3Space + strTo_19_Width_left(ui->OBT_PAR_PV_1->text());
    str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_PV_2->text());
    str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_PV_3->text());
    str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_PV_4->text());
    str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_PV_5->text());
    str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_PV_6->text());
    needWriteList.append(str3);

    if(ui->checkBox_OBT_ERR_PV->isChecked())
    {
        str1 = "  OBT_ERR_PV";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + strTo_19_Width_left(ui->OBT_ERR_PV_1->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_PV_2->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_PV_3->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_PV_4->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_PV_5->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_PV_6->text());
        needWriteList.append(str3);
    }

    if(ui->checkBox_OBT_PAR_KEP->isChecked())
    {
        str1 = "  OBT_PAR_KEP";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + strTo_19_Width_left(ui->OBT_PAR_KEP_1->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_KEP_2->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_KEP_3->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_KEP_4->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_KEP_5->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_PAR_KEP_6->text());
        needWriteList.append(str3);
    }

    if(ui->checkBox_OBT_ERR_KEP->isChecked())
    {
        str1 = "  OBT_ERR_KEP";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + strTo_19_Width_left(ui->OBT_ERR_KEP_1->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_KEP_2->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_KEP_3->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_KEP_4->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_KEP_5->text());
        str3 = str3 + strTo_19_Width_left(ui->OBT_ERR_KEP_6->text());
        needWriteList.append(str3);
    }

    if(ui->checkBox_FORCE->isChecked())
    {
        str3 = "FORCE";
        needWriteList.append(str3);

        str1 = "  INTG_CENTER";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->INTG_CENTER->text();
        needWriteList.append(str3);

        str1 = "  GRAVITY";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->GRAVITY_1->text();
        str3 = str3 + str3Space + ui->GRAVITY_2->text();
        str3 = str3 + str3Space + ui->GRAVITY_3->text();
        str3 = str3 + str3Space + ui->GRAVITY_4->text();
        needWriteList.append(str3);


        //PLANET 部分写入
        int size = planetList.size() ;
        for(int i=0;i<size;i++)
        {
            str1 = "  PLANET";
            str2 = strTo_19_Width(str1);
            str3 = str2 + str3Space + planetList[i].ID;
            str3 = str3 + str3Space + planetList[i].calFlag;
            str3 = str3 + str3Space + planetList[i].NewtonFlag;
            needWriteList.append(str3);

        }
        //

        str1 = "  DRAG";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->DRAG_1->text();
        str3 = str3 + str3Space + ui->DRAG_2->text();
        str3 = str3 + str3Space + ui->DRAG_3->text();
        needWriteList.append(str3);

        str1 = "  SRP";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->SRP_1->text();
        str3 = str3 + str3Space + ui->SRP_2->text();
        str3 = str3 + str3Space + ui->SRP_3->text();
        str3 = str3 + str3Space + ui->SRP_4->text();
        needWriteList.append(str3);

        str1 = "  GRT";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->GRT->text();
        needWriteList.append(str3);

        str1 = "  THRUST";
        str2 = strTo_19_Width(str1);
        str3 = str2 + str3Space + ui->THRUST->text();
        needWriteList.append(str3);
    }
    str3 = "META_STOP";
    needWriteList.append(str3);


    emit sendOrbitData(needWriteList);
    this->close();
}

void DialogOrbit::on_pushButton_exit_clicked()
{
    this->close();
}

void DialogOrbit::on_checkBox_FORCE_clicked()
{
    bool isCheck;
    isCheck = ui->checkBox_FORCE->isChecked();
    ui->checkBox_DRAG->setChecked(isCheck);
    ui->checkBox_INTG_CENTER->setChecked(isCheck);
    ui->checkBox_GRAVITY->setChecked(isCheck);
    ui->checkBox_PLANET->setChecked(isCheck);
    ui->checkBox_SRP->setChecked(isCheck);
    ui->checkBox_GRT->setChecked(isCheck);
    ui->checkBox_THRUST->setChecked(isCheck);
}

void   DialogOrbit::setPLANETTableHeader()
{
    QStringList list ;
    list.append("天体ID");
    list.append("偏导数计算标志");
    list.append("后牛顿标志");


    modelPLANET->setHorizontalHeaderLabels(list);
   // ui->tableView_PLANET->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_PLANET->setColumnWidth(0,100);
    ui->tableView_PLANET->setColumnWidth(1,115);
    ui->tableView_PLANET->setColumnWidth(2,100);

}

void DialogOrbit::on_tableView_PLANET_clicked(const QModelIndex &index)
{
     planetTableSelectedRow=index.row();
}

void DialogOrbit::updatePlanetTableData()//更新PLANET表格数据
{
    modelPLANET->clear();
    setPLANETTableHeader();
    planetTableSelectedRow=-1;
    int size = planetList.size();
    if(size > 0)
    {
        for(int i=0;i<size;i++)
        {
            int j=0;
            QString str = planetList[i].ID;
            QStandardItem*  tempItem0 = new QStandardItem(str);
            tempItem0->setBackground(QColor(192,192,192));
            modelPLANET->setItem(i,j,tempItem0);

            j=j+1;
            str = planetList[i].calFlag;
            QStandardItem*  tempItem1 = new QStandardItem(str);
            tempItem1->setBackground(QColor(192,192,192));
            modelPLANET->setItem(i,j,tempItem1);

            j=j+1;
            str = planetList[i].NewtonFlag;
            QStandardItem*  tempItem2 = new QStandardItem(str);
            tempItem2->setBackground(QColor(192,192,192));
            modelPLANET->setItem(i,j,tempItem2);

        }
    }

}

void DialogOrbit::on_pB_Add_clicked()
{
   // planetList
    PlanetDesc tempObj;
    tempObj.ID = "10";
    tempObj.calFlag = "1";
    tempObj.NewtonFlag = "1";
    planetList.append(tempObj);
    updatePlanetTableData();
}

void DialogOrbit::on_pB_del_clicked()
{
    if(planetTableSelectedRow>=0 && planetTableSelectedRow<planetList.size())
    {
        planetList.removeAt(planetTableSelectedRow);
        updatePlanetTableData();
    }
}

void DialogOrbit::on_pB_fixSave_clicked()
{
    if(planetTableSelectedRow>=0 && planetTableSelectedRow<planetList.size())
    {
        int i=0;
        for(i=0;i<planetList.size();i++)
        {
            QModelIndex index = modelPLANET->index(i,0);
            QVariant data = modelPLANET->data(index);
            QString str = data.toString();
            planetList[i].ID =str;

            index = modelPLANET->index(i,1);
            data = modelPLANET->data(index);
            str = data.toString();
            planetList[i].calFlag = str ;

            index = modelPLANET->index(i,2);
            data = modelPLANET->data(index);
            str = data.toString();
            planetList[i].NewtonFlag = str ;
        }
        updatePlanetTableData();
    }
}

void DialogOrbit::on_pB_refresh_clicked()
{
    updatePlanetTableData();

}

QString  DialogOrbit::strTo_19_Width(QString strConvert)
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
       // ui->lineEdit_log->setText("有第一列字符串长度大于19，返回空");
        str1 = "";
        return str1;
    }

}

QString  DialogOrbit::strTo_19_Width_left(QString strConvert)
{
    QString str1=strConvert;
    int len = str1.length();
    int firstWidth =19;
    if(len<firstWidth)
    {
        for(int i=0;i<(firstWidth-len);i++)
        {
            str1=" "+str1;
        }

        return str1;
    }else
    {

        str1 = " "+strConvert;
        return str1;
    }
}
