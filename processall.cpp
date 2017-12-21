#include "processall.h"
#include <string>
#include <vector>
#include "paper.h"
#include "txt.h"
#include "findinfo.h"
#include "mainwindow.h"
#include "export.h"
#include <QApplication>
using namespace std;

// put all the pdf file directely into the build file
vector<paper>* process_all() {
    // check all pdf and find info
    vector<string> txtList = traversePDF();
    vector<vector<string>>* data = readStrings(txtList);
    //data = clean(data);
    vector<paper> *papersList;
    papersList = findInfo(data);
    return papersList;
}

