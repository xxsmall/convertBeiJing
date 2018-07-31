#ifndef DIALOGTTCDATA_H
#define DIALOGTTCDATA_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDateTime>
#include <QDebug>

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

    void                setStationTableHeader(); //设置station表格的表格头部文字
    void                updateStationTableData();//更新station表格数据
    QString             strTo_19_Width(QString strConvert); //将一个字符串变成长度为19的字符串，右补空格

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

private:
    Ui::DialogTTCData *ui;
};

#endif // DIALOGTTCDATA_H
