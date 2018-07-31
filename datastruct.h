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


class XingLiDesc
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


class ttcStationDesc
{
  public:
    QString TTC_FAC_ID;
    QString REC_REF_FRE;
    QString TTC_TRANS_FRE;
    QString TURN_RATIO;
    QString TRS_START_TIME;
    QString TRS_END_TIME;
};
#endif // DATASTRUCT_H
