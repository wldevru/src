#include <WLCalc.h>

QQuaternion calcQuanternion(QMatrix3x3 M) 
{
const double  w = sqrt(1+M(0,0)+M(1,1)+M(2,2))/2;
const double  w4 = w*4;

return QQuaternion(w
                  ,(M(2,1)-M(1,2))/w4
                  ,(M(0,2)-M(2,0))/w4
                  ,(M(1,0)-M(0,1))/w4);
}

QQuaternion calcQuanternion(QMatrix4x4 M) 
{
const double  w = sqrt(1+M(0,0)+M(1,1)+M(2,2))/2;
const double w4 = w*4;

return QQuaternion(w
                  ,(M(2,1)-M(1,2))/w4
                  ,(M(0,2)-M(2,0))/w4
                  ,(M(1,0)-M(0,1))/w4);
}

QQuaternion MatrixToQuaternion(QMatrix4x4 m)
{
  QQuaternion quant;
  double tr, s, q[4];
  int    i, j, k;

  int nxt[3] = {1, 2, 0};

  tr = m(0,0) + m(1,1) + m(2,2);

  if (tr > 0.0)
  {
    s = sqrt (tr + 1.0);
	quant.setScalar(s/2.0);
    s = 0.5 / s;
	quant.setX((m(1,2)-m(2,1)) * s);
    quant.setY((m(2,0)-m(0,2)) * s);
    quant.setZ((m(0,1)-m(1,0)) * s);
  }
  else
  {
    i = 0;
    if (m(1,1) > m(0,0)) i = 1;
    if (m(2,2) > m(i,i)) i = 2;
    j = nxt[i];
    k = nxt[j];

    s = sqrt ((m(i,i) - (m(j,j) + m(k,k))) + 1.0);

    q[i] = s * 0.5;

    if (s != 0.0) s = 0.5 / s;

    q[3] = (m(j,k) - m(k,j)) * s;
    q[j] = (m(i,j) + m(j,i)) * s;
    q[k] = (m(i,k) + m(k,i)) * s;

    quant.setX(q[0]);
	quant.setY(q[1]);
    quant.setZ(q[2]);
	quant.setScalar(q[3]);
  }
return quant;
}





QMatrix4x4 getRotMatrix(double Xa,double Ya,double Za)
{
QMatrix4x4 M,Mb;

if(Xa!=0.0) {Mb.setToIdentity(); Mb.rotate(Xa,1,0,0);   M=Mb*M;}
if(Ya!=0.0) {Mb.setToIdentity(); Mb.rotate(Ya,0,1,0);   M=Mb*M;}
if(Za!=0.0) {Mb.setToIdentity(); Mb.rotate(Za,0,0,1);   M=Mb*M;}

return M;
}

QString toStringBits(int data,int size)
{
QString ret;

for(int i=0,b=1;i<size;i++,b<<=1)
         ret.prepend(data&b ? "1":"0");

return ret;
}

QMatrix4x4 calcPlane(WL3DPoint P0,WL3DPoint P1,WL3DPoint P2,bool *ok)
{
QMatrix4x4 ret;
WL3DPoint X,Y,Z;

if(P0!=P1&&P0!=P2&&P1!=P2) 
{
if(ok!=NULL) *ok=true;

X=P1-P0;
Y=P2-P0;

qDebug()<<"X "<<X.x<<X.y<<X.z;
qDebug()<<"Y "<<Y.x<<Y.y<<Y.z;

Z=X*Y;
Y=Z*X;

qDebug()<<"Yn"<<Y.x<<Y.y<<Y.z;
qDebug()<<"Z "<<Z.x<<Z.y<<Z.z;

X=X.normalize();
Y=Y.normalize();
Z=Z.normalize();

ret.setColumn(0,X.toV4D());
ret.setColumn(1,Y.toV4D());
ret.setColumn(2,Z.toV4D());
ret.setColumn(3,P0.toV4D());
}
else
  if(ok!=NULL) *ok=false;

return ret;
}
