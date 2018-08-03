#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QString>
//其他天体引力，依次为天体ID，偏导数计算标志，后牛顿标志
class PlanetDesc
{
public:
    QString ID;
    QString calFlag;
    QString NewtonFlag;
};


class XingLiDesc    //星历编辑表格用的类
{
public:
    QString time;
    QString MJD;
    QString JS;
    QString pos_x;
    QString pos_y;
    QString pos_z;
    QString speed_x;
    QString speed_y;
    QString speed_z;
    QString accelerat_x;
    QString accelerat_y;
    QString accelerat_z;

};


class ttcStationDesc   //测量数据中测站编辑表格用的类
{
  public:
    QString TTC_FAC_ID;
    QString REC_REF_FRE;
    QString TTC_TRANS_FRE;
    QString TURN_RATIO;
    QString TRS_START_TIME;
    QString TRS_END_TIME;
};

class ttcDataFileDesc      //测量数据文件编辑表格用的类
{
public:
    QString fileName;
    QString stationID;
    QString satNum;

};

typedef struct
{
    int years;         /*!< Years. All values are valid */
    int months;        /*!< Months. Valid values : 1 (January) - 12 (December ) */
    int days;         /*!< Days. Valid values 1 - 28,29,30,31 Depends on month .*/
    int hours;         /*!< Hours. Valid values 0 - 23. */
    int minutes;      /*!< Minutes. Valid values 0 - 59. */
    double seconds;    /*!< Seconds. Valid values 0 - 59.99999.... */
}ln_date;
#endif // DATASTRUCT_H
