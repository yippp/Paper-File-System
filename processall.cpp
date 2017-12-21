#include "processall.h"
#include <vector>
#include "paper.h"
#include "txt.h"
#include "findinfo.h"
#include "mainwindow.h"
#include <QApplication>
#include <fstream>
using namespace std;

vector<paper>* process_all() {
    // check all pdf and find info
    vector<string> txtList = traversePDF();
    vector<vector<string>>* data = readStrings(txtList);
    //data = clean(data);
    vector<paper> *papersList;
    papersList = findInfo(data);
    //saveToFile(papersList, txtList);
    cout<< sizeof(papersList->at(1)) << endl;
    return papersList;
}

void saveToFile(vector<paper>* papersList, vector<string> txtList) {
//    int i = 0;
//    for (string txt : txtList) {
//        fstream binary_file("../../../"+ txt + ".dat",ios::out|ios::binary|ios::app);
//        binary_file.write(reinterpret_cast<char *>(papersList->at(i)), sizeof(papersList->at(i)));
//        binary_file.close();
//        i++;
//    }

}

vector<paper>* readFromFile() {
    vector<struct paper> *papersList = new vector<struct paper>;
    fstream binary_file("../../../paperList.dat",ios::binary|ios::in|ios::app);
    binary_file.seekg (0, ios::end);
    int size = binary_file.tellg();
    binary_file.read(reinterpret_cast<char *>(papersList),size);
    binary_file.close();
    return papersList;
}
