#ifndef WLPAD_H
#define WLPAD_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QMutex>

struct dataSS
{
double speed;
double scur;

dataSS() {reset();}
void reset() {speed=scur=0;}

bool isEmpty() {return ((speed==0.0)&&(scur==0.0));}
};

struct dataPad
{
  double Vst;
  double Vma;
  double Aac;
  double Ade;
QString name;

dataPad(){Vst=0;Aac=100;;Vma=100;Ade=-100;}

QString toString()
    {
    QString ret;

    ret=name;
    ret+=","+QString::number(Vst);
    ret+=","+QString::number(Aac);
    ret+=","+QString::number(Vma);
    ret+=","+QString::number(Ade);

	return ret;
    }

bool fromString(QString str)
    {
    QStringList List=str.split(" ");
    if(List.size()==5)
    {
    name=List[0];
    Vst=List[1].toDouble();
    Vma=List[2].toDouble();
    Aac=List[3].toDouble();
    Ade=List[4].toDouble();
    return true;
    }
    else
    {
    QStringList List=str.split(",");
     if(List.size()==5)
     {
     name=List[0];
     Vst=List[1].toDouble();
     Aac=List[2].toDouble();
     Vma=List[3].toDouble();
     Ade=List[4].toDouble();
     return true;
     }
    }

    return false;
    }

void reset()
    {
	name.clear();
	Vst=Vma=Aac=Ade=0;
    }

void fromTT(double _Vst,double _Vma,double _Tac,double _Tde,QString _name)
    {
	this->Vst=_Vst;
	this->Vma=_Vma;
	this->Aac=(_Vma-_Vst)/_Tac;
	this->Ade=(_Vst-_Vma)/_Tde;
	this->name=_name;
    }

void fromAD(double _Vst,double _Vma,double _Aac,double _Ade,QString _name)
    {
	this->Vst=_Vst;
	this->Vma=_Vma;
	this->Aac=_Aac;
	this->Ade=_Ade;
	this->name=_name;
    }

bool isEqu(dataPad Pad)
    {
    return	  (this->Vst==Pad.Vst)
            &&(this->Vma==Pad.Vma)
            &&(this->Aac==Pad.Aac)
            &&(this->Ade==Pad.Ade)
            &&(this->name==Pad.name);
    }
};

class WLPad: public QObject
{
 Q_OBJECT

private:

dataPad m_nowPad;
dataPad m_nowPadBase;

QList <dataPad> Data;
double Vmov;

QMutex Mutex;
public:

WLPad();

~WLPad();
QList <dataPad> getDataList();

void setDataList(QList <dataPad> _Data);

bool SaveAD(double Vst,double Vma,double Aac,double Ade,QString name);
bool SaveTT(double Vst,double Vma,double Tac,double Tde,QString name);

bool Save(dataPad pad);

QString getName();

QList <dataPad> getPads();

dataPad getData(QString name="",bool *ok=nullptr);
bool findData(QString name);

QString toString();
void fromString(QString str);

bool Load(QString);
bool Reload();

bool setSpeed(float spe);
//bool setSS(dataSS data);
bool setSpePer(float  per);
bool addSpeK(float  k);
bool setAccPer(float  per);
bool setAcc(float  acc);
};

#endif // CWLPAD_H
