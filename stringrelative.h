#ifndef STRINGRELATIVE_H
#define STRINGRELATIVE_H

#include <algorithm>
#include <ctype.h>
#include <string>

using namespace std;


//prototypes
bool isNum(string str);
string removeSpace(string str);

bool isNum(string str) {
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


string removeSpace(string str) { // remove the string in the begin and end
    string buff(str);
    char space = ' ';
    str.assign(buff.begin() + buff.find_first_not_of(space),
        buff.begin() + buff.find_last_not_of(space) + 1);
    return str;
}

string removeSymbol(string str) { // remove symbol, number and space
    str.erase(remove_if(str.begin(), str.end(),
                        static_cast<int(*)(int)>(&ispunct)), str.end());
    str.erase(remove_if(str.begin(), str.end(),
                        static_cast<int(*)(int)>(&isdigit)), str.end());
    return str;
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

#endif // STRINGRELATIVE_H
