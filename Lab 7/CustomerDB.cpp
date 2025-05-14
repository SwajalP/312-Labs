/*
 * Name: 
 * EID: 
 * PA7
 * Santacruz, Fall 2023
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->books = 0;
    this->dice = 0;
    this->figures = 0;
    this->towers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) {
    for (int i = 0; i < this->length; i++)if (data[i].name == name) return data[i];

    if (length == capacity) {
        Customer* c1 = new Customer[capacity * 2];
        
        for (int i = 0; i < length; i++) c1[i] = data[i];
        for (int i = length; i < capacity * 2; i++) c1[i] = Customer(UTString(""));

        delete[] data;
        data = c1;
        capacity *=2;
    }

    data[length].name = name;
    data[length].books = 0; data[length].dice = 0;
    data[length].figures = 0; data[length].towers = 0;

    return data[length++];
}

bool CustomerDB::isMember(UTString name) {
    for(int i = 0; i < this->length; i++) if(data[i].name == name) return true;
    return false;
}
