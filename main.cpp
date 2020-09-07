//Kevin Leong 47970316

#include <iostream>

#include "Classifier.h"

using namespace std;


int main(int argc, char* argv[]) {


    ifstream fin;
    fin.open("IMDB.csv");

    getTop(fin);

    //string reviewVector[10];
    vector<DSString> reviewVector;
    vector<DSString> ratingVector;
    vector<DSString> commentVector;

    fileParse(fin, reviewVector);

    arrayParse(reviewVector, ratingVector, commentVector);


    return 0;
}

