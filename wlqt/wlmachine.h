#ifndef WLMACHINE_H
#define WLMACHINE_H

#include <QObject>
#include <QMutex>
#include <QThread>

#include "wldrive.h"

class WLMachine : public QThread
{
Q_OBJECT

public:
    enum TypeAutoMachine{AUTO_no=0
                        ,AUTO_FindDrivePos};

public:
    WLMachine(QObject *parent=nullptr);

   ~WLMachine();

public:
   void addDrive(WLDrive *_drive);

   //QList <WLDrive*> getDrives() {return m_drives;}
   //WLDrive* getDrive(QString) {WLDrive::getDreturn m_drives;}

public:
QString getStrFindDrivePos()            {return m_strFindDrivePos;}
   void setStrFindDrivePos(QString str) {m_strFindDrivePos=str;}

private:

 bool m_auto=false;
 bool m_ready=false;

 float m_percentManual=25.0f;

 enum TypeAutoMachine m_typeAutoMachine;
 QMutex MutexAuto;

private:
//for find position
QString m_strFindDrivePos;
QList<QString> m_listFindDrivePos;

bool updateFindDrivePos();

private:

virtual bool verifyReadyManualMotion()     {return true;}
virtual bool verifyReadyAutoMotion()       {return true;}
virtual bool isPossiblyManual()            {return true;}

public:

  void SDStop();

           bool isAuto() {return m_auto;}
virtual void   setAuto() {emit changedAuto(m_auto=true);}
virtual void resetAuto() {emit changedAuto(m_auto=false);}

  bool isReady() {return m_ready;}

  void goDriveManual(QString name,int IncDec,float step=0);

Q_INVOKABLE void goDriveFind(QString nameDrive);
Q_INVOKABLE void goDriveTeach(QString nameDrive);
Q_INVOKABLE void goDriveVerify(QString nameDrive);

            void goFindDrivePos();


  bool isActivDrives()  {return  WLDrive::isActivDrives();}

public:
  virtual void updateAuto();

public slots:
   void setPercentManual(float per);
   void setReady(bool ready);

signals:
   void changedAuto(bool);
   void changedReady(bool);

protected:
virtual void init() {}
        void run() {init();exec();}
};

#endif // WLMACHINE_H
