#include "mystring.h"

MyString::StringData::StringData() : data_ {nullptr}, count_ {0} {}
MyString::StringData::StringData(const char* array) {
    data_ = new char[strlen(array) + 1];
    count_ = 1;
}

MyString::StringData::~StringData() {
    if(data_ && count_ == 1) {
        delete[] data_;
        return;
    }
    --count_;
}

MyString::MyString() : string {nullptr} {}
MyString::MyString(const char* array) {
    string = new MyString::StringData(array);
}

MyString& MyString::operator=(MyString& other) {
    string = other.string;
    ++string->count_;
}

const char& MyString::operator[](const uint32_t i) const {
    return string->data_[i];
}

char& MyString::operator[](const uint32_t i) {}

const char* MyString::c_str() const { return string->data_; }

MyString& MyString::operator=(const char* other) {
    if(string) {
        if(string->count_ == 1) {
            delete string;
        } else {
            --string->count_;
        }
    }
    string = new MyString::StringData(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, MyString& myString) {
    os << myString.c_str();
    return os;
}