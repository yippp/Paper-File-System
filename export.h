#ifndef EXPORT_H
#define EXPORT_H

#include <string>
#include <fstream>
#include <iostream>

#include "paper.h"
using namespace std;

void exportBibTeX(vector<paper>* paperList) {
    // used for export buttom, to export BibTeX format references for all papers
    ofstream txt;
    txt.open("../../../BibTeX.txt");
    paper current;
    for (int i = 0; i < paperList->size(); i++) {
        current = paperList->at(i);

        txt << "@inproceedings{" << i << "," << endl;

        txt << "authors={" << current.authors << "}," << endl;

        txt << "booktitle={" << current.conference << "}," << endl;

        txt << "title={" << current.title << "}," << endl;

        txt << "year={" << current.year << "}," << endl;

        txt << "keywords={" << current.keywords << "}," << endl;

        txt << "doi={" << current.DOI << "}," << endl;

        txt << "}" << endl;
    }
    txt.close();
}

#endif // EXPORT_H
