#include "wledittext.h"

WLEditText::WLEditText(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    connect(ui.lineEditFind,&QLineEdit::returnPressed,this,[=](){
    ui.textEdit->find(ui.lineEditFind->text()
                    ,(ui.cbBackFind->isChecked() ? QTextDocument::FindBackward:QTextDocument::FindFlags()));
    });

    connect(ui.cbFunction,&QComboBox::currentTextChanged,[=](QString func){
     QString txt=ui.textEdit->toPlainText();
     int pos=txt.indexOf(func);

     if(pos!=-1) {
        QTextCursor cursor=ui.textEdit->textCursor();

        ui.textEdit->setFocus();

        cursor.setPosition(pos);

        cursor.select(QTextCursor::LineUnderCursor);

        ui.textEdit->setTextCursor(cursor);
        }

     });

    QTimer *timer=new QTimer;

    connect(timer,&QTimer::timeout,this,&WLEditText::updateFunctionIndex);
    timer->start(2000);

}

WLEditText::~WLEditText()
{

}

void WLEditText::setText(QString txt)
{
ui.textEdit->setText(txt);
updateFunctionIndex();
}

void WLEditText::updateFunctionIndex()
{
if(ui.cbFunction->isShowPopup())  return;

QString txt=ui.textEdit->toPlainText();
QStringList list;
QRegExp RegExp("function[\\s]+[\\S]+[(][^(]*[)]");

int pos = 0;

while ((pos = RegExp.indexIn(txt, pos)) != -1)
{
list+=txt.mid(pos,RegExp.matchedLength());

qDebug()<<pos<<RegExp.matchedLength();

pos+=RegExp.matchedLength();
}

ui.cbFunction->blockSignals(true);
ui.cbFunction->clear();
ui.cbFunction->addItems(list);
ui.cbFunction->blockSignals(false);
}


void WLEditText::keyPressEvent(QKeyEvent *event)
{
event->accept();
}

