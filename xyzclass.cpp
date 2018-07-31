#include "xyzclass.h"

XYZClass::XYZClass()
{

}

CRDCARTESIAN XYZClass::BLH_to_XYZ (CRDGEODETIC pos_BLH)
{
    double a=6378136.49;//a为椭球的长半轴:a=6378.137km
    double b=6356755.00;//b为椭球的短半轴:a=6356.7523141km
    double H=pos_BLH.altitude;
    //double H=pos_BLH.altitude+a;

    double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
    // double e=sqrt(0.006693421622966); //克拉索夫斯基椭球
    // double e=sqrt(0.006694384999588); //1975年国际椭球
    // double e=sqrt(0.0066943799013); //WGS-84椭球

    CRDCARTESIAN pos_XYZ;
    double m=M_PI/180;//经度维度需要转换成弧度.
    double B=pos_BLH.latitude*m;
    double L=pos_BLH.longitude*m;
    double W=sqrt(1-pow(e ,2)*pow(sin(B) ,2));
    double N=a/W; //N为椭球的卯酉圈曲率半径

    pos_XYZ.x=(N+H)*cos(B)*cos(L);
    pos_XYZ.y=(N+H)*cos(B)*sin(L);
    pos_XYZ.z=(N*(1-pow(e ,2))+H)*sin(B);

    return pos_XYZ;

}

 CRDGEODETIC  XYZClass::XYZ_to_BHL (CRDCARTESIAN pos_XYZ)//球心--->大地
 {

     double v0=pos_XYZ.z/sqrt(pow(pos_XYZ.x ,2)+pow(pos_XYZ.y ,2));

     double a=6378136.49;//a为椭球的长半轴:a=6378.137km
     double b=6356755.00;//b为椭球的短半轴:a=6356.7523141km
     double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
     // double e=sqrt(0.006693421622966); //克拉索夫斯基椭球
     // double e=sqrt(0.006694384999588); //1975年国际椭球
     // double e=sqrt(0.0066943799013); //WGS-84椭球

     // double W=sqrt(1-pow(e ,2)*pow(sin(B) ,2));
     double N=0 ; //N为椭球的卯酉圈曲率半径
     double B1=atan(v0) ,B2=0;
     double H=0;

     while(qAbs(B2-B1)>1E-5)
     {
         N = a/sqrt(1-pow(e ,2)*pow(sin(B1) ,2));
         H = pos_XYZ.z/sin(B1)-N*(1-pow(e ,2));
         B2 = atan(pos_XYZ.z*(N+H)/sqrt((pow(pos_XYZ.x ,2)+pow(pos_XYZ.y ,2))*(N*(1-pow(e,2))+H)));
         B1=B2;
     }

     double m=M_PI/180;
     CRDGEODETIC pos_BLH;
     pos_BLH.latitude=B1/m;
     pos_BLH.longitude=atan(pos_XYZ.y/pos_XYZ.x)/m;
     pos_BLH.altitude=H-a;

     return pos_BLH;
 }

CRDCARTESIAN XYZClass::XYZ_to_xyz (CRDCARTESIAN pos_XYZ , CRDGEODETIC Center)//球心--->站心
{
    CRDCARTESIAN pos_xyz ,tmp_XYZ;
    CRDCARTESIAN Center_XYZ = BLH_to_XYZ (Center);
    double a=6378137;//a为椭球的长半轴:a=6378.137km
    tmp_XYZ.x = pos_XYZ.x-Center_XYZ.x;
    tmp_XYZ.y = pos_XYZ.y-Center_XYZ.y;
    tmp_XYZ.z = pos_XYZ.z-Center_XYZ.z;
    double m=M_PI/180;
    pos_xyz.x = -sin(Center.latitude*m)*cos(Center.longitude*m)*tmp_XYZ.x-sin(Center.latitude*m)*sin(Center.longitude*m)*tmp_XYZ.y
    + cos(Center.latitude*m)*tmp_XYZ.z;
    pos_xyz.y = -sin(Center.longitude*m)*tmp_XYZ.x+cos(Center.longitude*m)*tmp_XYZ.y;
    pos_xyz.z =cos(Center.latitude*m)*cos(Center.longitude*m)*tmp_XYZ.x+cos(Center.latitude*m)*sin(Center.longitude*m)*tmp_XYZ.y
    + sin(Center.latitude*m)*tmp_XYZ.z - a;

    return pos_xyz;
}


CRDCARTESIAN XYZClass::xyz_to_XYZ (CRDCARTESIAN pos_xyz , CRDGEODETIC Center)//站心--->球心
{
    double a=6378137;//a为椭球的长半轴:a=6378.137km
    double b=6356752.3141;//b为椭球的短半轴:a=6356.7523141km

    double H0=Center.altitude+a;

    double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
    // double e=sqrt(0.006693421622966); //克拉索夫斯基椭球
    // double e=sqrt(0.006694384999588); //1975年国际椭球
    // double e=sqrt(0.0066943799013); //WGS-84椭球

    double m=M_PI/180;//经度维度需要转换成弧度.
    double B0=Center.latitude*m;
    double L0=Center.longitude*m;
    double W=sqrt(1-pow(e ,2)*pow(sin(B0) ,2));
    double N0=a/W; //N为椭球的卯酉圈曲率半径

    CRDCARTESIAN pos_XYZ;
    pos_XYZ.x = (N0+H0)*cos(B0)*cos(L0)
    -sin(B0)*cos(L0)*pos_xyz.x - sin(L0)*pos_xyz.y + cos(B0)*cos(L0)*pos_xyz.z;
    pos_XYZ.y = (N0+H0)*cos(B0)*sin(L0)
    -sin(B0)*sin(L0)*pos_xyz.x - cos(L0)*pos_xyz.y + cos(B0)*sin(L0)*pos_xyz.z;
    pos_XYZ.z = (N0*(1-pow(e ,2))+H0)*sin(B0)
    -cos(B0)*pos_xyz.x + sin(B0)*pos_xyz.z;

    return pos_XYZ;

}
