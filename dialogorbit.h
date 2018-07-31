#ifndef DIALOGORBIT_H
#define DIALOGORBIT_H

#include <QDialog>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QDateTime>

#include "datastruct.h"


namespace Ui {
class DialogOrbit;
}

class DialogOrbit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOrbit(QWidget *parent = 0);
    ~DialogOrbit();

     QStandardItemModel *modelPLANET;//PLANET表的model


     QList<PlanetDesc>   planetList;
     int                 planetTableSelectedRow; //PLANET表格选中的行，用来删除数据用的

     void                updatePlanetTableData();//更新PLANET表格数据
     void                setPLANETTableHeader(); //设置PLANET表格的表格头部文字
     QString             strTo_19_Width(QString strConvert); //将一个字符串变成长度为19的字符串，右补空格
     QString             strTo_19_Width_left(QString strConvert); //将一个字符串变成长度为19的字符串，左补空格

signals:
   void  sendOrbitData(QList<QString>);

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_exit_clicked();

    void on_checkBox_FORCE_clicked();

    void on_tableView_PLANET_clicked(const QModelIndex &index);

    void on_pB_Add_clicked();

    void on_pB_del_clicked();

    void on_pB_fixSave_clicked();

    void on_pB_refresh_clicked();

private:
    Ui::DialogOrbit *ui;
};

#endif // DIALOGORBIT_H
