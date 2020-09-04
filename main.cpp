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

    string topString;
    getline(fin, topString, '\n');
    cout << topString << endl;

    //string reviewArray[10];
    vector<string> reviewArray;
    vector<string> ratingVector;
    vector<string> commentVector;

    fileParse(fin, reviewArray);

    arrayParse(reviewArray, ratingVector, commentVector);

    vector<DSString> test;
    test.push_back("hello");
    DSString test2 = "cheese";
    test.push_back(test2);


    return 0;
}

