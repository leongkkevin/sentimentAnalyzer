//Kevin Leong 47970316

#include <iostream>

#include "Classifier.h"

using namespace std;


int main(int argc, char* argv[]) {


    ifstream fin;
    fin.open("IMDB.csv");

    getTop(fin);

    //string reviewArray[10];
    vector<DSString> reviewArray;
    vector<DSString> ratingVector;
    vector<DSString> commentVector;

    fileParse(fin, reviewArray);

    arrayParse(reviewArray, ratingVector, commentVector);


    return 0;
}

