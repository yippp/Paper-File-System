#ifndef FINDINFO_H
#define FINDINFO_H

#include <string>
#include <vector>
#include <ctype.h>
#include <regex>
#include <ostream>

#include "paper.h"
#include "stringrelative.h"
#include "txt.h"

// for debug
//#include "qdebug.h"
//#include "qdir.h"

using namespace std;


//prototypes
vector<struct paper>* findInfo(vector<vector<string>>* data);
void findDOI(const string line, string &doi);
void findAbstrct(struct paper &newPaper, const int lineIndex, const string line, bool &nextLine);
void findAuthor(vector<string> &stringFindAuthor, struct paper &newPaper);
void findKeywords(const string line, struct paper &newPaper);


vector<struct paper>* findInfo(vector<vector<string>>* data) {
    // used when click import button to find infomation for papers
    vector<struct paper> *papersList = new vector<struct paper>;
    bool nextLine = false;
    vector<string> stringFindAuthor;

    for (vector<string> txt : *data) {
        struct paper newPaper;

        // find info in each txt
        if (isNum(txt.begin()->substr(0, 4))) { // search first line
            newPaper.conference = removeSpace(txt.at(0).substr(4));
            newPaper.year = stoi(txt.begin()->substr(0, 4));
            //cout << "conference: " << newPaper.conference << endl;
            //cout << "year: " << newPaper.year << endl;
        }
        else {
            newPaper.title = txt.at(0);
            newPaper.lineTitle = 0;
            //cout << "title: " << newPaper.title << endl;
        }

        for (int lineIndex = 0; lineIndex < (int)txt.size(); lineIndex++) {
            // search each line
            string line = txt.at(lineIndex); // the current line

            if (newPaper.DOI == "") {
                findDOI(line, newPaper.DOI);
                //if (newPaper.DOI != "") cout << "DOI: " << newPaper.DOI << endl;
            }

            if (newPaper.title == "" && removeSymbol(line) != "" && lineIndex > 0) {
                // find title
                newPaper.lineTitle = lineIndex;
                newPaper.title = removeSpace(line);
                //cout << lineIndex << " title: " << newPaper.title << endl;
            }

            if (newPaper.abstract == "") {
                //if (nextLine) cout << "nextline" << endl;
                findAbstrct(newPaper, lineIndex, line, nextLine);
            }

            if (newPaper.keywords == "" && newPaper.lineAbstract != -1 &&
                (lineIndex == newPaper.lineAbstract + 1 ||
                lineIndex == newPaper.lineAbstract + 2)) {
                //cout << line << endl;
                findKeywords(line, newPaper);
            }
        }

        stringFindAuthor.clear();
        if (newPaper.lineTitle != -1 && newPaper.lineAbstract != -1) {
            for (int lineIndex = newPaper.lineTitle + 1;
                 lineIndex <= newPaper.lineAbstract - 1; lineIndex++) {
                // find authors between title and abstract
                stringFindAuthor.push_back(txt.at(lineIndex));
            }
            findAuthor(stringFindAuthor, newPaper); // which is slow
        }

        papersList->push_back(newPaper);
    }
    return papersList;
}


void findKeywords(string const line, struct paper &newPaper) {
    // find the keywords
    string noSpaceLine = removeSpace(line);
    string simpleLine = toLower(removeSymbol(line));
    if (simpleLine.substr(0, 8) == "keywords") {
        int begin = -1;
        for (int i = 8; i < (int)noSpaceLine.size(); i++) {
            if (isdigit(noSpaceLine[i]) || isalpha(noSpaceLine[i])) {
                begin = i;
                break;
            }
        }
        newPaper.keywords = noSpaceLine.substr(begin);
        //cout << "keywords: " << newPaper.keywords << endl;
    }
}


void findAuthor(vector<string> &stringFindAuthor, struct paper &newPaper) {
    // use Stanford Named Entity Recognizer to find out people name
    ofstream ofile;
    ofile.open("../../../temp/findAuthor.txt");
    //cout << stringFindAuthor.size() << endl;
    for (string line : stringFindAuthor) {
        if (line != "") {
            ofile << line << endl << endl;
        }
    }
    ofile.close();
    //qDebug()<<QDir::currentPath(); // show the path
    string command = "java -mx700m -cp \"../../../stanford-ner.jar:$scriptdir/lib/*\" \
edu.stanford.nlp.ie.crf.CRFClassifier -loadClassifier ../../../class.crf.ser.gz \
-textFile ../../../temp/findAuthor.txt > ../../../temp/findAuthor.tsv";
    //cout << "ner" << endl;
    system(command.data());
    // call java program to find out the people name and output to tsv file

    // read NER data from tsv file
    ifstream infile;
    vector<string> nerData;
    infile.open("../../../temp/findAuthor.tsv");
    string line;
    while(getline(infile, line)) {
        nerData.push_back(line);
    }
    infile.close();

    vector<string> words;
    bool addComma = true;
    for (string line : nerData) {
        words = split(line, " ");
        for (string word : words) {
            if (word.size() > 7) {
                if (word.substr(word.size() - 7) == "/PERSON") {
                    if (newPaper.authors == "") {
                        newPaper.authors = removeSymbol(word.substr(0, word.size() - 7));
                        //cout << "author1: " << newPaper.authors << endl;
                        addComma = true;
                    } else {
                        newPaper.authors += " " + removeSymbol(word.substr(0, word.size() - 7));
                        if (addComma) {
                            newPaper.authors += ", ";
                            addComma = false;
                        } else {
                            addComma = true;
                        }
                        //cout << "author2: " << newPaper.authors << endl;
                    }
                }
            }
        }
    }
    newPaper.authors = removeSpace(newPaper.authors);
    if (newPaper.authors.size() > 2) {
        if (newPaper.authors.at(newPaper.authors.size() - 1) == ',') {
            newPaper.authors = newPaper.authors.substr(0, newPaper.authors.size() - 2);
        }
    }
}


void findDOI(string const line, string &doi) {
    string pattern("10\\.[^\\s\\/]+\\/[^\\s]+"); // regix of DOI
    regex r(pattern);
    smatch results;
    if(regex_search(line, results, r)) {
        doi = results.str();
    }
}


void findAbstrct(struct paper &newPaper, int const lineIndex, string const line, bool &nextLine) {
    // find the abstract
    string simpleLine = toLower(removeSymbol(line));
    string noSpaceLine = removeSpace(line);

    if (simpleLine == "abstract" ) { // content is in the next line
        newPaper.lineAbstract = lineIndex;
        //cout << lineIndex << endl;
        //cout << newPaper.abstract.size() << endl;
        nextLine = true;
    } else if (nextLine) {
        if (noSpaceLine.size() != 0 && noSpaceLine.size() != 1) {
            //cout << noSpaceLine << endl;
            newPaper.abstract = noSpaceLine;
            nextLine = false;
        }
        //cout << newPaper.lineAbstract << endl;
        //cout << "abstract1: " << newPaper.abstract << endl;

    } else if (simpleLine.substr(0, 8) == "abstract" &&
               (noSpaceLine[8] = ':' || noSpaceLine[8] == '-')) {
        // the content is in the currrentline
        newPaper.lineAbstract = lineIndex;

        int begin = -1;
        for (int i = 8; i < (int)noSpaceLine.size(); i++) {
            if (isdigit(noSpaceLine[i]) || isalpha(noSpaceLine[i])) {
                begin = i;
                break;
            }
        }
        newPaper.abstract = noSpaceLine.substr(begin);
        //cout << "abstract2: " << newPaper.abstract << endl << endl;
    }
}

#endif // FINDINFO_H
