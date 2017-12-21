#include <string>
#include <vector>

#include "paper.h"
#include "txt.h"
#include "findinfo.h"
#include "mainwindow.h"
#include <QApplication>
using namespace std;


// put all the pdf file directely into the build file
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
//
int process_all() {
    // check all pdf and find info
    vector<string> txtList = traversePDF();
    vector<vector<string>>* data = readStrings(txtList);
    data = clean(data);
    vector<paper> *papersList;
    papersList = findInfo(data);
    return 0;
}
