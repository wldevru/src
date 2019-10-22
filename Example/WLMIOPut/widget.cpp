#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),SLOT(togOut3()));    
    connect(ui->pushButton_2,SIGNAL(clicked()),SLOT(movA0()));

    MDevice = new WLMotion;

    MDevice->initSerialPort("COM5");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::togOut3()
{
WLModuleIOPut *MIOPut=MDevice->getModuleIOPut();

if(MIOPut)
 {
 MIOPut->getOutputV(3)->setTog();
}
}

void Widget::movA0()
{
WLModuleAxis *MAxis=MDevice->getModuleAxis();
WLAxis *Axis;

if(MAxis)
 {
 Axis=MAxis->getAxis(0);
 if(!Axis->isEnable())
    {
    Axis->setTypePulse(typePulseAxis::AXIS_pulse_SD,0);
    Axis->setEnable(true);
    }
 Axis->setDelaySCurve(0.1);
 Axis->setParMov(100000*16,-100000*16,0,75000*16);
 Axis->mov(0,8000*16,20000*16);
 }
}
