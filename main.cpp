#include <QtGui>
#include <QtWidgets>
#include <QtQml>

#include "MainWindow.h"
#include "WindowFramelessHelper.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    QFont f("黑体",10);
    a.setFont(f);

    QDir::setCurrent(a.applicationDirPath());

    MainWindow w;
    w.show();

    return a.exec();
}
