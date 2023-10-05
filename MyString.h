#include <string.h>
#include <iostream>
#include <initializer_list>

class MyString
{
public:
// __Constructors__
    MyString();
    MyString(std::initializer_list <char> list);
    MyString(const char *line);
    MyString(const char *line, unsigned int line_size);
    MyString(std::string str);
    MyString(unsigned int count, char c);
    MyString(const MyString &other);

    ~MyString();

// __Some funcs__
    const char *c_str() const;
    const char *data() const;
    const unsigned int size() const;
    const unsigned int length() const;
    const bool empty() const;
    const unsigned int capacity() const;
    void clear();

// __Changing_memory_amount__
    void shrink_to_fit();
    void Realloc(unsigned int new_capacity);
    void ExtendAndRealloc();
    void ExtendAndRealloc(unsigned int text_size);
    void ExtendCapacity2TimesThanNeed();
    void ExtendCapacity2TimesThanNeed(unsigned int text_size);

    void ExtendIfTiny(unsigned int concat_line_size);

// __Operators__
    MyString operator+(const MyString& input_value);
    MyString operator+(const char* input_value);
    MyString operator+(const std::string input_value);
    MyString& operator+=(const char* input_value);
    MyString& operator+=(const std::string input_value);
    MyString& operator=(const char* input_value);
    MyString& operator=(const std::string input_value);
    MyString& operator=(const char input_value);

    friend std::ostream& operator<<(std::ostream& out, const MyString& s);
    friend std::istream& operator>>(std::istream& in, MyString& s);
    char& operator[](unsigned int index);
    friend bool operator>(MyString const& a, MyString const& b);
    friend bool operator<(MyString const& a, MyString const& b);
    friend bool operator>=(MyString const& a, MyString const& b);
    friend bool operator<=(MyString const& a, MyString const& b);
    friend bool operator!=(MyString const& a, MyString const& b);
    friend bool operator==(MyString const& a, MyString const& b);

// __Insert__
    void insert(unsigned int index, unsigned int count, char symbol);
    void insert(unsigned int index, const char * line);
    void insert(unsigned int index, const char * line, unsigned int count);
    void insert(unsigned int index, std::string str);
    void insert(unsigned int index, std::string str, unsigned int count);

// __Erase__
    void erase(unsigned int index, unsigned int count);

// __Append__
    void append(unsigned int count, const char symbol);
    void append(const char * line);
    void append(const char * line, unsigned int index, unsigned int count);
    void append(const std::string& str);
    void append(const std::string& str, unsigned int index, unsigned int count);
    void append(const MyString& input_value);

// __Replace__
    void replace(unsigned int index, unsigned int count, const char * line);
    void replace(unsigned int index, unsigned int count, std::string str);

// __Substr__
    MyString substr(unsigned int pos, unsigned int count = 0);

private:
    char * value_;
    unsigned int text_len_;
    unsigned int capacity_;

// __Allocators__
    void AllocMemForValue();
    void AllocAndCopyValue(const char *line);
    void AllocAndCopyValue(const char *line, unsigned int line_size);

// __Setters__   
    void SetZeroLenCapacityPointer();
    void SetTextLenWithCapacity(unsigned int new_len);
    void SetTextLen(unsigned int new_len);
    void SetCapacity(unsigned int new_capacity);
    void SetExtendedCapacity(unsigned int text_len);
    void SetZeroes();
};