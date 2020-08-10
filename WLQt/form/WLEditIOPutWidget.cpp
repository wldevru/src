#include "WLEditIOPutWidget.h"
#include "ui_WLEditIOPutWidget.h"

WLEditIOPutWidget::WLEditIOPutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLEditIOPutWidget)
{
    m_ModuleIOPut=nullptr;

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
m_ModuleIOPut=_ModuleIOPut;

m_input=_input;

ui->spinBox->setRange(0,(m_input? m_ModuleIOPut->getSizeInputs():m_ModuleIOPut->getSizeOutputs())
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

if(m_ModuleIOPut)
{
pal.setColor(QPalette::Base,m_ModuleIOPut->getInputV(ui->spinBox->value())->getNow() ?
                            QColor(255,150,150)
                            :
                            Qt::white);

ui->spinBox->setPalette(pal);
}
}

void WLEditIOPutWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
if(QMessageBox::question(this,tr("Question")
                        ,m_input ? tr("invert input"):tr("invert output")
                        ,QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
             {
             togInvers();
             }
}


