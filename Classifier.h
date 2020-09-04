//
// Created by Kevin Leong on 8/31/20.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "DSString.h"

using namespace std;

#ifndef S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
#define S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H

void fileParse(ifstream &fin, vector<string> &reviewArray) {

    //string reviewArray[10];
    for (int i = 0; i < 1000; ++i) { //PUT AMOUNT OF REVIEWS THERE
        string tempString;
        getline(fin, tempString, '\n');
        reviewArray.push_back(tempString);
        //cout << reviewArray[i] << endl;
    }

}

void arrayParse(vector<string> &reviewArray, vector<string> &ratingVector, vector<string> &commentVector){

    for(int i = 0; i < reviewArray.size(); i++) {
        vector<string> wordArray;

        stringstream ss;
        string sentenceString;
        sentenceString = reviewArray.at(i);
        ss << sentenceString;

        string tempString;

        while (getline(ss, tempString, ',')) {
            wordArray.push_back(tempString);
        }
        reverse(wordArray.begin(), wordArray.end());
        ratingVector.push_back(wordArray[0]);

        reverse(wordArray.begin(), wordArray.end());
        wordArray.pop_back();

        string fullComment;
        for (int i = 0; i < wordArray.size(); ++i) {
            fullComment = fullComment + wordArray.at(i);
        }
        commentVector.push_back(fullComment);
    }

}

//class Classifier {
//public:
//
//    };



#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
