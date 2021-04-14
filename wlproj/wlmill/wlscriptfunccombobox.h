#ifndef WLSCRIPTFUNCCOMBOBOX_H
#define WLSCRIPTFUNCCOMBOBOX_H

#include <QComboBox>

class WLScriptFuncComboBox : public QComboBox
{
Q_OBJECT

public:
    WLScriptFuncComboBox(QWidget *parent = nullptr);

    // QComboBox interface

   bool isShowPopup() {return m_showPopup;}

private:
   bool m_showPopup=false;

public:
   void showPopup() {m_showPopup=true;  QComboBox::showPopup();}
   void hidePopup() {m_showPopup=false; QComboBox::hidePopup();}

};

#endif // WLSCRIPTFUNCCOMBOBOX_H
