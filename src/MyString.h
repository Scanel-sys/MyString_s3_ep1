#include <string.h>
#include <iostream>
#include <initializer_list>

class MyString
{
public:
    MyString();
    MyString(std::initializer_list <char> list);
    MyString(const char *line);
    MyString(const char *line, unsigned int line_size);
    MyString(std::string str);
    MyString(unsigned int count, char c);
    MyString(const MyString &other);

    ~MyString();

    const char *c_str() const;
    const char *data() const;
    unsigned int size() const;
    unsigned int length() const;
    bool empty() const;
    unsigned int capacity() const;
    void clear();

    void shrink_to_fit();
    void Realloc(unsigned int new_capacity);
    void ExtendAndRealloc();
    void ExtendAndRealloc(unsigned int text_size);
    void ExtendCapacity2TimesThanNeed();
    void ExtendCapacity2TimesThanNeed(unsigned int text_size);

    void ExtendIfTiny(unsigned int concat_line_size);

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

    void insert(unsigned int index, unsigned int count, char symbol);
    void insert(unsigned int index, const char * line);
    void insert(unsigned int index, const char * line, unsigned int count);
    void insert(unsigned int index, std::string str);
    void insert(unsigned int index, std::string str, unsigned int count);

    void erase(unsigned int index, unsigned int count);

    void append(unsigned int count, const char symbol);
    void append(const char * line);
    void append(const char * line, unsigned int index, unsigned int count);
    void append(const std::string& str);
    void append(const std::string& str, unsigned int index, unsigned int count);
    void append(const MyString& input_value);

    void replace(unsigned int index, unsigned int count, const char * line);
    void replace(unsigned int index, unsigned int count, std::string str);

    MyString substr(unsigned int pos, unsigned int count = 0);

    long long find(const std::string line_to_find, unsigned int index = 0);
    long long find(const char* line_to_find, unsigned int index = 0);

private:
    char * value_;
    unsigned int text_len_;
    unsigned int capacity_;
    size_t stop_table[UCHAR_MAX + 1];


    int suffix_match(const char *line_to_find, size_t line_size, size_t offset, size_t suffixlen) const;
    size_t max(size_t a, size_t b) const;


    void AllocMemForValue();
    void AllocAndCopyValue(const char *line);
    void AllocAndCopyValue(const char *line, unsigned int line_size);

    void SetZeroLenCapacityPointer();
    void SetTextLenWithCapacity(unsigned int new_len);
    void SetTextLen(unsigned int new_len);
    void SetCapacity(unsigned int new_capacity);
    void SetExtendedCapacity(unsigned int text_len);
    void SetZeroes();
};