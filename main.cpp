#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

using namespace std;

void traversePDF();
void PDFtoTxt(string pdf);

int main(){
    traversePDF();
    return 0;
}

void traversePDF() { // find all PDF and convert
    struct dirent *ptr;
    DIR *dir;
    dir = opendir("./");
    while((ptr=readdir(dir)) != NULL) {
        // Skip"." and ".."
        if(ptr->d_name[0] == '.')
            continue;

        string filename = ptr->d_name;
        string lowerFilename = filename;
        transform(lowerFilename.begin(), lowerFilename.end(), lowerFilename.begin(), ::tolower); // lowercase
        if (lowerFilename.substr(lowerFilename.size() - 4) == ".pdf") {
            PDFtoTxt(filename);
        }
    }
    closedir(dir);
    // TODO: 判断txt是否存在，是则不convert
}

void PDFtoTxt(string pdf) { // convert PDF to txt witl the same name using pdftotxt
    string command = "./pdftotext -nodiag " + pdf;
    system(command.data());
}
