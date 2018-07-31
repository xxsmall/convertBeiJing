#ifndef DIALOGXINGLI_H
#define DIALOGXINGLI_H

#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDateTime>
#include <QDialog>

#include "datastruct.h"

namespace Ui {
class DialogXingLi;
}

class DialogXingLi : public QDialog
{
    Q_OBJECT

public:
    explicit DialogXingLi(QWidget *parent = 0);
    ~DialogXingLi();

    QStandardItemModel *modelXingLi;//星历表的model
    QList<XingLiDesc>   xingLiDataList;//星历表格的数据列表
    int                 xingLiTableSelectedRow;

    void                setXingLiTableHeader(); //设置PLANET表格的表格头部文字
    void                updateXingLiTableData();//更新PLANET表格数据

    QString             strTo_19_Width(QString strConvert); //将一个字符串变成长度为19的字符串，右补空格
    QString             strTo_n_Width_left(QString strConvert,int n);
    QString             strTo_n_Width_right(QString strConvert,int n);
signals:
   void  sendXingLiData(QList<QString>);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_addData_clicked();

    void on_tableView_XingLi_clicked(const QModelIndex &index);

    void on_pushButton_delData_clicked();

    void on_pushButton_refreshData_clicked();

    void on_pushButton_saveData_clicked();

private:
    Ui::DialogXingLi *ui;
};

#endif // DIALOGXINGLI_H
