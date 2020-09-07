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

void getTop(ifstream &fin){
    DSString topString;
    fin.getline(topString.getData(), 200000);
    //getline(fin, topString, '\n');
    cout << topString << endl;
}

void fileParse(ifstream &fin, vector<DSString> &reviewArray) {
    for (int i = 0; i < 50000; ++i) { //PUT AMOUNT OF REVIEWS THERE!!!!!!!!!!!!!!
        char tempChar[15000];
        fin.getline(tempChar, 15000, '\n');
        DSString tempString = tempChar;
        reviewArray.push_back(tempString);
    }

//    char tempChar[15000];
//    while(fin.getline(tempChar, 15000, '\n')){
//        DSString tempString = tempChar;
//        reviewArray.push_back(tempString);
//    }

}

void arrayParse(vector<DSString> &reviewArray, vector<DSString> &ratingVector, vector<DSString> &commentVector){

    for(int i = 0; i < reviewArray.size() - 0; i++) {
        vector<DSString> wordArray;

        stringstream ss;
        DSString sentenceString = reviewArray.at(i);
        ss << sentenceString.getData();

        char tempChar[15000];

        while (ss.getline(tempChar, 15000, ',')){
            DSString tempString;
            tempString = tempChar;
            wordArray.push_back(tempString);
        }
        //reverse(wordArray.begin(), wordArray.end());
        ratingVector.push_back(wordArray[wordArray.size() - 1]);

        //reverse(wordArray.begin(), wordArray.end());
        wordArray.pop_back();

        //rebuild the comment
        char charComment[15000];
        for (int j = 0; j < wordArray.size(); ++j) {
            strcat(charComment, wordArray.at(j).getData());
        }

        DSString fullComment(charComment);
        commentVector.push_back(fullComment);

        wordArray.clear();

        cout << i << endl;

    }

}

//class Classifier {
//public:
//
//    };



#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
