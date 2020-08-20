#ifndef WLEDITTEXT_H
#define WLEDITTEXT_H

#include <QDialog>
#include <QTextCodec>
#include "ui_wledittext.h"

class WLEditText : public QDialog
{
	Q_OBJECT

public:
	WLEditText(QWidget *parent = 0);
	~WLEditText();

 void setLabel(QString txt) {ui.label->setText(txt);}

 void setText(QString txt);

 const QString getText() {return ui.textEdit->toPlainText();}

  QTextDocument *getDocument() {return ui.textEdit->document();}
private:
	Ui::WLEditText ui;
};

#endif // WLEDITTEXT_H
