#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xyzclass.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>


#include "dialogqixiang.h"
#include "dialogorbit.h"
#include "dialogxingli.h"
#include "datastruct.h"
#include "dialogttcdata.h"



class stationDesc
{
public:
    QString name;
    QString x;
    QString deltaX;
    QString y;
    QString deltaY;
    QString z;
    QString deltaZ;
    QString id;

};

class qiXiangDesc
{
public:
    QString time;
    QString stationNum;
    QString temperature;
    QString humidity;
    QString pressure;

};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<stationDesc> stationParaList;  //测站描述表
    QList<qiXiangDesc> qiXiangDataList;  //气象数据队列
    int                stationSelected;  //测站编辑时，选中的测站
    QString            strEqual;    //特定字符串
    QString            strSpace2;   //两个空格
    int                firstWidth;  //第一列的宽度

    DialogQiXiang*     qiXiangObj;  //气象新增数据对话框
    QStandardItemModel *modelQiXiang;//气象表的model
    int                 qiXiangTableSelectedRow; //气象表格选中的行，用来删除数据用的

    DialogOrbit*       orbitObj;  //轨道根数编辑对话框
    QList<QString>     orbitNeedWritList;//需要写入到轨道接口文件的数据

    DialogXingLi*      xingLiObj; //星历数据编辑对话框
    QList<QString>     xingLiNeedWritList;//需要写入到星历接口文件的数据

    DialogTTCData*     ttcDataObj; //测量数据对话框
    QList<QString>     ttcDataNeedWritList; //需要写入到测量数据接口文件的数据

    void               createStationFile(); //生产测站描述文件
    QString            strTo_19_Width(QString strConvert); //将一个字符串变成长度为19的字符串，右补空格
    void               writeFile(QList<QString> textList,QString fileName);//写入文件
    void               initQiXiang(); //初始化气象表格
    void               initStation(); //初始化测站树
    void               setQiXiangTableHeader(); //设置气象表格的表格头部文字
    void               updateQiXiangTableData();//更新气象表格数据
    void               createQiXiangFile(); //产生气息数据文件

    void               initOrbitDialog();
    void               createOrbitFile(); //生产轨道接口描述文件

    void               initXingLiDialog(); //初始化星历对话框
    void               createXingLiFile(); //生产星历接口描述文件

    void               initTTCDataDialog(); //初始化测量数据对话框
    void               createTTCFile(); //生产TTC测量数据接口文件

private slots:
    void on_pushButton_clicked();
    void gpsPoint2DescartesPoint(const double latitude, const double longitude, const double altitude, double &x, double &y, double &z);

    void on_listView_station_activated(const QModelIndex &index);


    void on_listView_station_clicked(const QModelIndex &index);

    void on_pushButton_SFix_clicked();

    void on_pushButton_SSave_clicked();

    void on_pushButton_qiXiang_new_clicked();
    void on_tableView_qiXiang_clicked(const QModelIndex &index);

    void on_pushButton_qiXiang_del_clicked();

    void on_pushButton_orbit_save_clicked();

    void on_pushButton_qiXiang_refresh_clicked();

    void on_pushButton_qiXiang_save_clicked();

    void on_pushButton_xiLi_save_clicked();

    void on_pushButton_TTC_EditData_clicked();

public slots:

    void recvQiXiangData(QList<QString> dataList);
    void recvOrbitData(QList<QString> dataList);
    void recvXingLiData(QList<QString> dataList);
    void recvTTCData(QList<QString> dataList);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
