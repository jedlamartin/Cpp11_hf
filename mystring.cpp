#include "mystring.h"

MyString::StringData::StringData() : data_ {nullptr}, count_ {0} {}

MyString::StringData::StringData(const char* array) {
    length_ = strlen(array);
    data_ = new char[length_ + 1];
    strcpy(data_, array);
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

MyString::MyString(const MyString& myString) {
    string = myString.string;
    ++string->count_;
}

MyString& MyString::operator=(MyString& other) {
    string = other.string;
    ++string->count_;
    return *this;
}

const char& MyString::operator[](const uint32_t i) const {
    return string->data_[i];
}

char& MyString::operator[](const uint32_t i) {
    release();
    string = new MyString::StringData(string->data_);
    return string->data_[i];
}

const char* MyString::c_str() const { return string->data_; }

MyString& MyString::operator=(const char* other) {
    if(string) {
        release();
    }
    string = new MyString::StringData(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& myString) {
    os << myString.c_str();
    return os;
}

void MyString::release() {
    if(string->count_ == 1) {
        delete string;
        return;
    }
    --string->count_;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    uint32_t newLength = string->length_ + other.string->length_;
    char* newArray = new char[newLength + 1];
    strcpy(newArray, string->data_);
    strcat(newArray, other.string->data_);
    StringData* newStringData = new StringData(newArray);
    delete[] newArray;

    release();
    string = newStringData;
    return *this;
}
MyString operator+(const MyString& lhs, char rhs) {
    uint32_t newLength = string->length_ + 1;
    char* newArray = new char[newLength + 1];
    strcpy(newArray, string->data_);
    newArray[newLength - 1] = rhs;
    newArray[newLength] = '\0';
    StringData* newStringData = new StringData(newArray);
    delete[] newArray;

    release();
    string = newStringData;
    return *this;
}
MyString& MyString::operator+=(const MyString& other);
MyString& MyString::operator+=(const char other);

uint32_t length() const;