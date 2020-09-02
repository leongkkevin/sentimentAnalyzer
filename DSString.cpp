//
// Created by Kevin Leong on 8/31/20.
//

#include "DSString.h"

DSString::DSString() {
    this->size = 0;
    this-> capacity = 10;
    this-> data = new char[capacity];
}

DSString::DSString(const char *) {

}

