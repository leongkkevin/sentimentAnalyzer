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
    //cout << topString << endl;
}

void fileParse(ifstream &fin, vector<DSString> &reviewVector) {
    for (int i = 0; i < 50000; ++i) { //PUT AMOUNT OF REVIEWS THERE!!!!!!!!!!!!!!
        char tempChar[15000];
        fin.getline(tempChar, 15000, '\n');
        DSString tempString = tempChar;
        reviewVector.push_back(tempString);
    }

//    char tempChar[15000];
//    while(fin.getline(tempChar, 15000, '\n')){
//        DSString tempString = tempChar;
//        reviewVector.push_back(tempString);
//    }

}

void arrayParse(vector<DSString> &reviewVector, vector<DSString> &ratingVector, vector<DSString> &commentVector){

    for(int i = 0; i < reviewVector.size() - 0; i++) {
        vector<DSString> fullCommentVector;

        stringstream ss;
        DSString sentenceString = reviewVector.at(i);
        ss << sentenceString.getData();

        char tempCharArray[15000];

        while (ss.getline(tempCharArray, 15000, ',')){
            DSString tempString;
            tempString = tempCharArray;
            fullCommentVector.push_back(tempString);
        }
        //reverse(wordArray.begin(), wordArray.end());
        ratingVector.push_back(fullCommentVector[fullCommentVector.size() - 1]);

        //reverse(wordArray.begin(), wordArray.end());
        fullCommentVector.pop_back();

        //rebuild the comment
        char charComment[15000];
        for (int j = 0; j < fullCommentVector.size(); ++j) {
            strcat(charComment, fullCommentVector.at(j).getData());
        }

        DSString fullComment(charComment);
        commentVector.push_back(fullComment);

        fullCommentVector.clear();

        cout << i << endl;

    }

}

//class Classifier {
//public:
//
//    };



#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
