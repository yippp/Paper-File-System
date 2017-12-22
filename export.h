#ifndef EXPORT_H
#define EXPORT_H

#include <string>
#include <sstream>
#include "paper.h"
using namespace std;

string exportBibTeX(vector<paper>* paperList) {
    // used for export buttom, to export BibTeX format references for all papers
    stringstream txt;
    paper current;
    for (int i = 0; i < (int)paperList->size(); i++) {
        current = paperList->at(i);

        txt << "@inproceedings{" << i << "," << endl;

        txt << "authors={" << (string)current.authors << "}," << endl;

        txt << "booktitle={" << current.conference << "}," << endl;

        txt << "title={" << current.title << "}," << endl;

        txt << "year={" << current.year << "}," << endl;

        txt << "keywords={" << current.keywords << "}," << endl;

        txt << "doi={" << current.DOI << "}," << endl;

        txt << "}" << endl << endl;
    }
    string str = txt.str(); // remove all '\0'
    str.erase(remove(str.begin(), str.end(), '\0'), str.end());
    return str;
}

#endif // EXPORT_H
