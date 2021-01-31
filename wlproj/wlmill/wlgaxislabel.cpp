#include "wlgaxislabel.h"

WLGAxisLabel::WLGAxisLabel(QWidget *parent) : QWidget(parent)
{
//setMaximumSize(300,60);
setMinimumSize(200,20);

setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

setVisible(false);

setToolTip(tr("press for edit"));
}

void WLGAxisLabel::setDrive(WLMillDrive *_drive)
{
m_drive=_drive;

setVisible(m_drive ? true : false);
}

void WLGAxisLabel::setGCode(WLGCode *_gcode)
{
m_gcode=_gcode;
}

void WLGAxisLabel::paintEvent(QPaintEvent *event)
{
QPainter painter(this);
QFont font;
QColor colorF=QColor(Qt::darkGreen);
painter.setPen(QColor(Qt::black));
//painter.drawRect(0,0,this->width()-1,this->height()-1);
QString name=m_drive ? m_drive->getName() : "?";
QString  pos=m_drive ? QString("%1").arg(m_drive->getAxisPosition(),0,'f',2) : "0000.00";
QString    f=m_drive ? QString("%1").arg(m_drive->Vnow()*60,0,'f',2) : "0000.00";

QString ofst;
  float Hofst=0;

if(m_gcode)
   {
  if(name=="Z")
     {
     if(m_gcode->isGCode(43))
       {
       Hofst=- m_gcode->getHvalue();
       }
       else if(m_gcode->isGCode(44))
         {
         Hofst=m_gcode->getHvalue();
         }
     }

   ofst=QString("%1").arg(m_GPos,0,'f',2);

   if(name=="Z")
      {
      if(m_gcode->isGCode(43))
        {
        f=" +H"+QString::number(m_gcode->getValue('H'));
        colorF=QColor(Qt::red);
        }
        else if(m_gcode->isGCode(44))
          {
          f=" -H"+QString::number(m_gcode->getValue('H'));
          colorF=QColor(Qt::blue);
          }
      }
   }
else
   ofst=pos;

if(isChecked()) ofst+="*";

rName.setX(0);
rName.setY(0);
rName.setHeight(this->height()-1);
rName.setWidth(this->height()*1.5f);

painter.setPen(QColor(Qt::black));
font=painter.font();

font.setPixelSize(rName.height());

painter.setFont(font);
painter.drawText(rName,Qt::AlignCenter,name+":");

painter.drawRoundedRect(0,0,this->width()-1,this->height()-1,3,3);
//painter.drawText(rF,Qt::AlignVCenter|Qt::AlignRight,"F:");

//painter.drawRect(rName);

rPos.setTopLeft(QPoint(this->width()-this->width()/4,(this->height()-2)/2));
rPos.setBottomRight(QPoint(this->width()-2,this->height()-2));

font.setPixelSize((rName.height())/2);
painter.setFont(font);
painter.setPen(QColor(Qt::darkRed));
painter.drawText(rPos,Qt::AlignVCenter|Qt::AlignRight,pos);
//painter.drawRect(rPos);


rF.setBottomLeft(rPos.topLeft());
rF.setTopRight(QPoint(this->width()-2,0));

rOfst.setBottomLeft(rName.bottomRight());
rOfst.setTopRight(rF.topLeft());

painter.setPen(colorF);

painter.drawText(rF,Qt::AlignVCenter|Qt::AlignRight,f);

font.setPixelSize(rName.height()-2);
painter.setFont(font);
if(m_drive)
  {
  painter.setPen(m_drive->isTruPosition() ?  QColor(Qt::black) : QColor(Qt::red));
  }
else
   painter.setPen(QColor(Qt::darkRed));

painter.drawText(rOfst,Qt::AlignLeft,ofst);

painter.end();


}

void WLGAxisLabel::mousePressEvent(QMouseEvent *event)
{
if(!m_drive) return;

if(rName.contains(event->pos())) {
    emit changedPress(m_drive->getName(),typeName);

}
 else if(rOfst.contains(event->pos())) emit changedPress(m_drive->getName(),typeOfst);
       else if((rF.contains(event->pos()))
             ||(rPos.contains(event->pos()))) emit changedPress(m_drive->getName(),typePos);
}

