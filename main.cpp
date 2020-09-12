//Kevin Leong 47970316
//../IMDB.csv ../neutralWords.txt

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


#include <iostream>

#include "Classifier.h"

#define TEST false
int runCatchTest(int argc, char* const argv[]){
    return Catch::Session().run(argc, argv);
}

using namespace std;


int main(int argc, char* argv[]) {

    if(TEST){
        return runCatchTest(argc, argv);
    }

    ifstream fin;
    fin.open(argv[1]);
    ifstream inFile;
    inFile.open(argv[2]);

    ofstream fout;
    fout.open(argv[3]);
    //runs the classifier
    run(fin, inFile, fout);


    return 0;
}

