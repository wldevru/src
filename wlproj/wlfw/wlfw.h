#ifndef WLFW_H
#define WLFW_H

#include <QWidget>
#include "ui_wlfw.h"
#include <QList>
#include <QDir>
#include <QFileDialog>

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

bool conn;

private slots:

	void updateReady(bool enable);

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
	

};

#endif // WLFW_H
