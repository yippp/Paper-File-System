#ifndef TXT_H
#define TXT_H
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <ctype.h>

#include "stringrelative.h"
#include "paper.h"
//#include "qdebug.h"
//#include "qdir.h"
using namespace std;

//prototypes
vector<string> traversePDF();
void PDFtoTxt(const string pdf);
vector<vector<string> > *readStrings(const vector<string> txtList);
vector<vector<string>>* clean(vector<vector<string>>* data);


vector<string> traversePDF() { // find all PDF and convert
    vector<string> txtList; // storage the name of all pdf
    struct dirent *ptr;
    DIR *dir;

    dir = opendir("../../../"); // due to Qt GUI will change the working path
    //dir = opendir("./");
    while((ptr=readdir(dir)) != NULL) {
        // Skip"." and ".."
        if(ptr->d_name[0] == '.') {
            continue;
        }

        string filename = ptr->d_name;

        string lowerFilename = toLower(filename); // lowercase
        if (lowerFilename.substr(lowerFilename.size() - 4) == ".pdf") {
            PDFtoTxt(filename); // comment for quick debugging other function
            txtList.push_back(filename.substr(0, filename.size() - 4) + ".txt");
            continue;
        }
    }
    closedir(dir);
    return txtList;
    // TODO: 判断txt是否存在，是则不convert
}


void PDFtoTxt(string const pdf) { // convert PDF to txt witl the same name using pdftotxt
    //string command = "./pdftotext -nodiag " + pdf;
    string command = "../../../pdftotext -nodiag ../../../" + pdf; // due to Qt GUI will change the working path
    system(command.data());
}


vector<vector<string>>* readStrings(vector<string> const txtList) { // read the strings from txt into the program
    vector<vector<string>> *data = new vector<vector<string>>;
    string line;
    ifstream infile;
    vector<string> empty;
    for (string txt : txtList) {
        data->push_back(empty);
        //qDebug()<<QDir::currentPath(); // show the path
        string tempAddress = "../../../" + txt;
        infile.open(tempAddress.c_str());
        while(getline(infile, line)) {
            data->back().push_back(line);
        }
        infile.close();
    }
    return data;
}


vector<vector<string>>* clean(vector<vector<string>>* data) {
    // delete the char which are not in ascii but not <12>(form feed)
    string line;
    string temp;

    for (int i = 0; i < (int)data->size(); i++) {
        for (int j = 0; j < (int)data->at(i).size(); j++) {
            line = data->at(i).at(j);
            temp.erase();

            for (int k = 0; k < (int)line.size() ; k++) {
                if (isascii(line[k]) || int(line[k] == 12)) {
                    temp += line[k];
                }
            }
            data->at(i).at(j) = temp;
        }
    }
    return data;
}

#endif // TXT_H
