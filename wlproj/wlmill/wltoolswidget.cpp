#include <QMessageBox>

#include "wltoolswidget.h"
#include "ui_wltoolswidget.h"

WLToolsWidget::WLToolsWidget(WLGCode *_GCode,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLToolsWidget)
{
    ui->setupUi(this);

    m_GCode=_GCode;
    connect(m_GCode,&WLGCode::changedTool,this,&WLToolsWidget::updateTableTools);


    connect(ui->pbUpdateTool,SIGNAL(clicked()),SLOT(updateTableTools()));    
    connect(ui->pbAcceptTool,SIGNAL(clicked()),SLOT(onAcceptTableTools()));
    connect(ui->pbSetHToZero,SIGNAL(clicked()),SLOT(onPBSetHToZero()));

    connect(ui->tableTools,&QTableWidget::cellChanged,this,[=](){ui->pbAcceptTool->setEnabled(true);});

    updateTableTools();
}

WLToolsWidget::~WLToolsWidget()
{
    delete ui;
}

void WLToolsWidget::updateTableTools()
{
ui->tableTools->setColumnCount(2);
ui->tableTools->setRowCount(sizeTools-1);

ui->tableTools->setHorizontalHeaderLabels(QString("D,H").split(","));

for(int i=0;i<ui->tableTools->rowCount();i++)
  {
  ui->tableTools->setItem(i,0,new QTableWidgetItem(QString::number(m_GCode->getDataTool(i+1).d)));
  ui->tableTools->setItem(i,1,new QTableWidgetItem(QString::number(m_GCode->getDataTool(i+1).h)));
  }

ui->pbAcceptTool->setEnabled(false);
}

void WLToolsWidget::onAcceptTableTools()
{
double D,H;
WLGTool tool;

for(int i=0;i<ui->tableTools->rowCount();i++)
  {
  tool.d=ui->tableTools->item(i,0)->data(0).toString().toDouble();
  tool.h=ui->tableTools->item(i,1)->data(0).toString().toDouble();

  m_GCode->setDataTool(i+1,tool,false);
  }

ui->pbAcceptTool->setEnabled(false);
}

void WLToolsWidget::onPBSetHToZero()
{
if(QMessageBox::question(this, tr("Question:"),tr("are you sure?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
{
for(int i=0;i<ui->tableTools->rowCount();i++)
  {
  m_GCode->setDataTool(i+1,WLGTool(),false);
  }

updateTableTools();
}
}
