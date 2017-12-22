#include "mainwindow.h"
#include <QApplication>


// put all pdf file into the subfoler "pdf" in the debug folder
int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
//

