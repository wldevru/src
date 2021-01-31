#include "wlpamwidget.h"
#include <QDebug>
#include <QTimer>

WLPamWidget::WLPamWidget(dataPad Pad,float Vmax,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	qDebug()<<Pad.toString();
	qDebug()<<"Vmax"<<Vmax;

    //ui.sbVst->setRange(0,Vmax/2);
	//ui.sbVma->setRange(Vmax/2,Vmax);	
	
	ui.sbVst->setValue(Pad.Vst);
	ui.sbVma->setValue(Pad.Vma);
	
	ui.sbAac->setRange(0,99999);
	ui.sbAde->setRange(0,99999);

	ui.sbAac->setValue(Pad.Aac);
	ui.sbAde->setValue(-Pad.Ade);

    ui.cbEditName->insertItems(0,QString("main,mainMinus").split(","));
    ui.cbEditName->lineEdit()->setText(Pad.name);
    //ui.cbSize->addItems(QString("1/sec^2,sec").split(","));

    //connect(ui.cbSize,SIGNAL(currentIndexChanged(int)),SLOT(updateAccelLabel(int)));

	connect(ui.buttonBox,SIGNAL(accepted()),SLOT(onAccept()));
	connect(ui.buttonBox,SIGNAL(rejected()),SLOT(onReject()));

    QTimer *timer=new QTimer;

    connect(timer,SIGNAL(timeout()),SLOT(repaint()));
    timer->start(100);

    setUnit("1");
	setModal(true);

}

WLPamWidget::~WLPamWidget()
{

}

void WLPamWidget::updateVstLabel(double val)
{
ui.sbVma->setRange(val,ui.sbVma->maximum());
}

void WLPamWidget::updateVmaLabel(double val)
{
    ui.sbVst->setRange(0,val);
}

void WLPamWidget::setUnit(QString unit)
{
m_unit=unit;

ui.labelVst->setText("Vst("+m_unit+"/"+tr("s)"));
ui.labelVma->setText("Vma("+m_unit+"/"+tr("s)"));
ui.labelAac->setText("Aac("+m_unit+"/"+tr("s^2)"));
ui.labelAde->setText("Ade("+m_unit+"/"+tr("s^2)"));
}

void WLPamWidget::updateAccelLabel(int index)
{/*
if(index)
{
ui.sbAac->setValue((ui.sbVma->value()-ui.sbVst->value())/ui.sbAac->value());
ui.sbAde->setValue((ui.sbVma->value()-ui.sbVst->value())/ui.sbAde->value());
}
else
{
if(ui.sbAac->value()==0)
   ui.sbAac->setValue((ui.sbVma->value()-ui.sbVst->value())/0.000001);
else
   ui.sbAac->setValue((ui.sbVma->value()-ui.sbVst->value())/ui.sbAac->value());

if(ui.sbAde->value()==0)
   ui.sbAde->setValue((ui.sbVma->value()-ui.sbVst->value())/0.000001);
else
   ui.sbAde->setValue((ui.sbVma->value()-ui.sbVst->value())/ui.sbAde->value());
}
*/
}

dataPad WLPamWidget::getPad()
{
dataPad Pad;
/*
if(ui.cbSize->currentIndex()==1)
 Pad.fromTT(ui.sbVst->value(),ui.sbVma->value(),ui.sbAac->value(), ui.sbAde->value(),ui.lineEditName->text());
else
    */
 Pad.fromAD(ui.sbVst->value(),ui.sbVma->value(),ui.sbAac->value(),-ui.sbAde->value(),ui.cbEditName->currentText());

 return Pad;
}

void WLPamWidget::paintEvent(QPaintEvent *)
{
QPainter painter(this);
painter.setPen(Qt::blue);
painter.setFont(QFont("Arial", 30));

QPen penFocus;
QPen pen;

pen.setWidthF(2);
pen.setColor(QColor(Qt::blue));

penFocus.setWidthF(3);
penFocus.setColor(QColor(Qt::green));

QPoint point,pointLast;
QList <QPoint> pointList;
float kA=1;
float kD=1;

if(ui.sbVst->value()>ui.sbVma->value()) ui.sbVst->setValue(ui.sbVma->value());

if(ui.sbAac->value()>ui.sbAde->value())
 {
 kA=ui.sbAde->value()/ui.sbAac->value();
 }
else
 {
 kD=ui.sbAac->value()/ui.sbAde->value();
 }

if(ui.cbEditName->hasFocus()) pen=penFocus;

painter.setPen(pen);

pointLast.setX(0);
pointLast.setY(ui.sbVst->pos().y()-10);
point=pointLast;
point.setX(ui.sbVst->pos().x()+ui.sbVst->size().width()
           +(1-kA)*ui.sbAac->size().width());

painter.drawLine(pointLast,point);
pointLast=point;
point=pointLast;

if(ui.sbVst->value()!=0.0)
 {
 painter.setPen(ui.sbVst->hasFocus() ? penFocus:pen);
 point.setY(ui.sbVst->pos().y()-10-(ui.sbVst->pos().y()-20)*(ui.sbVst->value()/ui.sbVma->value()));
 painter.drawLine(pointLast,point);
 pointLast=point;
 }

point.setX(ui.sbAac->pos().x()+ui.sbAac->size().width());
point.setY(10);
painter.setPen(ui.sbAac->hasFocus() ? penFocus:pen);
painter.drawLine(pointLast,point);
pointLast=point;

point.setX(ui.sbVma->pos().x()+ui.sbVma->size().width());
painter.setPen(ui.sbVma->hasFocus() ? penFocus:pen);
painter.drawLine(pointLast,point);
pointLast=point;

point.setX(ui.sbAde->pos().x()+ui.sbAac->size().width()
          -(1-kD)*ui.sbAac->size().width());

if(ui.sbVst->value()!=0.0)
  point.setY(ui.sbVst->pos().y()-10-(ui.sbVst->pos().y()-20)*(ui.sbVst->value()/ui.sbVma->value()));
else
  point.setY(ui.sbVst->pos().y()-10);

painter.setPen(ui.sbAde->hasFocus() ? penFocus:pen);
painter.drawLine(pointLast,point);
pointLast=point;

if(ui.sbVst->value()!=0.0)
  {
  painter.setPen(ui.sbVst->hasFocus() ? penFocus:pen);
  point.setY(ui.sbVst->pos().y()-10);
  painter.drawLine(pointLast,point);
  pointLast=point;
  }

painter.setPen(pen);
point.setX(this->size().width());
painter.drawLine(pointLast,point);

}

