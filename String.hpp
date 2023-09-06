#include <iostream>

const int NULL_CHARACTER_OFFSET = 1;
const int SMALLER_THAN_OTHER = -1;
const int SAME_AS_OTHER = 0;
const int BIGGER_THAN_OTHER = 1;

class String
{
public:
    String();
    String(const char* string);
    String(const String& string);
    String(String&& string);
    ~String();

    String& operator=(const String& string);
    String& operator=(String&& string);
    String operator+(const String& string);
    String& operator+=(const String& string);

    bool operator==(const String& string);
    bool operator<(const String& string);
    bool operator>(const String& string);
    bool operator<=(const String& string);
    bool operator>=(const String& string);

    char& operator[] (int index);

    friend std::ostream& operator<<(std::ostream& os, const String& string);
    friend std::istream& operator>>(std::istream& is, String& string);

    int compareTo(const String& string);
private:
    char* data_;
    int size_;

    void allocateMemoryForData();
    void copyData(const char* string);
    void copyData(const String& string);
    void calculateSizeOfDataFromString(const char* string);
    int compareSizeTo(const String& string);
};