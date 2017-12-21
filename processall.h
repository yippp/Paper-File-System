#ifndef PROCESSALL_H
#define PROCESSALL_H

#include <string>
#include <vector>

#include "paper.h"
using namespace std;

vector<paper>* process_all();
void saveToFile(vector<paper>* papersList, vector<string> txtList);
vector<paper>* readFromFile();

#endif // PROCESSALL_H
