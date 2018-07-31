#include "dialogqixiang.h"
#include "ui_dialogqixiang.h"

DialogQiXiang::DialogQiXiang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogQiXiang)
{
    ui->setupUi(this);
    setWindowTitle("气象数据编辑");
}

DialogQiXiang::~DialogQiXiang()
{
    delete ui;
}

void DialogQiXiang::on_pushButton_exit_clicked()
{
    this->close();
}

void DialogQiXiang::on_pushButton_ok_clicked()
{
    QList<QString> needList;
    needList.clear();
    needList.append(ui->lineEdit_time->text());
    needList.append(ui->lineEdit_num->text());
    needList.append(ui->lineEdit_wenDu->text());
    needList.append(ui->lineEdit_shiDu->text());
    needList.append(ui->lineEdit_qiYa->text());
    emit  sendQiXiangData(needList);
    this->close();
}
