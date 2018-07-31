#ifndef DIALOGQIXIANG_H
#define DIALOGQIXIANG_H

#include <QDialog>

namespace Ui {
class DialogQiXiang;
}

class DialogQiXiang : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQiXiang(QWidget *parent = 0);
    ~DialogQiXiang();
signals:
   void  sendQiXiangData(QList<QString>);
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_ok_clicked();
public slots:


private:
    Ui::DialogQiXiang *ui;
};

#endif // DIALOGQIXIANG_H
