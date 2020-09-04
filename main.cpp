//Kevin Leong 47970316

#include <iostream>

#include "Classifier.h"

using namespace std;


int main(int argc, char* argv[]) {
//    std::cout << "Hello, World!" << std::endl;
//    std::ofstream fout("output01.txt");
//    fout << "Hello world!" << std::endl;
//    fout.close();

    ifstream fin;
    fin.open("IMDB.csv");

    DSString topString;
    fin.getline(topString.getData(), 200000);
    //getline(fin, topString, '\n');
    cout << topString << endl;

    //string reviewArray[10];
    vector<DSString> reviewArray;
    vector<DSString> ratingVector;
    vector<DSString> commentVector;

    fileParse(fin, reviewArray);

    arrayParse(reviewArray, ratingVector, commentVector);


    return 0;
}

