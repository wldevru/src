#ifndef WL3DMODEL_H
#define WL3DMODEL_H

#include <QObject>
#include <QColor>
#include <QFile>
#include <QOpenGLShaderProgram>

struct STriangle
{
QVector3D Points[6];
};

struct SModelGLData
{
QVector   <STriangle> Triangles;
QColor     color;
QMatrix4x4 M;
};

class WL3DModel :public QObject
{
	Q_OBJECT

public:
	WL3DModel();
	~WL3DModel();

virtual void buildGLData(QList<SModelGLData> &data) {data.clear();}

void setNameModel(QString _name) {name=_name;}
QString getNameModel() {return name;}

private:

	QString name;
	
};

bool loadSTL(QString fileName,QVector<STriangle> &Triangles);

#endif // WL3DMODEL_H
