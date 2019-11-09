#ifndef WLELEMENT_H
#define WLELEMENT_H

#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "..\wlflags.h"

#define idAxis 0
#define idCut  10

#define idLine  100
#define idCirc  101
#define idBuff  102
#define idWhell 103

const QString namesTypeElement("typeEEmpty,typeEInput,typeEOutput,typeEOutPWM");

enum typeElement{typeEEmpty=0
	            ,typeEInput
                ,typeEOutput
                ,typeEOutPWM
                ,typeEAxis
                ,typeEDCan
                ,typeEEncoder
                ,typeEFreq
                ,typeEWhell};	


class WLElement : public QObject
{
 Q_OBJECT

public:

    WLElement(QObject *parent=0);
   ~WLElement();

typeElement getTypeElement() {return typeE;}
       void setTypeElement(typeElement _type) {typeE=_type;}

quint8 getIndex() {return index;}
  void setIndex(quint8 _index) {index=_index;}

private:
 typeElement typeE;
     quint8  index;

signals:
  void sendCommand(QByteArray data);
  void sendMessage(QString,QString,int); 

public slots:
virtual void reset() {}
virtual void callStatus() {}

public:
virtual void writeXMLData(QXmlStreamWriter &stream) {}
virtual void  readXMLData(QXmlStreamReader &stream) {}
};

#endif // WLELEMENT_H
