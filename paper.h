#ifndef PAPER_H
#define PAPER_H

#include <string>
#include <vector>

struct paper{
    string title;
    string abstract;
    string DOI;
    string conference;
    vector<string> keywords;
    vector<string> authors;
    vector<string> references;

};
#endif // PAPER_H
