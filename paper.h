#ifndef PAPER_H
#define PAPER_H

#include <string>
#include <vector>
using namespace std;

struct paper{

    string title;
    string abstract;
    string DOI;
    string conference;
    int year;
    vector<string> keywords;
    vector<string> authors;
    vector<string> references;

    // store which line they are in
    int lineAbstract = -1;
    int lineTitle = -1;
    int lineReferences = -1;


};

#endif // PAPER_H
