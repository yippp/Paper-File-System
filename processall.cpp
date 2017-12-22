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
}

void saveToFile(vector<paper>* papersList, vector<string> txtList) {
    ofstream file;
    file.open("../../../data/file.txt");
    ofstream title;
    title.open("../../../data/title.txt");
    ofstream authors;
    authors.open("../../../data/authors.txt");
    ofstream abstract;
    abstract.open("../../../data/abstract.txt");
    ofstream tag;
    tag.open("../../../data/tag.txt");
    ofstream year;
    year.open("../../../data/year.txt");
    ofstream keywords;
    keywords.open("../../../data/keywords.txt");
    ofstream conference;
    conference.open("../../../data/conferences.txt");
    ofstream DOI;
    DOI.open("../../../data/DOI.txt");

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
}

vector<string> readFromFile(vector<paper> *papersList) {
    ifstream file;
    file.open("../../../data/file.txt");
    vector<string> txtList;
    if(file) {
        ifstream title;
        title.open("../../../data/title.txt");
        ifstream authors;
        authors.open("../../../data/authors.txt");
        ifstream abstract;
        abstract.open("../../../data/abstract.txt");
        ifstream tag;
        tag.open("../../../data/tag.txt");
        ifstream year;
        year.open("../../../data/year.txt");
        ifstream keywords;
        keywords.open("../../../data/keywords.txt");
        ifstream conference;
        conference.open("../../../data/conferences.txt");
        ifstream DOI;
        DOI.open("../../../data/DOI.txt");

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
    return txtList;
}
