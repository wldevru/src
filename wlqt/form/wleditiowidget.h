#ifndef WLEDITIOPUTWIDGETT_H
#define WLEDITIOPUTWIDGETT_H

#include <QWidget>
#include <QIcon>
#include <QMessageBox>
#include "wlmoduleioput.h"
#include "wlmodulepwm.h"
#include "wlmoduleencoder.h"

namespace Ui {
class WLEditIOWidget;
}

class WLEditIOWidget : public QWidget
{
    Q_OBJECT


public:
    explicit WLEditIOWidget(QWidget *parent = nullptr);
    ~WLEditIOWidget();

    void setModule(WLModule *_Module,bool _input=true);
    void setLabel(QString label);

    void setValue(int val);
    int  value();

    WLIOPut *getIOPut() {if(m_Module->type()==typeMIOPut)
                               {
                               WLModuleIOPut *ModuleIOPut = static_cast<WLModuleIOPut*>(m_Module);
                               return  m_input ? ModuleIOPut->getInput(value()): ModuleIOPut->getOutput(value());
                               }
                            else
                               return nullptr;
                        }


    WLEncoder *getEncoder() {if(m_Module->type()==typeMEncoder)
                               {
                               WLModuleEncoder *ModuleEncoder = static_cast<WLModuleEncoder*>(m_Module);
                               return  m_input ? ModuleEncoder->getEncoder(value()): nullptr;
                               }
                            else
                               return nullptr;
                        }

private:
    Ui::WLEditIOWidget *ui;

    bool m_input;
    bool m_enLatchInput;

WLModule *m_Module;

private slots:
   void update();

   void togInvers() {if(m_Module->type()==typeMIOPut) getIOPut()->togInv();}

   void onActTogInvers();
   void onActLatchInput();
   void oActResetEncoder();

   void setLatchInput(int);

   // QWidget interface
protected:   
   void mousePressEvent(QMouseEvent *event);
};

#endif // WLEDITIOPUTWIDGETT_H
