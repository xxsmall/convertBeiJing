#ifndef DIALOGTTCDATA_H
#define DIALOGTTCDATA_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDateTime>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#include "datastruct.h"

namespace Ui {
class DialogTTCData;
}

class DialogTTCData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTTCData(QWidget *parent = 0);
    ~DialogTTCData();

    QList<ttcStationDesc> ttcStationList; //测量数据文件接口中描述测站的队列
    QStandardItemModel* modelStation;//station表的model
    int  stationSelectedRow; //station表选中的行

    QList<ttcDataFileDesc> ttcFileList; //测量数据文件队列
    QStandardItemModel* modelFile;//station表的model
    int  fileSelectedRow; //station表选中的行


    void                setStationTableHeader(); //设置station表格的表格头部文字
    void                updateStationTableData();//更新station表格数据
    QString             strTo_19_Width(QString strConvert); //将一个字符串变成长度为19的字符串，右补空格

    void                setFileTableHeader(); //设置file表格的表格头部文字
    void                updateFileTableData();//更新file表格内容

    QList<QString>      anlyseAllTTCFile(); //分析所有数据文件，产生一个转换完文件行集合

    QString             removeMoreSpace(QString str); //将每行连续的空格变为单个空格

    QList<QString>      readFile(QString fileName);//按行读取文件，形成一个QList<QString>

    QList<QString>      getEffectLineList(QString selectFile); //通过readFile先读取所有行，然后去掉不需要的行

    QList<QString>      creatData(QList<QString> dataList,QString stationNum,QString sateNum);//单个数据文件产生的数据集合

    double              jde(int Y, int M, int D, int hour, int min, float sec);


signals:
   void  sendTTCData(QList<QString>);


private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();


    void on_pushButton_addStation_clicked();

    void on_pushButton_refreshStation_clicked();

    void on_tableView_station_clicked(const QModelIndex &index);

    void on_pushButton_delStation_clicked();

    void on_pushButton_saveStation_clicked();

    void on_checkBox_TTC_TRANS_FRE_clicked();

    void on_pushButton_selectFile_clicked();

    void on_pushButton_addFile_clicked();

    void on_tableView_fileList_clicked(const QModelIndex &index);

    void on_pushButton_delFile_clicked();

    void on_pushButton_analyseFile_clicked();

private:
    Ui::DialogTTCData *ui;
};

#endif // DIALOGTTCDATA_H
