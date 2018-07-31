#ifndef XYZCLASS_H
#define XYZCLASS_H
#include <Qmath.h>
//WGS84地理坐标系参变量
class CRDGEODETIC
{
public:
    double latitude;
    double longitude;
    double altitude;
};

//空间笛卡尔坐标系坐标点
class CRDCARTESIAN
{
public:
    double x;
    double y;
    double z;
};


class XYZClass
{
public:
    XYZClass();


public:
    CRDCARTESIAN BLH_to_XYZ (CRDGEODETIC pos_BLH);//大地--->球心
    CRDGEODETIC  XYZ_to_BHL (CRDCARTESIAN pos_XYZ);//球心--->大地
    CRDCARTESIAN XYZ_to_xyz (CRDCARTESIAN pos_XYZ , CRDGEODETIC Center);//球心--->站心
    CRDCARTESIAN xyz_to_XYZ (CRDCARTESIAN pos_xyz , CRDGEODETIC Center);//站心--->球心
};

#endif // XYZCLASS_H
