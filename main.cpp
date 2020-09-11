//Kevin Leong 47970316

#include <iostream>

#include "Classifier.h"

using namespace std;


int main(int argc, char* argv[]) {

    ifstream fin;
    fin.open("../IMDB.csv");

    //gets header
    getTop(fin);

    vector<DSString> reviewVector;
    vector<DSString> ratingVector;
    vector<DSString> commentVector;

    fileParse(fin, reviewVector);

    arrayParse(reviewVector, ratingVector, commentVector);

    vector<DSString> positiveComments;
    vector<DSString> negativeComments;
    classifyComments(ratingVector, commentVector, positiveComments, negativeComments);

    vector<DSString> positiveWordVector;
    vector<DSString> negativeWordVector;
    generateWordBank(positiveComments, positiveWordVector);
    generateWordBank(negativeComments, negativeWordVector);

    return 0;
}

