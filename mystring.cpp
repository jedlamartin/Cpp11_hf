#include "mystring.h"

StringData::StringData() : data_ {nullptr}, count_ {0} {}
StringData::StringData(const char* array) {
    data_ = new char[strlen(array) + 1];
    count_ = 1;
}
StringData::~StringData() {
    if(data_) {
        delete[] data_;
    }
}

MyString::MyString() : string {nullptr} {}
MyString::MyString(const char* array) {
    string = new StringData(array);
}
MyString& MyString::operator=(MyString& other) {}
const char& MyString::operator[](const uint32_t i) const {}
char& MyString::operator[](const uint32_t i) {}