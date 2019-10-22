#include "WLIOPut.h"

WLIOPut WLIOPut::In0("In_0.-1",0);
WLIOPut WLIOPut::In1("In_1.-1",1);
WLIOPut WLIOPut::Out("Out.-1",0);

void WLIOPut::setData(quint8 _flags)
{
Flags.m_Data&=0xFF00;
Flags.m_Data|=_flags;

if(getCond()>1) sendChanged();	
}

void WLIOPut::addComment(QString _comment)
{
if((Flags.get(IOPF_input)&&(getIndex()>2))
||(!Flags.get(IOPF_input)&&(getIndex()>1)))
 {
 if(!comment.isEmpty()) comment+=",";

 comment+=_comment;
 }
} 

void WLIOPut::removeComment(QString remcomment)
{
if(!comment.isEmpty()) 
 {
 QStringList List=comment.split(",");

 for(int i=0;i<List.size();i++)
   {
   if(List[i]==remcomment) List.removeAt(i--);
   }

 switch(List.size())
 {
 case 0: comment.clear();break;
 case 1: comment=List.takeFirst();break;
 default:
	     comment.clear();
	     for(int i=0;i<List.size();i++)
		    {
		    if(i!=0) comment+=",";
			comment+=List[i];
		    }
		 break;
 } 
 }

}

 



unsigned char getByteFrom (WLIOPut *B0
	                      ,WLIOPut *B1
						  ,WLIOPut *B2
						  ,WLIOPut *B3
						  ,WLIOPut *B4
						  ,WLIOPut *B5
						  ,WLIOPut *B6
						  ,WLIOPut *B7)
{
unsigned char ret=0;

ret=B0->getNow()? bit0:0
   |B1->getNow()? bit1:0;

if(B2) ret|=B2->getNow()? bit2:0;
 else
 if(B3) ret|=B3->getNow()? bit3:0;
 else
 if(B4) ret|=B4->getNow()? bit4:0;
 else
 if(B5) ret|=B5->getNow()? bit5:0;
 else
 if(B6) ret|=B6->getNow()? bit6:0;
 else 
 if(B7) ret|=B7->getNow()? bit7:0;

return ret;
}

void setByteTo(unsigned char byte
	             ,WLIOPut *B0
				 ,WLIOPut *B1
				 ,WLIOPut *B2
				 ,WLIOPut *B3
				 ,WLIOPut *B4
				 ,WLIOPut *B5
				 ,WLIOPut *B6
				 ,WLIOPut *B7)
{
B0->setOut(byte&bit0);
B1->setOut(byte&bit1);

if(B2) B2->setOut(byte&bit2);
 else
 if(B3) B3->setOut(byte&bit3);
 else
 if(B4) B4->setOut(byte&bit4);
 else
 if(B5) B5->setOut(byte&bit5);
 else
 if(B6) B6->setOut(byte&bit6);
 else
 if(B7) B7->setOut(byte&bit7);
}

void setIOPutInvStr(QString data,WLIOPut *ioputs,int size)
{
QStringList List=data.split(",");
int index;
for(int i=0;i<List.size();i++)
    { 
	index=List[i].toInt();
	if((index<size)
	 &&(index>=0))  ioputs[index].setInv(); 
    }
}

QString getIOPutInvStr(WLIOPut *ioputs,int size)
{
QString List;

for(int i=0;i<size;i++)
     if(ioputs[i].isInv()) 
	  if(List.isEmpty())
		  List+=QString::number(i);
	  else
		  List+=","+QString::number(i);

return  List;
}



void WLIOPut::setInv(bool _inv)
{
if((Flags.get(IOPF_inv))^_inv)
 {
 Flags.set(IOPF_inv,_inv);
 
 QByteArray data;
 QDataStream Stream(&data,QIODevice::WriteOnly);
 
 Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
 Stream.setByteOrder(QDataStream::LittleEndian);
 
 if(Flags.get(IOPF_input))
  Stream<<(quint8)comIOPut_setInputInv<<getIndex()<<(quint8)_inv;
 else
  Stream<<(quint8)comIOPut_setOutputInv<<getIndex()<<(quint8)_inv;
 
 emit sendCommand(data);
 }
}

void WLIOPut::setOut(bool _now)   
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)comIOPut_setOutput<<getIndex()<<(quint8)_now;

emit sendCommand(data);
}
