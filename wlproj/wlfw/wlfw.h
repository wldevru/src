#ifndef WLFW_H
#define WLFW_H

#include <QWidget>
#include "ui_wlfw.h"
#include <QList>
#include <QDir>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QClipboard>

#include "wldevfw.h"

class WLFW : public QWidget
{
	Q_OBJECT

public:
    WLFW(QWidget *parent = nullptr);
	~WLFW();

private:
	Ui::WLFWClass ui;

    WLDevFW *DFW;

 QByteArray program;
  QString fileName;
QList <WLDeviceInfo> m_listDevice;

bool m_conn=false;
bool m_reboot=false;
float m_progressReboot=0;

long m_timeReboot=6000;

QTimer *m_timerReboot;

WLDeviceInfo m_rebootDI;

QNetworkAccessManager* m_netManager;

private slots:

    void onReplyFinished();

    void updateRebootProgress();
	void updateReady(bool enable);

    void onCopyUID();
    void onWriteCloud();
	void onPBRead();
	void onPBWrite();
	void onPBConnect();
    void onPBReboot();
    void onUpdateDevices();

	void updateConnect(bool enable);
	void setConnect(bool enable);
	void onCreateFile();

	void saveProgram();
    void setUID96(QString);

	void showEndWrite();
	void showEndRead();
	


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WLFW_H
