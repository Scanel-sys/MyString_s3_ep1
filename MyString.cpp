#include "MyString.h"


MyString::MyString()
{
    this->value_ = 0;
    this->textSize = 0;
    this->capacity = 0;
}


MyString::MyString(const char *line)
{
    if(line)
    {
        this->textSize = strlen(line);
        this->capacity = this->textSize + 1;
        this->value_ = new char(this->capacity);
        strcpy(this->value_, line);
        std::cout << this->value_;
    }
}


MyString::MyString(MyString &other)
{
    this->value_ = new char(other.capacity);
    if(this->value_)
    {
        this->textSize = other.textSize;
        this->capacity = other.capacity;
        strcpy(this->value_, other.value_);
        std::cout << this->value_;
    }
}


MyString::~MyString()
{
    delete(this->value_);
}