#include "processall.h"
#include <vector>
#include "paper.h"
#include "txt.h"
#include "findinfo.h"
#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
using namespace std;

vector<paper>* process_all(vector<paper>* papersList, vector<string> txtList, vector<string> &newTxtList) {
    // check all pdf and find info
    // the below 2 line is used to read from text
//    vector<paper> *papersList = new vector<paper>;
//    vector<string> txtList = readFromFile(papersList);
    newTxtList.insert(newTxtList.end(), txtList.begin(), txtList.end());
    vector<paper>* tempPaperList = new vector<paper>;
    vector<string> tempTxtList;
    vector<string> findTxtList = traversePDF(); // the new list of all txt
    for (string txt : findTxtList) {
        vector<string>::iterator pos = find(txtList.begin(), txtList.end(), txt);
        if (pos == txtList.end()) {
            tempTxtList.clear();
            tempTxtList.push_back(txt);
            vector<vector<string>>* data = readStrings(tempTxtList);
            tempPaperList = findInfo(data);
            papersList->insert(papersList->end(), tempPaperList->begin(), tempPaperList->end());
            newTxtList.push_back(txt);
        }
    }
    saveToFile(papersList, newTxtList);
    return papersList;

//    vector<string> txtList = traversePDF();
//    vector<vector<string>>* data = readStrings(txtList);
//    vector<paper> *papersList;
//    papersList = findInfo(data);
//    saveToFile(papersList, txtList);
//    return papersList;
}

void saveToFile(vector<paper>* papersList, vector<string> txtList) {
    ofstream file;
    file.open("../../../file.txt");
    ofstream title;
    title.open("../../../title.txt");
    ofstream authors;
    authors.open("../../../authors.txt");
    ofstream abstract;
    abstract.open("../../../abstract.txt");
    ofstream tag;
    tag.open("../../../tag.txt");
    ofstream year;
    year.open("../../../year.txt");
    ofstream keywords;
    keywords.open("../../../keywords.txt");
    ofstream conference;
    conference.open("../../../conferences.txt");
    ofstream DOI;
    DOI.open("../../../DOI.txt");

    for (int i = 0; i < (int)txtList.size(); i++) {
        file << txtList.at(i) << endl;
        title << papersList->at(i).title << endl;
        authors << papersList->at(i).authors << endl;
        abstract << papersList->at(i).abstract << endl;
        tag << papersList->at(i).tag << endl;
        year << papersList->at(i).year << endl;
        keywords << papersList->at(i).keywords << endl;
        conference << papersList->at(i).conference << endl;
        DOI << papersList->at(i).DOI << endl;
    }

    file.close();
    title.close();
    authors.close();
    abstract.close();
    tag.close();
    year.close();
    keywords.close();
    conference.close();
    DOI.close();
    //    int i = 0;
    //    for (string txt : txtList) {
    //        fstream binary_file("../../../"+ txt + ".dat",ios::out|ios::binary|ios::app);
    //        binary_file.write(reinterpret_cast<char *>(papersList->at(i)), sizeof(papersList->at(i)));
    //        binary_file.close();
    //        i++;
    //    }
}

vector<string> readFromFile(vector<paper> *papersList) {
    ifstream file;
    file.open("../../../file.txt");
    vector<string> txtList;
    if(file) {
        ifstream title;
        title.open("../../../title.txt");
        ifstream authors;
        authors.open("../../../authors.txt");
        ifstream abstract;
        abstract.open("../../../abstract.txt");
        ifstream tag;
        tag.open("../../../tag.txt");
        ifstream year;
        year.open("../../../year.txt");
        ifstream keywords;
        keywords.open("../../../keywords.txt");
        ifstream conference;
        conference.open("../../../conferences.txt");
        ifstream DOI;
        DOI.open("../../../DOI.txt");

        string fileLine;
        string titleLine;
        string authorsLine;
        string abstractLine;
        string tagLine;
        string yearLine;
        string keywordsLine;
        string conferenceLine;
        string doiLine;

        while(getline(file, fileLine)) {
            txtList.push_back(fileLine);
            paper newPaper;

            getline(title, titleLine);
            newPaper.title = titleLine;
            getline(authors, authorsLine);
            newPaper.authors = authorsLine;
            getline(abstract, abstractLine);
            newPaper.abstract = abstractLine;
            getline(tag, tagLine);
            newPaper.tag = tagLine;
            getline(year, yearLine);
            newPaper.year = atoi(yearLine.c_str());
            getline(keywords, keywordsLine);
            newPaper.keywords = keywordsLine;
            getline(conference, conferenceLine);
            newPaper.conference = conferenceLine;
            getline(DOI, doiLine);
            newPaper.DOI = doiLine;

            papersList->push_back(newPaper);
        }

        file.close();
        title.close();
        authors.close();
        abstract.close();
        tag.close();
        year.close();
        keywords.close();
        conference.close();
        DOI.close();
        saveToFile(papersList, txtList);
    } else {
        perror("can not find saved data.");
    }
//    fstream binary_file("../../../paperList.dat",ios::binary|ios::in|ios::app);
//    binary_file.seekg (0, ios::end);
//    int size = binary_file.tellg();
//    binary_file.read(reinterpret_cast<char *>(papersList),size);
//    binary_file.close();
    return txtList;
}
