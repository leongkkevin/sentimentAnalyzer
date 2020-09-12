//
// Created by Kevin Leong on 8/31/20.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_DSSTRING_H
#define S20_PA01_SENTIMENTANALYSIS_DSSTRING_H


#include <iostream>
#include <cstring>

class DSString{

private:

    int size;
    int capacity;
    char* data;



public:
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    DSString& operator= (const char*);
    DSString& operator= (const DSString&);
    DSString operator+ (const DSString&);
    bool operator== (const char*) const;
    bool operator== (const DSString&) const;
    bool operator> (const DSString&)  const;
    bool operator< (const DSString&)  const;
    char& operator[] (const int);
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    void resize(int newLength);
    int createLength(const char *newData);

    int getLength() const;
    int getCap();
    char* getData();

    void append(char addData);
    DSString substring(int start, int numChars);
    char* c_str();



};


#endif