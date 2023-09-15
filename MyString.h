#include <string.h>
#include <iostream>


class MyString
{
public:
    MyString();
    MyString(const char *line);
    MyString(MyString &other);

    ~MyString();

private:
    char * value_;
    unsigned int textSize;
    unsigned int capacity;
};