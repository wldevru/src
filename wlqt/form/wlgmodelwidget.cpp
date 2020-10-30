#include "wlgmodelwidget.h"
#include "ui_wlgmodelwidget.h"

WLGModelWidget::WLGModelWidget(WLGModel *_GModel,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLGModelWidget)
{
    ui->setupUi(this);

    m_GModel=_GModel;

    createTable();

    ui->lineEdit->setText(m_GModel->getStrAxis());

    setModal(true);
    setWindowTitle("GModel");
}

WLGModelWidget::~WLGModelWidget()
{
   delete ui;
}

void WLGModelWidget::createTable()
{
 ui->tableWidget->clear();
 ui->tableWidget->setColumnCount(2);
 ui->tableWidget->setRowCount(6);

 ui->tableWidget->setHorizontalHeaderLabels(QString(tr("Offset,Direction")).split(","));
 ui->tableWidget->setVerticalHeaderLabels(QString(("GX,GY,GZ,GA,GB,GC")).split(","));

 ui->tableWidget->setItem(0,0,new QTableWidgetItem(m_GModel->getX().ofstFrame.toString()));
 ui->tableWidget->setItem(1,0,new QTableWidgetItem(m_GModel->getY().ofstFrame.toString()));
 ui->tableWidget->setItem(2,0,new QTableWidgetItem(m_GModel->getZ().ofstFrame.toString()));
 ui->tableWidget->setItem(3,0,new QTableWidgetItem(m_GModel->getA().ofstFrame.toString()));
 ui->tableWidget->setItem(4,0,new QTableWidgetItem(m_GModel->getB().ofstFrame.toString()));
 ui->tableWidget->setItem(5,0,new QTableWidgetItem(m_GModel->getC().ofstFrame.toString()));

 ui->tableWidget->setItem(0,1,new QTableWidgetItem(m_GModel->getX().dirFrame.toString()));
 ui->tableWidget->setItem(1,1,new QTableWidgetItem(m_GModel->getY().dirFrame.toString()));
 ui->tableWidget->setItem(2,1,new QTableWidgetItem(m_GModel->getZ().dirFrame.toString()));
 ui->tableWidget->setItem(3,1,new QTableWidgetItem(m_GModel->getA().dirFrame.toString()));
 ui->tableWidget->setItem(4,1,new QTableWidgetItem(m_GModel->getB().dirFrame.toString()));
 ui->tableWidget->setItem(5,1,new QTableWidgetItem(m_GModel->getC().dirFrame.toString()));

 ui->tableWidget->resizeColumnsToContents();
}

void WLGModelWidget::saveData()
{
 m_GModel->setStrAxis(ui->lineEdit->text());

 SAxisGModel sa;

 sa=m_GModel->getX();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(0,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(0,1)->text());
 m_GModel->setX(sa);

 sa=m_GModel->getY();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(1,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(1,1)->text());
 m_GModel->setY(sa);

 sa=m_GModel->getZ();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(2,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(2,1)->text());
 m_GModel->setZ(sa);

 sa=m_GModel->getA();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(3,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(3,1)->text());
 m_GModel->setA(sa);

 sa=m_GModel->getB();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(4,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(4,1)->text());
  m_GModel->setB(sa);

 sa=m_GModel->getC();
 sa.ofstFrame.fromString(ui->tableWidget->takeItem(5,0)->text());
  sa.dirFrame.fromString(ui->tableWidget->takeItem(5,1)->text());
  m_GModel->setC(sa);

}
