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

using namespace std;

//prototypes
void PDFtoTxt(string pdf);
vector<vector<string> > *readStrings(vector<string> txtList);
vector<vector<string>>* clean(vector<vector<string>>* data);

void PDFtoTxt(string pdf) { // convert PDF to txt witl the same name using pdftotxt
    string command = "./pdftotext -nodiag " + pdf;
    system(command.data());
}


vector<vector<string>>* readStrings(vector<string> txtList) { // read the strings from txt into the program
    vector<vector<string>> *data = new vector<vector<string>>;
    string line;
    ifstream infile;
    vector<string> newText;

    for (string txt : txtList) {
        data->push_back(newText);
        infile.open(txt.c_str());
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
