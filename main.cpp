#include <string>
#include <vector>

#include "paper.h"
#include "txt.h"
#include "findinfo.h"

using namespace std;


// put all the pdf file directely into the build file

int main() {
    vector<string> txtString = traversePDF();
    vector<vector<string>>* data = readStrings(txtString);
    data = clean(data);
    vector<paper> *papersList;
    papersList = findInfo(data);
    return 0;
}
