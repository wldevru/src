#include "wlevscript.h"

WLEVScript::WLEVScript(QObject *parent)
	: QThread(parent)
{
busy=false;
Dialog=nullptr;
engine= new QScriptEngine;
Delay = new WLDelay(engine);
FileAccess = new WLFileAccess(engine);

engine->setProcessEventsInterval(1);
//engine->installTranslatorFunctions
}

WLEVScript::~WLEVScript()
{

}

bool  WLEVScript::setCode(QString _code)      
{
if(isBusy())  
 {
 emit sendMessage("scriptEngine","busy",-1);
 return 0;
 }
else 
 {
 busy=true;
 code=_code;
 engine->evaluate(code);
 QTimer::singleShot(0,this,SLOT(evalCode(void)));
 return 1;
 }
}

bool WLEVScript::runFunc(QString _func)
{
bool ret = false;

if(isBusy()) 
   emit sendMessage("scriptEngine","busy:"+func+"/"+_func,-1);
else 
 {  
 if(code.contains(_func))
   {
   emit changedBusy(busy=true);
   func=_func;

   QTimer::singleShot(0,this,SLOT(evalFunc(void)));

   ret=true;
   }
 }

return ret;
}

void WLEVScript::reset()
{qDebug()<<"resetScript";
 if(isBusy())
    {
     QScriptValue sv;
     //Delay->terminate();
     engine->abortEvaluation(sv);
     emit changedBusy(busy=false);
     emit sendMessage(tr("script"),"brake",-1);
    }
}

void WLEVScript::addDialogWidget(WLDialog *DialogW)
{
    Dialog = new WLDialogObj(this);

    QScriptValue objectDialog = engine->newQObject(Dialog);
    engine->globalObject().setProperty("DIALOG",objectDialog);


    Dialog->setWidgetDialog(DialogW);
/*
connect(Dialog,SIGNAL(buildMessage(QString)),DialogW,SLOT(showMessage(QString)));
connect(Dialog,SIGNAL(buildEnterNum(QString)),DialogW,SLOT(showEnterNum(QString)));
connect(Dialog,SIGNAL(buildEnterString(QString)),DialogW,SLOT(showEnterString(QString)));

connect(DialogW,SIGNAL(enterNum(double)),Dialog,SLOT(setNum(double)));
connect(DialogW,SIGNAL(enterString(QString)),Dialog,SLOT(setString(QString)));
connect(DialogW,SIGNAL(enterCancel()),Dialog,SLOT(setCancel()));
*/
connect(Dialog,SIGNAL(sendMessage(QString,QString,int)),SIGNAL(sendMessage(QString,QString,int)));

}

void WLEVScript::run()
{
Delay->start();

QScriptValue objectDelay = engine->newQObject(Delay);
engine->globalObject().setProperty("TIMER",objectDelay);

QScriptValue objectFAccess = engine->newQObject(FileAccess);
engine->globalObject().setProperty("FILE",objectFAccess);

qDebug()<<"WLEVScript run"<<"thread"<<(this);

exec();
qDebug()<<"WLEVScript out";
}



void WLEVScript::evalFunc() 
{
Dialog->reset();

if(code.contains(func)){
QScriptValue svfunc = engine->evaluate(func);
//if(Dialog!=NULL) Dialog->reset();
//svfunc=svfunc.call(QScriptValue(),vList);

if(svfunc.isError())   {
    emit sendMessage("scriptEngine",svfunc.toString(),-1);
   }
else {
   emit changedBusy(busy=false);
   emit complete(func);
   }

//qDebug()<<"retScript"<<svfunc.property("X").toString();
//qDebug()<<"retScript"<<svfunc.property("Y").toString();
//qDebug()<<"retScript"<<svfunc.property("Z").toString();

//qDebug()<<"retScript"<<svfunc.property(0).toString();
//qDebug()<<"retScript"<<svfunc.property(1).toString();
//qDebug()<<"retScript"<<engine->importedExtensions()[0];
}
else
 emit changedBusy(busy=false);


qDebug()<<"retScript";
};

void WLEVScript::evalCode() 
{
QScriptValue svcode=engine->evaluate(code);

if(svcode.isError()) emit sendMessage("scriptEngine",svcode.toString(),-1);

busy=false;
emit complete(code);
};
