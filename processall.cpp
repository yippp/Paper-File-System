#include <vector>
#include <QApplication>
#include <fstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "processall.h"
#include "paper.h"
#include "txt.h"
#include "findinfo.h"

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
    // create the data folder
    mkdir("../../../data/", S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);


    ofstream file;
    file.open("../../../data/file.dat");
    ofstream title;
    title.open("../../../data/title.dat");
    ofstream authors;
    authors.open("../../../data/authors.dat");
    ofstream abstract;
    abstract.open("../../../data/abstract.dat");
    ofstream tag;
    tag.open("../../../data/tag.dat");
    ofstream year;
    year.open("../../../data/year.dat");
    ofstream keywords;
    keywords.open("../../../data/keywords.dat");
    ofstream conference;
    conference.open("../../../data/conferences.dat");
    ofstream DOI;
    DOI.open("../../../data/DOI.dat");

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
    // read the papers' info from the file in data folder
    ifstream file;
    file.open("../../../data/file.dat");
    vector<string> txtList;
    if(file) {
        // if there is saved data
        ifstream title;
        title.open("../../../data/title.dat");
        ifstream authors;
        authors.open("../../../data/authors.dat");
        ifstream abstract;
        abstract.open("../../../data/abstract.dat");
        ifstream tag;
        tag.open("../../../data/tag.dat");
        ifstream year;
        year.open("../../../data/year.dat");
        ifstream keywords;
        keywords.open("../../../data/keywords.dat");
        ifstream conference;
        conference.open("../../../data/conferences.dat");
        ifstream DOI;
        DOI.open("../../../data/DOI.dat");

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
