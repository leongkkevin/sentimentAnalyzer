//
// Created by Kevin Leong on 8/31/20.
//

#include "DSString.h"

DSString::DSString() {

    this->size = 0;
    this->capacity = this->size+1;
    this-> data = new char[this->capacity];
    data[capacity - 1] = '\0';
}

DSString::DSString(const char *newData) {
    this->size = createLength(newData);
    this->capacity = this->size + 1;
    this->data = new char[this->capacity];
    for(int i = 0; i < this->capacity; i++){
        this->data[i] = newData[i];
    }

    data[capacity - 1] = '\0';
}

DSString::DSString(const DSString &copyString) {
    this->size = copyString.size;
    this->capacity = copyString.capacity;
    this->data = new char[this->capacity];
    for(int i = 0; i < this->capacity; i++){
        this->data[i] = copyString.data[i];
    }
    data[capacity - 1] = '\0';
}

DSString::~DSString() {
    delete[] data;
}

//Assorted Functions

void DSString::resize(int newCapacity){
    //copy the data from initial data
    char temp[capacity];
    for(int i = 0; i < capacity; i++){
        temp[i] = data[i];
    }

    //delete old data
    delete this->data;

    //new data with new capacity;
    this->data = new char[newCapacity + 1];

    //set the new data with temp copy
    for(int i = 0; i < this->size; i++){
        this->data[i] = temp[i];
    }

    //set a new capacity
    this->capacity = newCapacity + 1;
}

int DSString::createLength(const char *newData){
    int wordLength = strlen(newData);;
//    while(newData[wordLength] != '\0'){
//        wordLength++;
//    }
    return wordLength;
}

int DSString::getLength() {
    return this->size;
}
int DSString::getCap() {
    return this->capacity;
}

void DSString::setInfo(){
    this->size = createLength(this->data);
    this->capacity = this->size + 1;
}

void DSString::append(const DSString &addData){

    strcat(this->data, addData.data);
    //resize if necessary
    if(addData.size + this->size > this-> capacity){
        resize(addData.size + this->size);
    }

    //copy data in data's data
    int j = 0;
    for(int i = this->size; i < this->capacity; ++i) {
        this->data[i] = addData.data[j];
        ++j;
    }

    //change size
    this->size = this->capacity - 1;
}

char *DSString::getData() {
    return this->data;
}


DSString DSString::substring(int start, int numChars) {

    char *subChars = new char[numChars + 1];
//    char subChars[numChars + 1];

    int j = 0;
    for(int i = start; i < numChars + start; ++i){
        subChars[j] = this->getData()[i];
        j++;
    }

    DSString sub(subChars);

    return sub;
}

char *DSString::c_str() {
    return this->data;
}

//Overloaded Operators

DSString &DSString::operator=(const char *newData) {
    int wordLength = createLength(newData);

    //set capacity
    this->capacity = this->size + 1;

    //resize if necessary
    if(wordLength > capacity){
        resize(wordLength);
    }

    //recreate data
    this-> data = new char[wordLength];

    //set new size
    this->size = wordLength;

    //copy data into this data
    for(int i = 0; i < this->capacity; i++){
        this->data[i] = newData[i];
    }

    return *this;
}

DSString &DSString::operator=(const DSString &newString) {
    char * newData = newString.data;
//    int wordLength = createLength(newData);

    //set new size
    this->size = newString.size;
    //set capacity
    this->capacity = this->size + 1;

    //resize if necessary
    if(newString.size > capacity){
        resize(newString.size);
    }

    //recreate data
    this-> data = new char[newString.size];

    //copy data into this data
    for(int i = 0; i < this->capacity; i++){
        this->data[i] = newData[i];
    }
    return *this;
}

DSString DSString::operator+(const DSString &addString) {
    DSString copy = *this;
    copy.size = this->getLength();
    copy.capacity = this->getCap();

    //resize if necessary
    if(addString.size + copy.getLength() > copy.getCap()){
        copy.resize(addString.size + copy.getLength());
    }

    //copy data in data's data
    int j = 0;
    for(int i = copy.getLength(); i < copy.getCap(); ++i) {
        copy.data[i] = addString.data[j];
        copy.size++;
        ++j;
    }

    //get rid of null terminator
    copy.size--;
    return copy;
}

std::ostream &operator<<(std::ostream &out, const DSString &outString) {
        out << outString.data;
        return out;
}

bool DSString::operator==(const char *compString) {
    if(strcmp(this->data, compString) < 0 || strcmp(this->data, compString) > 0){
        return false;
    } else if (strcmp(this->data, compString) == 0){
        return true;
    }
}

bool DSString::operator==(const DSString &compString) {
    if(strcmp(this->data, compString.data) < 0 || strcmp(this->data, compString.data) > 0){
        return false;
    } else if (strcmp(this->data, compString.data) == 0){
        return true;
    }
}

bool DSString::operator>(const DSString &compString) {
    return strcmp(this->data, compString.data) > 0;
}

char &DSString::operator[](const int location) {

    return this->getData()[location];
}







