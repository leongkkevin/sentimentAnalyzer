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

void fileParse(ifstream &fin, vector<DSString> &reviewArray) {
    for (int i = 0; i < 20000; ++i) { //PUT AMOUNT OF REVIEWS THERE!!!!!!!!!!!!!!
        char tempChar[15000];
        fin.getline(tempChar, 15000, '\n');
        //getline(fin, tempString, '\n');
        DSString tempString = tempChar;
        reviewArray.push_back(tempString);
    }

}

void arrayParse(vector<DSString> &reviewArray, vector<DSString> &ratingVector, vector<DSString> &commentVector){

    for(int i = 0; i < reviewArray.size() - 0; i++) {
        vector<DSString> wordArray;

        stringstream ss;
        DSString sentenceString;
        sentenceString = reviewArray.at(i);
        ss << sentenceString.getData();

        //DSString tempString;
        char tempChar[15000];

        while (ss.getline(tempChar, 15000, ',')){ //getline(ss, tempString, ',')) {
            DSString tempString;
            tempString = tempChar;
            wordArray.push_back(tempString);
        }
        //reverse(wordArray.begin(), wordArray.end());
        ratingVector.push_back(wordArray[wordArray.size() - 1]);

        //reverse(wordArray.begin(), wordArray.end());
        wordArray.pop_back();

        char charComment[15000];
        for (int j = 0; j < wordArray.size(); ++j) {
            strcat(charComment, wordArray.at(j).getData());
            //charComment = charComment + wordArray.at(i);
            //fullComment = fullComment + wordArray.at(i);
        }
        DSString fullComment(charComment);
        commentVector.push_back(fullComment);

        wordArray.clear();

    }

}

//class Classifier {
//public:
//
//    };



#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
