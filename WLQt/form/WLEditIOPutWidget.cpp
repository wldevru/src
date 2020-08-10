#include "WLEditIOPutWidget.h"
#include "ui_WLEditIOPutWidget.h"

WLEditIOPutWidget::WLEditIOPutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLEditIOPutWidget)
{
    ModuleIOPut=nullptr;

    ui->setupUi(this);

    ui->spinBox->setEnabled(false);

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),SLOT(update()));
    timer->start(50);

}

WLEditIOPutWidget::~WLEditIOPutWidget()
{
delete ui;
}

void WLEditIOPutWidget::setModuleIOPut(WLModuleIOPut *_ModuleIOPut,bool _input)
{
ModuleIOPut=_ModuleIOPut;

m_input=_input;

ui->spinBox->setRange(0,(m_input? ModuleIOPut->getSizeInputs():ModuleIOPut->getSizeOutputs())
                         -1);
ui->spinBox->setEnabled(true);
}

void WLEditIOPutWidget::setLabel(QString label)
{
    ui->label->setText(label);
}

void WLEditIOPutWidget::setValue(int val)
{
ui->spinBox->setValue(val);
}

int WLEditIOPutWidget::value()
{
return ui->spinBox->value();
}

void WLEditIOPutWidget::update()
{
QPalette pal;

if(ModuleIOPut)
{
pal.setColor(QPalette::Base,ModuleIOPut->getInputV(ui->spinBox->value())->getNow() ?
                            QColor(255,150,150)
                            :
                            Qt::white);

ui->spinBox->setPalette(pal);
}
}
