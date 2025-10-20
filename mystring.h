#pragma once
#include <cinttypes>
#include <cstring>

struct StringData {
    char* data_;
    uint32_t count_;
    StringData();
    StringData(const char* array);
    ~StringData();
    StringData(StringData& other) = delete;
};

class MyString {
public:
    MyString();
    MyString(const char* array);
    MyString& operator=(MyString& other);
    const char& operator[](uint32_t i) const;
    char& operator[](uint32_t i);

private:
    StringData* string;
};
