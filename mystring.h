#pragma once
#include <cinttypes>
#include <cstring>
#include <exception>
#include <iostream>

class MyString {
public:
    MyString();
    MyString(const char* array);
    MyString(const MyString& array);
    ~MyString();
    MyString& operator=(const MyString& other);
    MyString& operator=(const char* other);
    const char& operator[](uint32_t i) const;
    char& operator[](uint32_t i);
    const char* c_str() const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(const char other);

    // TODO: move constructor and move assignment operator

    uint32_t length() const;

private:
    struct StringData {
        char* data_;
        uint32_t length_;
        uint32_t count_;
        StringData();
        StringData(const char* array);
        ~StringData();
        StringData(StringData& other) = delete;
    };

    StringData* string;
    void release();
};

MyString operator+(const MyString& lhs, const MyString& rhs);
MyString operator+(const MyString& lhs, char rhs);
MyString operator+(char lhs, const MyString& rhs);
std::ostream& operator<<(std::ostream& os, const MyString& myString);

// TODO: operator>>
std::istream& operator>>(std::istream& is, MyString& myString);