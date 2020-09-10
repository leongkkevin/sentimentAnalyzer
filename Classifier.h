//
// Created by Kevin Leong on 8/31/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "DSString.h"

using namespace std;

#ifndef S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
#define S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H

void checkDuplicate(vector<DSString> &vector, DSString dsString);

void getTop(ifstream &fin){
    DSString headerString;
    fin.getline(headerString.getData(), 2000);
}

void fileParse(ifstream &fin, vector<DSString> &reviewVector) {
    for (int i = 0; i < 40000; ++i) {
        char bufferChar[15000];
        fin.getline(bufferChar, 15000, '\n');
        DSString tempString = bufferChar;
        reviewVector.push_back(tempString);
    }

//parse from the file and seperate each review
//    char bufferChar[15000];
//    while(fin.getline(bufferChar, 15000, '\n')){
//        DSString tempString = bufferChar;
//        reviewVector.push_back(tempString);
//    }

}

void arrayParse(vector<DSString> &reviewVector, vector<DSString> &ratingVector, vector<DSString> &commentVector){

    for(int i = 0; i < reviewVector.size() - 0; i++) {

        stringstream ss;
        DSString sentenceString = reviewVector.at(i);
        ss << sentenceString.getData();

        vector<DSString> fullCommentVector;

        //for each line, delimit by comma and push it into a vector
        char tempCharArray[15000];
        while (ss.getline(tempCharArray, 15000, ',')){
            DSString tempString;
            tempString = tempCharArray;
            fullCommentVector.push_back(tempString);
        }

        //push the last value (assumed to be + or -) into the rating vector
        ratingVector.push_back(fullCommentVector[fullCommentVector.size() - 1]);

        //remove the rating
        fullCommentVector.pop_back();

        //rebuild the comment
//        char charComment[15000];
        char *charComment = new char[15000];

        for (int j = 0; j < fullCommentVector.size(); ++j) {
            strcat(charComment, fullCommentVector.at(j).getData());
        }

        //push the entire comment into comment vector
        DSString fullComment(charComment);
        commentVector.push_back(fullComment);

        //delete the vector
        fullCommentVector.clear();

    }
}

void classifyComments(vector<DSString> &ratingVector, vector<DSString> &commentVector, vector<DSString> &positiveComments, vector<DSString> &negativeComments){

    for(int i = 0; i < ratingVector.size(); ++i){
        if(ratingVector.at(i) == "positive"){
            positiveComments.push_back(commentVector.at(i));
        } else if(ratingVector.at(i) == "negative"){
            negativeComments.push_back(commentVector.at(i));
        }
    }
}

DSString onlyAlpha(DSString tempString){
    vector<char> tempWordVect;
    for(int i = 0; i < tempString.getLength(); ++i) {
        char checkAlpha = tempString.getData()[i];

        checkAlpha = tolower(checkAlpha);

        if(isalpha(checkAlpha)){
            tempWordVect.push_back(checkAlpha);
        }
    }

    char returnChar[tempWordVect.size()+1];
    for(int i = 0; i < tempWordVect.size(); ++i){
        returnChar[i] = tempWordVect.at(i);
    }

    DSString nonAlphaWord(returnChar);

    return nonAlphaWord;

}

bool checkNeutralWords(const DSString& checkString){

    bool returnBool = false;
    DSString neutralWord;

    while(inFile.getline(neutralWord.getData(), 100, '\n')){

        if(checkString == neutralWord){
            returnBool = true;
        }
    }

    return returnBool;

}

void generateWordBank(ifstream &fin, vector<DSString> &commentVector, vector<DSString> &wordBankVector){
    for(int i = 0; i < commentVector.size(); ++i){
        stringstream ss;
        DSString sentenceString = commentVector.at(i);
        ss << sentenceString.getData();

        char tempCharArray[15000];
        while (ss.getline(tempCharArray, 15000, ' ')){
            DSString tempString;
            tempString = tempCharArray;

            tempString = onlyAlpha(tempString);

            if(!checkNeutralWords(tempString)){
                wordBankVector.push_back(tempString);
            }
        }
    }
    
}
//class Classifier {
//public
//
//    };



#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
