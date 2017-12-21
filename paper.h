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
    string keywords;
    string tag;
    //string authors;
    vector<string> authors;
    //vector<string> references;

    // store which line they are in
    int lineAbstract = -1;
    int lineTitle = -1;
    //int lineReferences = -1;


};

// // for test
//void forTest() {
//    vector<paper *> list;
//    paper test1 = new paper;
//    paper test2 = new paper;
//    list.push_back(test1);
//    list.push_back(test2);
//    test1.title = "test1";
//    test2.title = "test2";
//}

#endif // PAPER_H
