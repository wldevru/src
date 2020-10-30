var iM=5
var posSetTool={X:5,Y:20,Z:20}
var posChTool={X:-5,Y:50,Z:50}

function getCurPos(ms)
{
var curPos={X:0,Y:0,Z:0}

X=AXIS.getPos(0)
Y=AXIS.getPos(1)
Z=AXIS.getPos(2)

return curPos
}

function DELAY(ms)
{
TIMER.restart(10);
while(TIMER.getCount(10)<ms); 
}

function WAIT(a)
{
DELAY(100)
return a
}

function M6()
{
}

function M7()
{
MACHINE.setOutput(2,1);
}

function M8()
{
MACHINE.setOutput(3,1);
}

function M9()
{
MACHINE.setOutput(2,0);
MACHINE.setOutput(3,0);
}

function M66()
{
}


function M100()
{
}

function M101()
{
}


function M3()
{
//DIALOG.message("M3 шпиндель включен!",0);
MACHINE.enableSOut(1);
//MACHINE.setOutput(1,1);
return 1;
}

function M4()
{
return 1;
}

function M5()
{
MACHINE.enableSOut(0)
//DIALOG.message("M5",0);
//MACHINE.setOutput(1,0);
//MACHINE.setOutput(3,0);
return 1;
}



function M30()
{
DIALOG.message("M30 конец программы!",0);
}


function userFunc1()
{
var front=!MACHINE.getInProbe()
var str
var Fprobe=50
var nameFile
var step
var X0,X1,Xstep,Xmax
var Y0,Y1,Ystep,Ymax
var buf
var Zback=MACHINE.getCurPositionSC(2)
var dir=1

DIALOG.enterSaveFile("Файл сохранения результатов","")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk())
 nameFile=DIALOG.getString()
else
 return

DIALOG.enterNum("Введите X0=")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
  X0=DIALOG.getNum();
else
  return

DIALOG.enterNum("Введите Y0=")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
  Y0=DIALOG.getNum();
else
  return

DIALOG.enterNum("Введите X1=")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
  X1=DIALOG.getNum();
else
  return

DIALOG.enterNum("Введите Y1=")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
  Y1=DIALOG.getNum();
else
  return

DIALOG.enterNum("Введите максимальный шаг")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
 {
  step=DIALOG.getNum();
  }
else
  return

if(X0==X1||Y0==Y1)
 {
  DIALOG.message("Точки расположены очень близко")
  return
  }

if(X1<X0)
 {
 buf=X0
 X0=X1
 X1=buf
 }

if(Y1<Y0)
 {
 buf=Y0
 Y0=Y1
 Y1=buf
 }

Xmax=Math.ceil((X1-X0)/step);
Ymax=Math.ceil((Y1-Y0)/step);

Xstep=(X1-X0)/Xmax;
Ystep=(Y1-Y0)/Ymax;

FILE.createFile(nameFile) 

for(var i=0, j=0 ;i<=Xmax;i++)
{
 if(dir>0) 
    j=0
else
    j=Ymax

for(;j<=Ymax&&j>=0;j+=dir)
 {
 MACHINE.runGCode("G0 X"+(X0+Xstep*i).toString()+" Y"+(Y0+Ystep*j).toString()+ "Z"+Zback.toString())
 while(WAIT(MACHINE.isActiv()));
 
 MACHINE.goDriveProbe(2,0,50,0)
 while(WAIT(MACHINE.isActiv()));

 MACHINE.runGCode("G0 Z"+Zback.toString())

FILE.write(nameFile,(Math.round((X0+Xstep*i)*100)/100).toString()+","+(Math.round((Y0+Ystep*j)*100)/100).toString()+","+(Math.round(MACHINE.getProbePosition(2,front)*100)/100).toString()+'\r\n') 
  }
dir=-dir;
}  

DIALOG.message("Сканирование успешно завершено!");

return 1;
}

function userFunc2()
{
var front=!MACHINE.getInProbe()
var Fprobe=50
var T= GCODE.getT()
var Zback=MACHINE.getCurPositionSC("Z")

DIALOG.enterNum("Номер инструмента=")
while(WAIT(DIALOG.isShow()));

if(DIALOG.isOk()) 
  T=DIALOG.getNum();
else
  return

MACHINE.runGCode("G0 G53 Z0")
MACHINE.runGCode("G0 G53 X73 Y421")
MACHINE.runGCode("G0 G53 Z-10")
while(WAIT(MACHINE.isActiv()));

MACHINE.goDriveProbe("Z",0,400,0)
while(WAIT(MACHINE.isActiv()));

MACHINE.runGCode("G0 G53 Z0")
while(WAIT(MACHINE.isActiv()));

GCODE.setHTool(T,MACHINE.getProbePosition("Z",front))
return 1;
}

function ON()
{
}

function OFF()
{
}
