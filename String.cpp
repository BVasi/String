#include "String.hpp"

String::String()
{
    data_ = nullptr;
    size_ = 1;
}

String::String(const char* string)
{
    calculateSizeOfDataFromString(string);
    allocateMemoryForData();
    copyData(string);
}

String::String(const String& string)
{
    size_ = string.size_;
    allocateMemoryForData();
    copyData(string);
}

String::String(String&& string)
{
    size_ = std::move(string.size_);
    data_ = std::move(string.data_);
}

String::~String()
{
    delete[] data_;
}

String& String::operator=(const String& string)
{
    size_ = string.size_;
    allocateMemoryForData();
    copyData(string);

    return *this;
}

String& String::operator=(String&& string)
{
    size_ = std::move(string.size_);
    data_ = std::move(string.data_);

    return *this;
}

String String::operator+(const String& string)
{
    String newString;
    newString.size_ = size_ + string.size_ - NULL_CHARACTER_OFFSET;
    newString.allocateMemoryForData();

    for (int index = 0; index < size_ - NULL_CHARACTER_OFFSET; index++)
    {
        newString.data_[index] = data_[index];
    }

    for (int index = 0; index < string.size_; index++)
    {
        newString.data_[size_ + index - NULL_CHARACTER_OFFSET] = string.data_[index];
    }

    return newString;
}

void bufferCopy(char* oldBuffer, char* newBuffer, int sizeOfBuffer)
{
    for (int index = 0; index < sizeOfBuffer; index++)
    {
        newBuffer[index] = oldBuffer[index];
    }
}

String& String::operator+=(const String& string)
{
    int initialSize = size_;
    size_ = initialSize + string.size_ - NULL_CHARACTER_OFFSET;
    String temp;
    if (data_)
    {
        temp = std::move(*this);
    }
    allocateMemoryForData();
    if (temp.data_)
    {
        copyData(temp);
    }

    for (int index = 0; index < string.size_; index++)
    {
        data_[initialSize + index - NULL_CHARACTER_OFFSET] = string.data_[index];
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    os << string.data_;

    return os;
}

int String::compareSizeTo(const String& string)
{
    if (size_ < string.size_)
    {
        return SMALLER_THAN_OTHER;
    }
    if (size_ > string.size_)
    {
        return BIGGER_THAN_OTHER;
    }

    return SAME_AS_OTHER;
}

int String::compareTo(const String& string)
{
    int sizeRelativeToOther = compareSizeTo(string);
    if (sizeRelativeToOther != SAME_AS_OTHER)
    {
        return sizeRelativeToOther;
    }

    for (int index = 0; index < size_; index++)
    {
        if (data_[index] < string.data_[index])
        {
            return SMALLER_THAN_OTHER;
        } 
        if (data_[index] > string.data_[index])
        {
            return BIGGER_THAN_OTHER;
        }
    }

    return SAME_AS_OTHER;
}

bool String::operator==(const String& string)
{
    return (compareTo(string) == SAME_AS_OTHER);   
}

bool String::operator<(const String& string)
{
    return (compareTo(string) == SMALLER_THAN_OTHER);
}

bool String::operator>(const String& string)
{
    return (compareTo(string) == BIGGER_THAN_OTHER);
}

bool String::operator<=(const String& string)
{
    return (compareTo(string) <= SAME_AS_OTHER);
}

bool String::operator>=(const String& string)
{
    return (compareTo(string) >= SAME_AS_OTHER);
}

char* readAnySizeStream(std::istream& is)
{
    char character;
    int size = 0;
    int capacity = 1024;
    char* buffer = new char[capacity];

    while (is.get(character) && character != '\n')
    {
        if (size == capacity - NULL_CHARACTER_OFFSET)
        {
            capacity *= 2;
            char* newBuffer = new char[capacity];
            bufferCopy(buffer, newBuffer, size);
            delete[] buffer;
            buffer = newBuffer;
        }

        buffer[size] = character;
        size++;
        buffer[size] = '\0';
    }

    return buffer;
}

std::istream& operator>>(std::istream& is, String& string)
{
    char* buffer = readAnySizeStream(is);
    string.calculateSizeOfDataFromString(buffer);
    string.allocateMemoryForData();
    string.copyData(buffer);
    delete[] buffer;

    return is;
}

char& String::operator[](int index)
{
    return data_[index];
}

void String::allocateMemoryForData()
{
    data_ = new char[size_];
}

void String::copyData(const char* string)
{
    for (int index = 0; index < size_; index++)
    {
        data_[index] = string[index];
    }
}

void String::copyData(const String& string)
{
    for (int index = 0; index < size_; index++)
    {
        data_[index] = string.data_[index];
    }
}

void String::calculateSizeOfDataFromString(const char* string)
{
    int index = 0;
    while (string[index] != '\0')
    {
        index++;
    }
    size_ = index + NULL_CHARACTER_OFFSET;
}

int main()
{

    return 0;
}