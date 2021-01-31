#include "wlmpgwidget.h"
#include "ui_wlmpgwidget.h"

WLMPGWidget::WLMPGWidget(WLWhell *_whell,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLMPGWidget)
{
    ui->setupUi(this);

    m_whell=_whell;

    ui->buttonGroupAxis->setId(ui->rbOff,0);
    ui->buttonGroupAxis->setId(ui->rbX,1);
    ui->buttonGroupAxis->setId(ui->rbY,2);
    ui->buttonGroupAxis->setId(ui->rbZ,3);
    ui->buttonGroupAxis->setId(ui->rb4,4);
    ui->buttonGroupAxis->setId(ui->rb5,5);
    ui->buttonGroupAxis->setId(ui->rb6,6);

    ui->buttonGroupX->setId(ui->rbX1,1);
    ui->buttonGroupX->setId(ui->rbX10,2);
    ui->buttonGroupX->setId(ui->rbX100,3);

    update();
}

WLMPGWidget::~WLMPGWidget()
{
    delete ui;
}


void WLMPGWidget::update()
{
if(m_whell==nullptr)
  {
  setDisabled(true);
  }
else
  {
  ui->groupBoxAxis->setEnabled(m_whell->isManualAxis());
  ui->groupBoxX->setEnabled(m_whell->isManualX());
  ui->groupBoxV->setEnabled(m_whell->isManualV());

  connect(ui->buttonGroupAxis,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked)
          ,this,[=](int id){m_whell->setIndexAxis(static_cast<quint8>(id));});

  connect(ui->buttonGroupX,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked)
          ,this,[=](int id){m_whell->setIndexX(static_cast<quint8>(id));});

  connect(ui->cbVmode,&QCheckBox::clicked,[=](bool ch){m_whell->setVmode(ch);});

  connect(m_whell,&WLWhell::changedCurIndexAxis,this,[=](quint8 index){if(ui->buttonGroupAxis->button(index)!=nullptr)
                                                                       ui->buttonGroupAxis->button(index)->setChecked(true);});

  connect(m_whell,&WLWhell::changedCurIndexX,this,[=](quint8 index){if(ui->buttonGroupX->button(index)!=nullptr)
                                                                       ui->buttonGroupX->button(index)->setChecked(true);});

  connect(m_whell,&WLWhell::changedCurVmode,this,[=](bool ch){ui->cbVmode->setChecked(ch);});

  quint8 index;

  index=m_whell->getCurIndexAxis();

  if(ui->buttonGroupAxis->button(index)!=nullptr)
      ui->buttonGroupAxis->button(index)->setChecked(true);

  index=m_whell->getCurIndexX();

  if(ui->buttonGroupX->button(index)!=nullptr)
     ui->buttonGroupX->button(index)->setChecked(true);

  ui->cbVmode->setChecked(m_whell->getCurVmode());
}
}

void WLMPGWidget::keyPressEvent(QKeyEvent *event)
{
if(!event->isAutoRepeat())
{
if(ui->groupBoxAxis->isEnabled())
switch(event->key())
   {
   case Qt::Key_0:
   case Qt::Key_1:
   case Qt::Key_2:
   case Qt::Key_3:
   case Qt::Key_4:
   case Qt::Key_5:
   case Qt::Key_6:  ui->buttonGroupAxis->button(event->key()-Qt::Key_0)->click();
   }

if(ui->groupBoxX->isEnabled())
switch(event->key())
   {
   case Qt::Key_Q:  ui->buttonGroupX->button(1)->click();break;
   case Qt::Key_W:  ui->buttonGroupX->button(2)->click();break;
   case Qt::Key_E:  ui->buttonGroupX->button(3)->click();break;
   }

if(ui->groupBoxV->isEnabled())
switch(event->key())
   {
   case Qt::Key_V:  ui->cbVmode->click();break;
   }
}

}
