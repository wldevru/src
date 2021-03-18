#ifndef WLGPROGRAMWIDGET_H
#define WLGPROGRAMWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QStyledItemDelegate>

#include "ui_wlgprogramwidget.h"


#include "wlgprogram.h"
#include "wlgcodesh.h"

class WLGProgramListDelegate: public QStyledItemDelegate
{
Q_OBJECT

public:
    WLGProgramListDelegate() {}

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
         {
      /*   if((option.state & QStyle::State_HasFocus))// || (option.state & QStyle::State_MouseOver))
           {
               // get the color to paint with
               QVariant var = index.model()->data(index, Qt::BackgroundRole);


               // draw the row and its content
               painter->fillRect(option.rect, var.value<QColor>());
               painter->drawText(option.rect, index.model()->data(index, Qt::DisplayRole).toString());
           }
           else*/
              QStyledItemDelegate::paint(painter, option, index);
         }
};

class WLGProgramWidget : public QWidget
{
	Q_OBJECT

public:
    WLGProgramWidget(WLGProgram *_Program,QWidget *parent = nullptr);
    ~WLGProgramWidget();

private:
	void showListProgram(int iCenter);    

    bool isListProgram() {return ui.stackedWidget->currentIndex()==0;}

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

    QListWidgetItem *itemSelect=nullptr;

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
    void onChangedPositionListProgram(QListWidgetItem*,QListWidgetItem*);
};

#endif // WLGPROGRAMWIDGET_H
