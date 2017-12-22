#ifndef STRINGRELATIVE_H
#define STRINGRELATIVE_H

#include <algorithm>
#include <ctype.h>
#include <string>

using namespace std;


//prototypes
bool isNum(const string str);
string removeSpace(string str);
string removeSymbol(string str);
string toLower(string str);
vector<string> split(const string& str, const string& delimiter);

bool isNum(string const str) {
    for (int i = 0; i < (int)str.size(); i++) {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}


string removeSpace(string str) {
    // remove the string in the begin and end
    string buff(str);
    char space = ' ';
    str.assign(buff.begin() + buff.find_first_not_of(space),
        buff.begin() + buff.find_last_not_of(space) + 1);
    return str;
}

string removeSymbol(string str) {
    // remove symbol, number and space
    str.erase(remove_if(str.begin(), str.end(),
                        static_cast<int(*)(int)>(&ispunct)), str.end());
    str.erase(remove_if(str.begin(), str.end(),
                        static_cast<int(*)(int)>(&isdigit)), str.end());
    return str;
}

string toLower(string str) {
    // lower all chars
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

vector<string> split(const string& str, const string& delimiter) {
    // split the string according to the delimiter and storage in vector words
    vector<string> words;
    if(str == "") {
        return words;
    }

    char *strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());

    char *d = new char[delimiter.length() + 1];
    strcpy(d, delimiter.c_str());

    char *p = strtok(strs, d);
    while(p) {
        words.push_back((string)p);
        p = strtok(NULL, d);
    }

    return words;
}

#endif // STRINGRELATIVE_H
