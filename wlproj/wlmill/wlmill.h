#ifndef WITELINE_H
#define WITELINE_H

#include <QMainWindow>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QTime>
#include <QPicture>
#include <QToolBar>
#include <QMenuBar>
#include <QDial>
#include <QUdpSocket>
#include <QComboBox>
#include <QColorDialog>
#include <QActionGroup>

#include "wlpamlistwidget.h"
#include "wlvisualwidget.h"
#include "wlpositionwidget.h"
#include "wlgprogram.h"
#include "wllabel.h"
#include "wlmillmachine.h"
#include "wliowidget.h"
#include "wlframe.h"
#include "wlevscript.h"
#include "wlmessmanager.h"
#include "wldialogscript.h"
#include "wlgprogramwidget.h"
#include "wledittext.h"
#include "wlmcodesh.h"
#include "wlmillcontrol.h"
#include "wllog.h"

#define FileState    QCoreApplication::applicationDirPath()+"//state.dat"
#define configWLMill QCoreApplication::applicationDirPath()+"//wlmillconfig//config.xml"

#define VERSION_Y0 (__DATE__[ 7] - '0')
#define VERSION_Y1 (__DATE__[ 8] - '0')
#define VERSION_Y2 (__DATE__[ 9] - '0')
#define VERSION_Y3 (__DATE__[10] - '0')

#define VERSION_M_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define VERSION_M_FEB (__DATE__[0] == 'F')
#define VERSION_M_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define VERSION_M_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define VERSION_M_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define VERSION_M_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define VERSION_M_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define VERSION_M_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define VERSION_M_SEP (__DATE__[0] == 'S')
#define VERSION_M_OCT (__DATE__[0] == 'O')
#define VERSION_M_NOV (__DATE__[0] == 'N')
#define VERSION_M_DEC (__DATE__[0] == 'D')

#define VERSION_M0 ((VERSION_M_OCT || VERSION_M_NOV || VERSION_M_DEC) ? 1 : 0)
#define VERSION_M1 \
    ( \
        (VERSION_M_JAN) ? 1 : \
        (VERSION_M_FEB) ? 2 : \
        (VERSION_M_MAR) ? 3 : \
        (VERSION_M_APR) ? 4 : \
        (VERSION_M_MAY) ? 5 : \
        (VERSION_M_JUN) ? 6 : \
        (VERSION_M_JUL) ? 7 : \
        (VERSION_M_AUG) ? 8 : \
        (VERSION_M_SEP) ? 9 : \
        (VERSION_M_OCT) ? 0 : \
        (VERSION_M_NOV) ? 1 : \
        (VERSION_M_DEC) ? 2 : \
                          0   \
    )

#define VERSION_D0 ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') : 0)
#define VERSION_D1 (__DATE__[ 5] - '0')

#define VERSION_HOUR0 (__TIME__[0] - '0')
#define VERSION_HOUR1 (__TIME__[1] - '0')

#define VERSION_MIN0 (__TIME__[3] - '0')
#define VERSION_MIN1 (__TIME__[4] - '0')

#define VERSION_SEC0 (__TIME__[6] - '0')
#define VERSION_SEC1 (__TIME__[7] - '0')

#define VERSION_DAY       (10U * VERSION_D0 + VERSION_D1)
#define VERSION_MONTH     (10U * VERSION_M0 + VERSION_M1)
#define VERSION_YEAR      (10U * VERSION_Y2 + VERSION_Y3)

#define VERSION_HOUR      (10U * VERSION_HOUR0 + VERSION_HOUR1)
#define VERSION_MIN       (10U * VERSION_MIN0 + VERSION_MIN1)
#define VERSION_SEC       (10U * VERSION_SEC0 + VERSION_SEC1)

#define VERSION_BCD_DAY   (16U * VERSION_D0 + VERSION_D1)
#define VERSION_BCD_MONTH (16U * VERSION_M0 + VERSION_M1)
#define VERSION_BCD_YEAR  (16U * VERSION_Y2 + VERSION_Y3)

#define VERSION_BCD_HOUR  (16U * VERSION_HOUR0 + VERSION_HOUR1)
#define VERSION_BCD_MIN   (16U * VERSION_MIN0 + VERSION_MIN1)
#define VERSION_BCD_SEC   (16U * VERSION_SEC0 + VERSION_SEC1)


class WLMill : public QMainWindow
{

	Q_OBJECT

public:
    WLMill(QWidget *parent = nullptr);
    ~WLMill();

private:

void closeEvent (QCloseEvent * event);
void leaveEvent ( QEvent * event );

/*
void    connectManual();
void disconnectManual();*/

void UpdateFileName();

QString getLastProgram();

private:
bool m_bclose;

private:
//HANDLE mx;

unsigned long m_lifeM;

//Ui::WiteLineClass ui;
QTime TimeNow;
QTime TimeEnd;
int f;

QString        lastFileSC;
WLGProgram  *Program;
WLMillMachine *MillMachine;

WLEVScript *ES;
WLEVScript *ESLoop;


WLLog *Log;

QTime Time;

WLGProgramWidget  *ProgramWidget;
QUdpSocket *remoteComSocket;

QPixmap PixR;	
QPixmap PixY;	
QPixmap PixG;	
//DockProgram
QDockWidget *DockProgram;
QDockWidget *DockPosition;
QDockWidget *DockManual;
QDockWidget *DockIOPut;
QDockWidget *DockMillControl;

//WLSpindleWidget *DockSpindle;
/*
QTextEdit   *TextProgram;

QPushButton *PButtonCreate;
QPushButton *PButtonBackup;
QPushButton *PButtonReload;
*/
//bool fEditProgram;
//DockPam
QDockWidget *DockPam;
QTextEdit *TextPam;
//TBControls
QToolBar    *TBControls;

QDockWidget *DockControls;

//QToolButton *TButtonGo;
//QToolButton *TButtonPause;
//QToolButton *TButtonStop;

QPushButton *ButtonGo;
QPushButton *ButtonConv;
QPushButton *ButtonReset;


QSlider     *DialPercent;
QSlider     *DialSmooth;

QPushButton *PButtonSetTraj;
QPushButton *PButtonGoHome;
QPushButton *PButtonGoBack;
QPushButton *PButtonGoTo;
WLLabel     *SpeedLabel;

WLLabel     *LabelBufSize;

//DockChekers
QDockWidget *DockCheckers;
WLLabel *LabelMade;
WLLabel *LabelOrder;
WLLabel *LabelOrderMade;
//TBVisual
QToolBar *TBView;
QToolBar *TBMessage;
QToolBar *TBScript;
QToolBar *TBWireChild;

WLMillControl *MillControl=nullptr;
/*
QToolBar *TBWireCorrect;
QToolBar *TBWireEdit;
QToolBar *TBWireMovie;
*/
//

WLDialog     *Dialog;

WLEVScript *EVLScript;
WLEVScript *EVMScript;

WLMessManager *MessManager=nullptr;

WLPositionWidget *PositionWidget=nullptr;
WLVisualWidget *VisualWidget=nullptr;

WLIOWidget *IOWidget;

QToolButton *TButtonGo;
QToolButton *TButtonStop;
///
//Menu
QMenuBar *MenuBar;

//QWorkspace *WorkSpace;

QDialog *MW;

public:
        void setLifeM(unsigned long M) {m_lifeM=M;  emit changedLife();}

unsigned long getLifeM() {return m_lifeM;}



private: 
	
 void autoSaveChekers();

 void createDockPosition();

 void createDockControls();
 void createDockProgram();
 void createDockManual();
 void createDockSpindle();
 void createDockMillControl();
 
 void createDockTime();
 
 void createTBControls();

 void createTBView();
 void createTBMcode();
 void createTBMessage();
 void createTBScript();
 void createMenuBar();
 void createDockIOPut();  

 void updateOrderMade();

 void saveDataState();  
 void loadDataState();

  int loadConfig();
 

private slots:
  void saveConfig();
  void readyMachine();

protected:

signals:
    void changedEditElementPos(int);
    void changedLife();
    void closeChild();
	void sendMessage(QString);

private slots:

    void onEditDevice();
    void onEditWhell();
    void onSetColors();

    void onEditDrive(QString nameDrive);

    void onEditDriveX(){onEditDrive("X");}
    void onEditDriveY(){onEditDrive("Y");}
    void onEditDriveZ(){onEditDrive("Z");}
    void onEditDriveA(){onEditDrive("A");}
    void onEditDriveB(){onEditDrive("B");}

    void onEditWLMill();

    void setStateButtonGo(bool state);

	void updateEnableMoved(bool);

    void addLifeM() {m_lifeM++;emit changedLife();}

	void showMessage(QString name,QString data,int code);

	void setFocusPause() {/*TButtonPause->setFocus();*/}

	void updateTitle();

	void onSaveAsProgram();
	void onLoadProgram();

	void onSaveSC();
	void onLoadSC();

	void onEditScript();

	void UpdateTimes();

	void Error(QString,QString);

	void about();
	void help();

    void placeVisualizer();

    // QWidget interfaceplaceVisualizer()
protected:
    void resizeEvent(QResizeEvent *event);

    // QWidget interface
protected:
    void showEvent(QShowEvent *event);

};

#endif // WITELINE_H
