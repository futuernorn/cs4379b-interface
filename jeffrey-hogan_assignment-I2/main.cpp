// Source copied from http://qt-project.org/doc/qt-4.8/mainwindows-dockwidgets.html

 #include <QApplication>

 #include "mainwindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     MainWindow mainWin;
     mainWin.show();
     return app.exec();
 }

