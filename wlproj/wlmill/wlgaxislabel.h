#ifndef WLGAXISLABEL_H
#define WLGAXISLABEL_H

#include <QWidget>
#include <QPainter>
#include <QSizePolicy>
#include "wlgcode.h"
#include "wlmilldrive.h"

class WLGAxisLabel : public QWidget
{
    Q_OBJECT

public:
    typedef enum {typeName,typeOfst,typePos}type;

public:
    explicit WLGAxisLabel(QWidget *parent = nullptr);

    void setDrive(WLMillDrive *_drive);
    void setGCode(WLGCode *_gcode);

private:
   WLMillDrive *m_drive=nullptr;
   WLGCode     *m_gcode=nullptr;

   QRect rName;
   QRect rPos;
   QRect rF;
   QRect rOfst;

signals:
   void changedPress(QString name,int type);

public slots:
    // QWidget interface

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // WLGAXISLABEL_H
