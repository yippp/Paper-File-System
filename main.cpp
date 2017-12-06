#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <regex>

#include "paper.h"
#include "stringrelative.h"
#include "txt.h"

using namespace std;

//prototypes
vector<string> traversePDF();
vector<struct paper>* findInfo(vector<vector<string>>* data);
bool findDOI(string line, string &doi);
void findAbstrct(struct paper &newPaper, int lineIndex, string line, bool &nextLine);


int main() {
    vector<string> txtString = traversePDF();
    vector<vector<string>>* data = readStrings(txtString);
    data = clean(data);
    vector<paper> *papersList;
    papersList = findInfo(data);
    return 0;
}


vector<string> traversePDF() { // find all PDF and convert
    vector<string> txtList; // storage the name of all pdf
    struct dirent *ptr;
    DIR *dir;
    dir = opendir("./");
    while((ptr=readdir(dir)) != NULL) {
        // Skip"." and ".."
        if(ptr->d_name[0] == '.') {
            continue;
        }

        string filename = ptr->d_name;

        string lowerFilename = toLower(filename); // lowercase
        if (lowerFilename.substr(lowerFilename.size() - 4) == ".pdf") {
            //PDFtoTxt(filename);
            txtList.push_back(filename.substr(0, filename.size() - 4) + ".txt");
            continue;
        }
    }
    closedir(dir);
    return txtList;
    // TODO: 判断txt是否存在，是则不convert
}




vector<struct paper>* findInfo(vector<vector<string>>* data) {
    vector<struct paper> *papersList = new vector<struct paper>;
    bool DOIfound;
    bool nextLine = false;

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

        DOIfound = false;
        for (int lineIndex = 0; lineIndex < (int)txt.size(); lineIndex++) { // search each line
            string line = txt.at(lineIndex); // the current line
            if (!DOIfound) {
                DOIfound = findDOI(line, newPaper.DOI);
                if (DOIfound) {
                    //cout << "DOI: " << newPaper.DOI << endl;
                }
            }

            if (newPaper.abstract == "") {
                //if (nextLine) cout << "nextline" << endl;
                findAbstrct(newPaper, lineIndex, line, nextLine);

            }
        }
        papersList->push_back(newPaper);
    }
    return papersList;
}


bool findDOI(string line, string &doi) {
    string pattern("10\\.[^\\s\\/]+\\/[^\\s]+"); // regix of DOI
    regex r(pattern);
    smatch results;
    if(regex_search(line, results, r)) {
        doi = results.str();
        return true;
    }
    return false;
}


void findAbstrct(struct paper &newPaper, int lineIndex, string line, bool &nextLine) {
    string simpleLine = toLower(removeSymbol(line));
    string noSpaceLine = removeSpace(line);

    if (simpleLine == "abstract" ) { // content is in the next line
        newPaper.lineAbstract = lineIndex;
        //cout << lineIndex << endl;
        //cout << newPaper.abstract.size() << endl;
        nextLine = true;

    } else if (nextLine) { // with bug
        //newPaper.lineAbstract == lineIndex - 1 &&
        //newPaper.lineAbstract != -1 &&
        //newPaper.abstract.size() == 0
        newPaper.abstract = noSpaceLine;
        //cout << "abstract1: " << newPaper.abstract << endl;
        nextLine = false;

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
