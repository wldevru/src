#ifndef WLIOWidget_H
#define WLIOWidget_H

#include <QTabWidget>
#include <QTableWidget>
#include <QAbstractTableModel>
#include <QModelIndex>

#include "ui_WLIOWidget.h"

#include "WLModuleIOPut.h"
#include "WLModuleAIOPut.h"
#include "WLModulePWM.h"

#define Table_in  0
#define Table_out 1
#define Table_pwm 2

class WLInputViewModel: public QAbstractTableModel
{
Q_OBJECT

public:
    WLInputViewModel(WLModuleIOPut *moduleIOPut,QObject *parent=nullptr):QAbstractTableModel(parent)
    {
    m_moduleIOPut=moduleIOPut;
    connect(moduleIOPut,SIGNAL(changedInput(int)),SLOT(updateInput(int)));
    }

// QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent)   const {Q_UNUSED(parent); return m_moduleIOPut->getSizeInputs();}
    int columnCount(const QModelIndex &parent)const {Q_UNUSED(parent); return 2;}
    QVariant data(const QModelIndex &index, int role) const
    {
    QVariant ret;
    if(index.isValid())
        switch(role)
        {
        case Qt::EditRole:        if(!m_moduleIOPut->getInputV(index.row())->isEnable()) ret=0;
                                  break;

        case Qt::DisplayRole:         if(index.column()==0)
                                               ret=m_moduleIOPut->getInputV(index.row())->getComment();
                                      break;

        case Qt::DecorationRole:      switch(index.column())
                                       {
                                       case 0: ret=m_moduleIOPut->getInputV(index.row())->getNow()? QIcon(":/data/icons/ion.png")
                                                                                                 :  QIcon(":/data/icons/ioff.png");
                                               break;

                                       case 1: ret=m_moduleIOPut->getInputV(index.row())->isInv()? QIcon(":/data/icons/ion.png")
                                                                                                 : QIcon(":/data/icons/ioff.png");
                                               break;
                                       }
                                       break;

        }

    return ret;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
    if (role != Qt::DisplayRole)
              return QVariant();

    if(orientation==Qt::Vertical
     &&section)  return section;

    if(orientation==Qt::Horizontal)
        switch(section)
        {
        case 0: return tr("input");
        case 1: return tr("inv");
        }

     return QVariant();
    }


    Qt::ItemFlags flags(const QModelIndex &index) const
    {
    Qt::ItemFlags ret=Qt::NoItemFlags;
    if(index.isValid()&&m_moduleIOPut->getInputV(index.row())->isEnable())
      {
      ret=Qt::ItemIsEnabled;
      }

    return ret;
    }

    WLModuleIOPut *moduleIOPut() const {return m_moduleIOPut;}

private slots:
    void updateInput(int n) {emit changedData(index(n,0));
                             emit changedData(index(n,1));}

signals:
   void changedData(QModelIndex);

private:
    WLModuleIOPut *m_moduleIOPut;

};

class WLOutputViewModel: public QAbstractTableModel
{
Q_OBJECT

public:
    WLOutputViewModel(WLModuleIOPut *moduleIOPut,QObject *parent=nullptr):QAbstractTableModel(parent)
    {
    m_moduleIOPut=moduleIOPut;
    connect(moduleIOPut,SIGNAL(changedOutput(int)),SLOT(updateOutput(int)));
    }

// QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent)   const {Q_UNUSED(parent); return m_moduleIOPut->getSizeOutputs();}
    int columnCount(const QModelIndex &parent)const {Q_UNUSED(parent); return 2;}
    QVariant data(const QModelIndex &index, int role) const
    {
    QVariant ret;
    if(index.isValid())
        switch(role)
        {
        case Qt::DisplayRole:         if(index.column()==0)
                                               ret=m_moduleIOPut->getOutputV(index.row())->getComment();
                                      break;

        case Qt::DecorationRole:      switch(index.column())
                                       {
                                       case 0: ret=m_moduleIOPut->getOutputV(index.row())->getNow()? QIcon(":/data/icons/ion.png")
                                                                                                 :  QIcon(":/data/icons/ioff.png");
                                               break;

                                       case 1: ret=m_moduleIOPut->getOutputV(index.row())->isInv()? QIcon(":/data/icons/ion.png")
                                                                                                  : QIcon(":/data/icons/ioff.png");
                                               break;
                                       }
                                       break;

        }

    return ret;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
    if (role != Qt::DisplayRole)
              return QVariant();

    if(orientation==Qt::Vertical
     &&section)  return section;

    if(orientation==Qt::Horizontal)
        switch(section)
        {
        case 0: return tr("output");
        case 1: return tr("inv");
        }

     return QVariant();
    }

   Qt::ItemFlags flags(const QModelIndex &index) const
   {
   Qt::ItemFlags ret=Qt::NoItemFlags;
   if(index.isValid()&&m_moduleIOPut->getOutputV(index.row())->isEnable())
     {
     ret=Qt::ItemIsEnabled;
     }

   return ret;
   }

   WLModuleIOPut *moduleIOPut() const {return m_moduleIOPut;}

signals:
    void changedData(QModelIndex);

private slots:
    void updateOutput(int n) {emit changedData(index(n,0));
                              emit changedData(index(n,1));}
private:
    WLModuleIOPut *m_moduleIOPut;

};

class WLOutPWMViewModel: public QAbstractTableModel
{
Q_OBJECT

public:
    WLOutPWMViewModel(WLModulePWM *modulePWM,QObject *parent=nullptr):QAbstractTableModel(parent)
    {
    m_modulePWM=modulePWM;
    connect(modulePWM,SIGNAL(changedOutPWM(int)),SLOT(updateOutPWM(int)));
    }

// QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent)   const {Q_UNUSED(parent); return m_modulePWM->getSizeOutPWM();}
    int columnCount(const QModelIndex &parent)const {Q_UNUSED(parent); return 4;}
    QVariant data(const QModelIndex &index, int role) const
    {
    QVariant ret;
    if(index.isValid())
        switch(role)
        {
        case Qt::EditRole:        if(!m_modulePWM->getOutPWM(index.row())->isEnable()) ret=0;
                                  break;
        case Qt::DisplayRole:         switch(index.column())
                                      {
                                      case 0: ret=QString::number(m_modulePWM->getOutPWM(index.row())->getKOut()*100,'f',2)+"%";break;
                                      case 1: ret=QString::number(m_modulePWM->getOutPWM(index.row())->power(),'f',2)+"%";break;
                                      case 3: ret=QString::number(m_modulePWM->getOutPWM(index.row())->freq(),'f',2)+"%";break;
                                      }
                                      break;

        case Qt::DecorationRole:      switch(index.column())
                                       {
                                       case 2: ret=m_modulePWM->getOutPWM(index.row())->isInv()? QIcon(":/data/icons/ion.png")
                                                                                               : QIcon(":/data/icons/ioff.png");
                                               break;
                                       }
                                       break;

        }

    return ret;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
    if (role != Qt::DisplayRole)
              return QVariant();

    if(orientation==Qt::Vertical
     &&section)  return section;

    if(orientation==Qt::Horizontal)
        switch(section)
        {
        case 0: return    ("K");
        case 1: return tr("value");
        case 2: return tr("inv");
        case 3: return tr("Freq");
        }

     return QVariant();
    }


    Qt::ItemFlags flags(const QModelIndex &index) const
    {
    Qt::ItemFlags ret=Qt::NoItemFlags;
    if(index.isValid()&&m_modulePWM->getOutPWM(index.row())->isEnable())
      {
      ret=Qt::ItemIsEnabled;
      }

    return ret;
    }

    WLModulePWM *modulePWM() const {return m_modulePWM;}

signals:
    void changedData(QModelIndex);

private slots:
    void updateOutPWM(int n) {emit changedData(index(n,0));
                              emit changedData(index(n,1));}
private:
    WLModulePWM *m_modulePWM;

};

namespace Ui {
class  WLIOWidget;
}

class WLIOWidget : public QTabWidget
{
	Q_OBJECT

public:
    WLIOWidget(QWidget *parent = nullptr);
    ~WLIOWidget();

    void setModuleIOPut(WLModuleIOPut *_ModuleIOPut)    {m_inputViewModel  = new WLInputViewModel(_ModuleIOPut);
                                                         m_outputViewModel = new WLOutputViewModel(_ModuleIOPut);}


    void setModulePWM(WLModulePWM *_ModulePWM)          {m_outPWMViewModel = new WLOutPWMViewModel(_ModulePWM);}

    void setModuleAIOPut(WLModuleAIOPut *_ModuleAIOPut) {m_moduleAIOPut=_ModuleAIOPut;}
	void Init();

private:
    Ui::WLIOWidget *ui;
	
    WLInputViewModel   *m_inputViewModel;
    WLOutputViewModel  *m_outputViewModel;
    WLOutPWMViewModel  *m_outPWMViewModel;


    QTableView   *m_tableViewIn;
    QTableView   *m_tableViewOut;
    QTableView   *m_tableViewOutPWM;


    //QTableWidget *TableIn;
   // QTableWidget *TableOut;
    //QTableWidget *TableOutPWM;
    QTableWidget *TableAIn;

    QIcon *m_IconOn;
    QIcon *m_IconOff;

    //WLModuleIOPut  *m_moduleIOPut;
    //WLModulePWM    *m_modulePWM;
    WLModuleAIOPut *m_moduleAIOPut;


private slots:
	void updateData();

    void setDCTableInput(QModelIndex);
    void setDCTableOutput(QModelIndex);
    void setDCTableOutPWM(QModelIndex);

};

#endif // WLIOWidget_H
