#include "wlpamlistwidget.h"


WLPamListWidget::WLPamListWidget(WLDrive *_drive,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLPamListWidget)
{
    m_Drive=_drive;

    padList=m_Drive->pad()->getDataList();

    ui->setupUi(this);

    setEnabledEditVst(false);

    connect(ui->pbAdd,SIGNAL(clicked()),SLOT(add()));
    connect(ui->pbRem,SIGNAL(clicked()),SLOT(remove()));
    connect(ui->pbEdit,SIGNAL(clicked()),SLOT(edit()));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),SLOT(edit(int,int)));

    updateTable();
    setWindowTitle(windowTitle()+" : "+m_Drive->getName());

    setUnit("1");
}

WLPamListWidget::~WLPamListWidget()
{
    delete ui;
}

void WLPamListWidget::updateTable()
{
ui->tableWidget->setColumnCount(5);
ui->tableWidget->setRowCount(padList.size());

QString uV=m_unit+"/"+tr("s");
QString uA=m_unit+"/"+tr("s^2");

ui->tableWidget->setHorizontalHeaderLabels(QString(tr("Name")+",Vst("+uV+"),Aac("+uA+"),Vma("+uV+"),Ade("+uA+")").split(","));

QTableWidgetItem *item;

for(int i=0;i<ui->tableWidget->rowCount();i++)
 {
 item = new  QTableWidgetItem;
 item->setFlags(Qt::ItemIsEnabled);
 item->setText(padList[i].name);
 ui->tableWidget->setItem(i,0,item);

 item = new  QTableWidgetItem;
 item->setFlags(Qt::ItemIsEnabled);
 item->setText(QString::number(padList[i].Vst));
 ui->tableWidget->setItem(i,1,item);

 item = new  QTableWidgetItem;
 item->setFlags(Qt::ItemIsEnabled);
 item->setText(QString::number(padList[i].Aac));
 ui->tableWidget->setItem(i,2,item);

 item = new  QTableWidgetItem;
 item->setFlags(Qt::ItemIsEnabled);
 item->setText(QString::number(padList[i].Vma));
 ui->tableWidget->setItem(i,3,item);

 item = new  QTableWidgetItem;
 item->setFlags(Qt::ItemIsEnabled);
 item->setText(QString::number(-padList[i].Ade));
 ui->tableWidget->setItem(i,4,item);
}

ui->tableWidget->resizeColumnsToContents();
}

void WLPamListWidget::remove()
{
if(padList[ui->tableWidget->currentRow()].name.toLower()!="main")
 {
 padList.removeAt(ui->tableWidget->currentRow());
 updateTable();
 }
}

void WLPamListWidget::add()
{
dataPad pad;

pad.name="newPad";

WLPamWidget PW(pad,10000,this);

PW.setEnabledEditVst(false);

PW.show();
if(PW.exec())
 {
 pad=PW.getPad();
 padList+=pad;
 updateTable();
 }
}

void WLPamListWidget::edit(int row, int count)
{
if(row<0
 ||row>=padList.size()) return;

WLPamWidget PW(padList[row],10000,this);

if(padList[row].name.toLower()=="main") PW.setEnabledEditName(false);

PW.setEnabledEditVst(m_editVst);
PW.setUnit(m_unit);
PW.show();

if(PW.exec())
 {
 padList[row]=PW.getPad();
 }

updateTable();
}

void WLPamListWidget::edit()
{
qDebug()<<ui->tableWidget->currentRow();
edit(ui->tableWidget->currentRow()
    ,ui->tableWidget->currentColumn());
}

void WLPamListWidget::setUnit(QString unit)
{
m_unit=unit;
updateTable();
}


