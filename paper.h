#ifndef PAPER_H
#define PAPER_H

#include <string>
#include <vector>
using namespace std;

struct paper{
    // structure to save the info for each paper
    string title;
    string abstract;
    string DOI;
    string conference;
    int year;
    string keywords;
    string tag;
    string authors;

    // store which line they are in
    int lineAbstract = -1;
    int lineTitle = -1;
};

#endif // PAPER_H
