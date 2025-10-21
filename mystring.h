#pragma once
#include <cinttypes>
#include <cstring>
#include <iostream>

class MyString {
public:
    MyString();
    MyString(const char* array);
    MyString& operator=(MyString& other);
    MyString& operator=(const char* other);
    const char& operator[](uint32_t i) const;
    char& operator[](uint32_t i);
    const char* c_str() const;

private:
    struct StringData {
        char* data_;
        uint32_t count_;
        StringData();
        StringData(const char* array);
        ~StringData();
        StringData(StringData& other) = delete;
    };

    StringData* string;
};

std::ostream& operator<<(std::ostream& os, MyString& myString);