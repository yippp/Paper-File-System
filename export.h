#ifndef EXPORT_H
#define EXPORT_H

#include <string>
#include <fstream>
#include <iostream>

#include "paper.h"
using namespace std;
void exportBibTeX(vector<paper>* paperList) {
    ofstream txt;
    txt.open("../../../BibTeX.txt");
    paper current;
    string authors;
    for (int i = 0; i < paperList->size(); i++) {
        current = paperList->at(i);
        txt << "@inproceedings{" << i << "," << endl;

        txt << "author={";
        authors = "";
        for (int j = 0; j < current.authors.size(); j++) {
            if (j > 0 && j != current.authors.size() - 1) {
                authors += " and ";
            }
            authors += current.authors.at(j);
        }
        txt << authors << "}," << endl;

        txt << "booktitle={" << current.conference << "}," << endl;

        txt << "title={" << current.title << "}," << endl;

        txt << "year={" << current.year << "}," << endl;

        txt << "keywords={" << current.keywords << "}," << endl;

        txt << "doi={" << current.DOI << "}," << endl;

        txt << "}" << endl;
    }
    txt.close();
}

/*
@INPROCEEDINGS{5277711,
author={S. Marinai},
booktitle={2009 10th International Conference on Document Analysis and Recognition},
title={Metadata Extraction from PDF Papers for Digital Library Ingest},
year={2009},
volume={},
number={},
pages={251-255},
keywords={citation analysis;digital libraries;document image processing;grammars;meta data;PDF papers;PDF parsing;author identification;citation database;digital library software suite;document analysis;layout analysis;low level document image processing;metadata extraction;Data mining;Electronics packaging;HTML;Internet;Labeling;Open source software;Publishing;Software libraries;Software packages;Text analysis;Digital Library;Layout Anlysis;Neural Network;PDF;XML},
doi={10.1109/ICDAR.2009.232},
ISSN={1520-5363},
month={July},}
*/
#endif // EXPORT_H
