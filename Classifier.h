//
// Created by Kevin Leong on 8/31/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

#include "DSString.h"

using namespace std;

#ifndef S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
#define S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H

//gets the first line of the document being read in
void getTop(ifstream &fin){
    char tempString[160];
    fin.getline(tempString, 160, '\n');
    DSString headerString(tempString);
}

//parses the file into individual reviews
void fileParse(ifstream &fin, vector<DSString> &reviewVector, int size) {
    for (int i = 0; i < size; ++i) {
        char bufferChar[15000];
        fin.getline(bufferChar, 15000, '\n');
        DSString tempString = bufferChar;
        reviewVector.push_back(tempString);
    }

}

//parses each review and seperates them into ratings (positive or negative) and the comment associated
void seperateReview(vector<DSString> &reviewVector, vector<DSString> &ratingVector, vector<DSString> &commentVector){

    for(int i = 0; i < reviewVector.size(); i++) {

        stringstream ss;
        //DSString sentenceString = reviewVector.at(i);
        DSString sentenceString(reviewVector.at(i));
        ss << sentenceString.getData();

        vector<DSString> fullCommentVector;

        //for each line, delimit by comma and push it into a vector
        char *tempCharArray = new char[15000];
        while (ss.getline(tempCharArray, 15000, ',')){
            DSString tempString(tempCharArray);
            fullCommentVector.push_back(tempString);
        }

        //push the last value (assumed to be + or -) into the rating vector
        ratingVector.push_back(fullCommentVector[fullCommentVector.size() - 1]);

        //remove the rating
        fullCommentVector.pop_back();

        //rebuild the comment
        DSString fullComment = reviewVector.at(i).substring(0, reviewVector.at(i).getLength() - 9);
        commentVector.push_back(fullComment);

        //clear the vector
        fullCommentVector.clear();

    }
}

//classifies the comments into a positive and negative vector
void classifyComments(vector<DSString> &ratingVector, vector<DSString> &commentVector, vector<DSString> &positiveComments, vector<DSString> &negativeComments){

    for(int i = 0; i < ratingVector.size(); ++i){
        if(ratingVector.at(i) == "positive"){
            positiveComments.push_back(commentVector.at(i));
        } else if(ratingVector.at(i) == "negative"){
            negativeComments.push_back(commentVector.at(i));
        }
    }
}

//removes any non-alpha characters from words
DSString onlyAlpha(DSString tempString){
    vector<char> tempWordVect;

    //seperates the word into characters
    for(int i = 0; i < tempString.getLength(); ++i) {
        char checkAlpha = tempString[i];

        checkAlpha = tolower(checkAlpha);

        //checks to see if there's any non-alpha characters
        if(isalpha(checkAlpha)){
            tempWordVect.push_back(checkAlpha);
        }
    }

    //reconstructs the word and returns
    DSString nonAlphaWord;
    for(int i = 0; i < tempWordVect.size(); ++i){
        nonAlphaWord.append(tempWordVect.at(i));
    }

    return nonAlphaWord;

}

//reads in the neutral word file and puts them into a set
void generateNeutralWordBank(ifstream &inFile, set<DSString> &neutralDSSet){
    stringstream ss;
    char tempCharArray[150];

    DSString tempString;
    while (inFile.getline(tempCharArray, 100, '\n')) {
        tempString = tempCharArray;
        neutralDSSet.insert(tempString);
    }

}

//makes a word bank from the positive and negative reviews
void makeSpecWordBank(
        vector<DSString> &commentVector,
        const set<DSString>& neutralDSSet,
        vector<DSString> wordBankVector,
        map<DSString,int> &wordBank,
        int points){

    //creates a word bank using the positive and negative comments
    for(int i = 0; i < commentVector.size(); ++i){
        stringstream ss;
        DSString sentenceString = commentVector.at(i);
        ss << sentenceString.getData();

        char tempCharArray[150];
        while (ss.getline(tempCharArray, 150, ' ')){
            DSString tempString(tempCharArray);
            DSString onlyAlphaString = onlyAlpha(tempString);

            if((neutralDSSet.count(onlyAlphaString) == 0)){
                wordBankVector.push_back(onlyAlphaString);
            }
        }
    }

    //assigns each word points based off of its occurence in the bank
    for(int i = 0; i < wordBankVector.size(); ++i){

        if(wordBank.count(wordBankVector.at(i)) != 0){
            wordBank[wordBankVector.at(i)] = wordBank[wordBankVector.at(i)] + points;
        } else {
            wordBank[wordBankVector.at(i)] = points;
        }
    }
}

void generateWordBank(
        ifstream &inFile,
        vector<DSString> &positiveCommentVector,
        vector<DSString> &negativeCommentVector,
        vector<DSString> &wordBankVector,
        map<DSString, int> &wordBank){

    set<DSString> neutralDSSet;
    generateNeutralWordBank(inFile, neutralDSSet);

    //make a word bank based off of the positive and negative comments
    makeSpecWordBank(positiveCommentVector, neutralDSSet, wordBankVector, wordBank, 1);
    makeSpecWordBank(negativeCommentVector, neutralDSSet, wordBankVector, wordBank, -1);
}

//uses the word bank to assign each test comment with a point value
void analyzeSentiment(vector<DSString> &testCommentVector, vector<DSString> &predictedRatingVector, map<DSString,int> &wordBank){

    for(int i = 0; i < testCommentVector.size(); ++i){
        int totalCommentPoint = 0;

        DSString sentenceString = testCommentVector.at(i);
        stringstream ss;
        ss << sentenceString;

        //Parse each test comment into individual words
        char tempCharWordArray[15000];
        while (ss.getline(tempCharWordArray, 15000, ' ')){
            DSString tempString(tempCharWordArray);

            //convert them only to alpha characters
            DSString onlyAlphaString = onlyAlpha(tempString);

            //add points to comment's point counter if the word was found in the word bank
            if(wordBank.count(onlyAlphaString) != 0){
                totalCommentPoint += wordBank[onlyAlphaString];
            }
        }

        //assigns a positive or negative value to the comment
        if(totalCommentPoint > 0){
            predictedRatingVector.push_back(DSString("positive"));
        } else if(totalCommentPoint < 0){
            predictedRatingVector.push_back(DSString("negative"));
        }

    }

}

//returns the accuracy of the classifier
float findAccuracy(vector<DSString> testRatingVector, vector<DSString> predictedRatingVector, vector<int> &wrongReviewNumbers){
    float correct = 0;

    //compares the predicted ratings to the test ratings and totals how many are correct
    for(int i = 0; i < predictedRatingVector.size(); ++i){
        if(testRatingVector.at(i) == predictedRatingVector.at(i)){
            correct++;
        } else {
            //adds the value of the incorrect line to the vector
            wrongReviewNumbers.push_back(40000 + i);
        }
    }

    //return the percentage
    return correct/testRatingVector.size();
}

//classifies test and outputs the answer into the output file
void classifyTestComments(ifstream &fin, map<DSString,int> &wordBank){
    //parse each test review into individual reviews
    vector<DSString> testReviewVector;
    fileParse(fin, testReviewVector, 10000);

    //seperate each test review into the ratting and the comment
    vector<DSString> testRatingVector;
    vector<DSString> testCommentVector;
    vector<DSString> predictedRatingVector;
    seperateReview(testReviewVector, testRatingVector, testCommentVector);

    //find a positive or negative value for each review
    analyzeSentiment(testCommentVector, predictedRatingVector, wordBank);

    //find accuracy
    vector<int> wrongReviewNumbers;
    float accuracy = findAccuracy(testRatingVector, predictedRatingVector, wrongReviewNumbers);

    //outputs the percent accuracy and wrong review sentiment locations to output file
    ofstream outFile("output01.txt");
    outFile << accuracy << endl;
    for(int i = 0; i < wrongReviewNumbers.size(); ++i){
        outFile << wrongReviewNumbers.at(i) << endl;
    }
}


//runs the program
void run(ifstream &fin, ifstream &inFile){

    //gets header
    getTop(fin);

    vector<DSString> reviewVector;
    vector<DSString> ratingVector;
    vector<DSString> commentVector;

    fileParse(fin, reviewVector, 40000);

    seperateReview(reviewVector, ratingVector, commentVector);

    vector<DSString> positiveComments;
    vector<DSString> negativeComments;
    classifyComments(ratingVector, commentVector, positiveComments, negativeComments);

    getTop(inFile);
    vector<DSString> wordBankVector;
    map<DSString, int> wordBank;
    generateWordBank(inFile, positiveComments, negativeComments, wordBankVector, wordBank);

    classifyTestComments(fin, wordBank);

}




#endif //S20_PA01_SENTIMENTANALYSIS_CLASSIFIER_H
