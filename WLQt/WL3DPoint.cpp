#include "wl3dpoint.h"

double calcAngleRad(WL3DPoint A,WL3DPoint B)
{
double val=calcACos(A,B);

if(val<-1) val=-1;
 else
    if(val>1) val=1;

return acos(val);
}

double calcAngleGrd(WL3DPoint A,WL3DPoint B)
{
return calcAngleRad(A,B)*180.0/M_PI;
}

double calcACos(WL3DPoint A,WL3DPoint B)
{
return ((A.x*B.x+A.y*B.y+A.z*B.z)/(A.r()*B.r()));
}
