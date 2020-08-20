#include <QApplication>
#include <QTextCodec>
#include <QLibrary>
#include <QThread>
#include <QDebug>
#include <QTranslator>

#include "wlmill.h"


int main(int argc, char *argv[])
{ 
	QApplication a(argc, argv);

    QTranslator translator;
    translator.load(QApplication::applicationDirPath()+"//lang//WLMill_"+QLocale::system().name());

    a.installTranslator(&translator);

   QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //Windows-1251

    QTextCodec::setCodecForLocale(codec);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //HiDPI pixmaps

    WLMill w;
    w.show();

	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
   
	return a.exec();	
}

