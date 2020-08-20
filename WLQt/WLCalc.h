#ifndef WLCalc_H
#define WLCalc_H

#include <QQuaternion>
#include <QVector3D>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QtMath>

#include "wl3dpoint.h"

QQuaternion calcQuanternion(QMatrix4x4 M);
QQuaternion MatrixToQuaternion(QMatrix4x4 M);
QQuaternion calcQuanternion(QMatrix3x3 M);

QMatrix4x4 getRotMatrix(double Xa,double Ya,double Za=0);

QMatrix4x4 calcPlane(WL3DPoint P0,WL3DPoint P1,WL3DPoint P2,bool *ok=NULL);

QString toStringBits(int data,int size);
#endif // WLCalc
