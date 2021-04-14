#ifndef WLEDITTEXT_H
#define WLEDITTEXT_H

#include <QDialog>
#include <QTextCodec>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

#include "wlscriptfunccombobox.h"
#include "ui_wledittext.h"


class WLEditText : public QDialog
{
	Q_OBJECT

public:
    WLEditText(QWidget *parent = nullptr);
	~WLEditText();

 void setLabel(QString txt) {ui.label->setText(txt);}

 void setText(QString txt);

 const QString getText() {return ui.textEdit->toPlainText();}

 QTextDocument *getDocument() {return ui.textEdit->document();}
private:
	Ui::WLEditText ui;

private slots:
    void updateFunctionIndex();
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WLEDITTEXT_H
