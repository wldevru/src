#ifndef WLGPROGRAMWIDGET_H
#define WLGPROGRAMWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>

#include "ui_wlgprogramwidget.h"


#include "wlgprogram.h"
#include "wlgcodesh.h"


class WLGProgramWidget : public QWidget
{
	Q_OBJECT

public:
    WLGProgramWidget(WLGProgram *_Program,QWidget *parent = nullptr);
    ~WLGProgramWidget();

private:
	void showListProgram(int iCenter);    

private:
    Ui::WLGProgramWidget ui;
	
    bool m_changedProgram;

    WLGProgram *m_GProgram;

    WLGCodeSH *m_GCodeSH;

    int   m_startIProgram;
    int     m_endIProgram;
    int m_sizeListProgram;

    QString m_lastNameProgram;

    int iEditElement=0;

    bool m_trackElementF=true;


signals:

	void changed(bool);
    void changedEditElement(int index);

    void pressOpenFile();

public slots:

	void setEditDisabled(bool);
    void setEditElement(int iElement);
	void loadTextProgram();

private slots:

    void updateTrack();
    void setTrack(bool en) {m_trackElementF=en;}

    void saveTextProgram();

	void onUpdate();
	void onAccept();
	void onBackup();
	void onReload();
    void onOpenFile() {emit pressOpenFile();}

	void onChangedTextProgram();
	void onChangedPositionTextProgram();
	void onChangedPositionListProgram();
};

#endif // WLGPROGRAMWIDGET_H
