#include "mystring.h"

MyString::MyString() : string {new StringData()} {}

MyString::MyString(const char* array) : string {new StringData {array}} {}

MyString::MyString(const MyString& myString) {
    string = myString.string;
    ++string->count_;
}

MyString::MyString(MyString&& other) noexcept {
    string = other.string;
    other.string = nullptr;
}

MyString::~MyString() { release(); }

MyString& MyString::operator=(const MyString& other) {
    if(this != &other) {
        release();
        string = other.string;
        ++string->count_;
    }
    return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if(this != &other) {
        release();

        string = other.string;
        other.string = nullptr;
    }
    return *this;
}

MyString& MyString::operator=(const char* other) {
    release();

    string = new MyString::StringData(other);
    return *this;
}

const char& MyString::operator[](const uint32_t i) const {
    if(i >= string->length_) {
        throw std::out_of_range("Out of bound");
    }
    return string->data_[i];
}

char& MyString::operator[](const uint32_t i) {
    if(i >= string->length_) {
        throw std::out_of_range("Out of bound");
    }
    if(string->count_ > 1) {
        StringData* new_data = new StringData(string->data_);
        release();
        string = new_data;
    }
    return string->data_[i];
}

const char* MyString::c_str() const { return string->data_; }

MyString& MyString::operator+=(const MyString& other) {
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

MyString& MyString::operator+=(const char other) {
    uint32_t newLength = string->length_ + 1;
    char* newArray = new char[newLength + 1];
    strcpy(newArray, string->data_);
    newArray[newLength - 1] = other;
    newArray[newLength] = '\0';
    StringData* newStringData = new StringData(newArray);
    delete[] newArray;

    release();
    string = newStringData;
    return *this;
}

uint32_t MyString::length() const { return string->length_; }

MyString::StringData::StringData() :
    data_ {new char[1]}, length_ {0}, count_ {1} {
    data_[0] = '\0';
}

MyString::StringData::StringData(const char* array) {
    length_ = strlen(array);
    data_ = new char[length_ + 1];
    strcpy(data_, array);
    count_ = 1;
}

MyString::StringData::~StringData() {
    if(data_) {
        delete[] data_;
    }
}

void MyString::release() {
    if(string) {
        if(--string->count_ == 0) {
            delete string;
            string = nullptr;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const MyString& myString) {
    os << myString.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& myString) {
    size_t size = 1024;
    char* input = new char[size];
    size_t index = 0;
    int c;
    while((c = is.get()) && !isspace(c)) {
        if(index == size - 1) {
            size *= 2;
            char* tmp = new char[size];
            strncpy(tmp, input, index);
            delete[] input;
            input = tmp;
        }
        input[index++] = c;
    }
    input[index] = '\0';
    myString = input;
    return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString result = lhs;
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, char rhs) {
    MyString result = lhs;
    result += rhs;
    return result;
}

MyString operator+(char lhs, const MyString& rhs) {
    char lhs_s[2];
    lhs_s[0] = lhs;
    lhs_s[1] = '\0';
    MyString result = lhs_s;
    result += rhs;
    return result;
}
