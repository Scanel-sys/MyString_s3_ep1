#include "MyString.h"


/*
    TO DO:
        > refactor shitty suffix table maker
        > in find function casting (int) change to c++ casts 
        - iterator
            > insert
            
*/


// ==========================================================================
// =============================== public ===================================
// ========================================================================== 

MyString::MyString()
{
    this->SetTextLen(0);
    this->SetCapacity(BASIC_STRING_CAPACITY);
    this->StringAlloc();
}

MyString::MyString(std::initializer_list <char> list)
{
    this->SetSizeParameters(list.size());
    this->StringAlloc();
    unsigned int i = 0;
    for(auto element : list)
    {
        this->value_[i] = element;
        i++;
    }
}

MyString::MyString(const char *line) : MyString::MyString(line, strlen(line)){}

MyString::MyString(const char *line, unsigned int line_size)
{
    if(line)
    {
        this->SetSizeParameters(line_size);
        this->StringAlloc();
        this->CopyValue(line, line_size);
    }
}

MyString::MyString(std::string str) : MyString::MyString(str.c_str(), str.size()){}

MyString::MyString(unsigned int count, char c)
{
    this->SetSizeParameters(count);
    this->StringAlloc();
    for(unsigned int i = 0; i < this->size(); i++)
        this->value_[i] = c;
    this->value_[this->size()] = ENDLINE_SYMBOL;
}

MyString::MyString(const MyString &other) : MyString::MyString(other.c_str(), other.size()){}

MyString::~MyString()
{
    delete[] this->value_;
}


const char * MyString::c_str() const
{
    return this->value_;
}

const char * MyString::data() const
{
    return this->c_str();
}

unsigned int MyString::size() const
{
    return this->text_len_;
}

unsigned int MyString::length() const
{
    return this->size();
}

bool MyString::empty() const
{
    return this->size() == 0;
}

unsigned int MyString::capacity() const
{
    return this->capacity_;
}

void MyString::clear()
{
    this->value_[0] = ENDLINE_SYMBOL;
    this->SetTextLen(0);
}

void MyString::SetZeroes()
{
    for(unsigned int i = 0; i < this->capacity_; i++)
        this->value_[i] = ENDLINE_SYMBOL;
}

void MyString::shrink_to_fit()
{
    if(this->size() + 1 < this->capacity())
    {
        this->SetCapacity(this->size() + 1);
        this->Realloc(this->capacity());
    }
}


MyString MyString::operator+(const MyString& input_value)
{
    MyString output(*this);
    output.append(input_value);
    return output;
}

MyString MyString::operator+(const char* input_value)
{
    MyString output(*this);
    output.append(input_value);
    return output;
}

MyString MyString::operator+(const std::string input_value)
{
    MyString output(*this);
    output.append(input_value);
    return output;
}

MyString& MyString::operator+=(const char* input_value)
{
    this->append(input_value);
    return *this;
}

MyString& MyString::operator+=(const std::string input_value)
{
    this->append(input_value);
    return *this;
}

MyString& MyString::operator+=(const MyString& input_value)
{
    this->append(input_value);
    return *this;
}


MyString& MyString::operator=(const char* input_value)
{
    this->clear();
    this->append(input_value);
    return *this;
}

MyString& MyString::operator=(const std::string input_value)
{
    this->clear();
    this->append(input_value);
    return *this;
}

MyString& MyString::operator=(const char input_value)
{
    this->clear();
    this->append(1, input_value);
    return *this;
}

MyString& MyString::operator=(const MyString& input_value)
{
    this->clear();
    this->append(input_value);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    return out << s.c_str();
}

std::istream& operator>>(std::istream& in, MyString& s)
{
    bool if_skiws_set = std::cin.flags() & std::ios_base::skipws;
    char temp;
    unsigned int i = 0;

    in >> std::noskipws >> temp;
    while(!in.eof() && temp != '\n')
    {
        s.value_[i] = temp;
        in >> temp;
        i++;
        if(i == s.capacity())
        {
            s.SetTextLen(i);
            s.ExtendString();
        }
    }
    s.SetTextLen(i);
    s.value_[s.size()] = ENDLINE_SYMBOL;

    if(!if_skiws_set)
        in >> std::skipws;

    return in;
}

char& MyString::operator[](unsigned int index)
{
    if(index < this->size())
        return this->value_[index];
    return this->value_[this->size()];
}

bool operator>(MyString const& a, MyString const& b)
{
    if(a.size() > b.size())
        return true;
    if(a.size() < b.size())
        return false;
    
    for(unsigned int i = 0; i < a.size(); i++)
    {
        if(a.value_[i] < b.value_[i])
            return false;
        if(a.value_[i] > b.value_[i])
            return true;
    }
    return false;
}

bool operator<(MyString const& a, MyString const& b)
{
    if(a.size() < b.size())
        return true;
    if(a.size() > b.size())
        return false;
    
    for(unsigned int i = 0; i < a.size(); i++)
    {
        if(a.value_[i] > b.value_[i])
            return false;
        if(a.value_[i] < b.value_[i])
            return true;
    }
    
    return false;
}

bool operator>=(MyString const& a, MyString const& b)
{
    return !(a < b);
}

bool operator<=(MyString const& a, MyString const& b)
{
    return !(a > b);
}

bool operator!=(MyString const& a, MyString const& b)
{
    return !(a == b);
}

bool operator==(MyString const& a, MyString const& b)
{
    if(a.c_str() == b.c_str())
        return true;
    if(a.size() != b.size())
        return false;
    
    for(unsigned int i = 0; i < a.size(); i++)
        if(a.value_[i] != b.value_[i])
            return false;

    return true;
}


MyString& MyString::insert(unsigned int index, unsigned int count, char symbol)
{
    char * line_to_insert = new char[count + 1];
    for(unsigned int i = 0; i < count; i++)
        line_to_insert[i] = symbol;
    line_to_insert[count] = ENDLINE_SYMBOL;
    this->replace(index, 0, line_to_insert);
    delete[] line_to_insert;
    return *this;
}

MyString& MyString::insert(unsigned int index, const char * line)
{
    this->replace(index, 0, line);
    return *this;
}

MyString& MyString::insert(unsigned int index, const char * line, unsigned int count)
{
    char * line_to_insert = new char[count + 1];
    line_to_insert[0] = ENDLINE_SYMBOL;
    strncat(line_to_insert, line, count);
    this->replace(index, 0, line_to_insert);
    delete[] line_to_insert;
    return *this;
}

MyString& MyString::insert(unsigned int index, std::string str)
{
    this->replace(index, 0, str.c_str());
    return *this;
}

MyString& MyString::insert(unsigned int index, std::string str, unsigned int count)
{
    this->insert(index, str.c_str(), count);
    return *this;
}

MyString& MyString::erase(unsigned int index, unsigned int count)
{
    unsigned int stop_index;
    if(index + count < this->size())
        stop_index = index + count;
    else
        stop_index = this->size();

    if(index < stop_index)
    {
        this->value_[index] = ENDLINE_SYMBOL;
        this->SetTextLen(index - 1);
        this->append(&this->value_[stop_index]);
    }
    return *this;
}

MyString& MyString::append(unsigned int count, const char symbol)
{
    this->ExtendIfNotEnoughCapacity(count);

    for(unsigned int i = 0; i < count; i++)
        this->value_[this->size() + i] = symbol;
    this->SetTextLen(this->size() + count);
    return *this;
}

MyString& MyString::append(const char * line)
{
    int line_size = strlen(line);
    this->ExtendIfNotEnoughCapacity(line_size);

    this->CopyValue(line, line_size, this->size());
    this->SetTextLen(this->size() + line_size);
    return *this;
}

MyString& MyString::append(const char * line, unsigned int index, unsigned int count)
{
    unsigned int line_size = strlen(line);
    unsigned int chars_to_copy = 0;
    if(index < line_size)
    {
        if(index + count <= line_size)
            chars_to_copy = count;
        else
            chars_to_copy = line_size - index;
    }
    this->ExtendIfNotEnoughCapacity(chars_to_copy);

    for(unsigned int i = 0; i < chars_to_copy; i++)
        this->value_[this->size() + i] = line[index + i];
    this->SetTextLen(this->size() + chars_to_copy);
    return *this;
}

MyString& MyString::append(const std::string& str)
{
    return this->append(str.c_str(), 0, str.size());
}

MyString& MyString::append(const std::string& str, unsigned int index, unsigned int count)
{
    return this->append(str.c_str(), index, count);
}

MyString& MyString::append(const MyString& input_value)
{
    return this->append(input_value.c_str());
}

MyString& MyString::replace(unsigned int index, unsigned int count, const char * line)
{
    char * str_to_concat = NULL;
    unsigned int last_char_to_del = index + count;
    if(last_char_to_del < this->size())
    {
        unsigned int str_to_cat_size = this->size() - last_char_to_del;
        str_to_concat = new char[str_to_cat_size + 1];
        str_to_concat[0] = ENDLINE_SYMBOL;
        strncat(str_to_concat, &this->value_[last_char_to_del], str_to_cat_size);
    }

    unsigned int str_size = strlen(line);
    this->ExtendIfNotEnoughCapacity(str_size - count);
    this->value_[index] = ENDLINE_SYMBOL;
    strncat(this->value_, line, str_size);
    
    if(str_to_concat != NULL)
    {
        strcat(this->value_, str_to_concat);
        delete[] str_to_concat;    
    }
    this->SetTextLen(this->size() + strlen(line) - count);
    return *this;
}

MyString& MyString::replace(unsigned int index, unsigned int count, std::string str)
{
    this->replace(index, count, str.c_str());
    return *this;
}

MyString MyString::substr(unsigned int pos, unsigned int count)
{
    if(pos < this->size())
    {
        int chars_to_copy = count;

        if(count == 0 || pos + count >= this->size())
            chars_to_copy = this->size() - pos;

        MyString output(&this->value_[pos], chars_to_copy);
        return output;
    }

    MyString output;
    return output;
}


long long MyString::find(const std::string line_to_find, unsigned int index)
{
    return this->find(line_to_find.c_str(), index);
}

long long MyString::find(const char* line_to_find, unsigned int index)
{
    unsigned int line_size = strlen(line_to_find);
    
    if(!line_to_find || line_size > this->size() || line_size <= 0) 
        return -1;

    size_t * suffix_table = new size_t[line_size];

    for(size_t i = 0; i < UCHAR_MAX + 1; ++i)
        stop_table[i] = -1;
    
    /* In stop_table writing last occuring in line_to_find  */
    /* excluding last symbol */
    for(size_t i = 0; i < line_size - 1; ++i) 
        stop_table[(int)line_to_find[i]] = i;
    
    /* Simple variant. Can be faster */
    for(size_t i = 0; i < line_size; ++i)
    {
        size_t offset = line_size;
        while(offset && !suffix_match(line_to_find, line_size, offset, i))
            --offset;
        suffix_table[line_size - i - 1] = line_size - offset;
    }
    
    for(size_t this_pos = index; this_pos <= this->size() - line_size; )
    {
        size_t template_idx = line_size - 1;
        /* comparing MyString with line_to_find */
        while(line_to_find[template_idx] == this->value_[this_pos + template_idx])
        {
            if(template_idx == 0)
            {
                delete[] suffix_table;
                return this_pos;
            }
            --template_idx;
        }
        /*  not similar  */
        this_pos += max(suffix_table[template_idx], template_idx - stop_table[(int)this->value_[template_idx + this_pos]]);
        /*          ^^^         ^^^^               */
        /*         suffix     stop-symbol          */
    }
    delete[] suffix_table;
    return -1;
}


// ==========================================================================
// =============================== private ==================================
// ========================================================================== 

void MyString::StringAlloc()
{
    this->value_ = new char[this->capacity()];
}

void MyString::Realloc(unsigned int new_capacity)
{
    char * temp = new char[new_capacity];
    strncpy(temp, this->value_, this->size());
    delete[] this->value_;
    this->value_ = temp; 
}

void MyString::ExtendString()
{
    this->SetDoubledCapacity();
    this->Realloc(this->capacity());
}

void MyString::ExtendString(unsigned int text_size)
{
    this->SetDoubledTextlenCapacity(text_size);
    this->Realloc(this->capacity());
}

void MyString::ExtendIfNotEnoughCapacity(unsigned int line_to_add_size)
{
    if(this->capacity() - this->size() - 1 < line_to_add_size)
        this->ExtendString(this->capacity() - 1 + line_to_add_size);
}


void MyString::CopyValue(const char *line)
{
    this->CopyValue(line, strlen(line));
}

void MyString::CopyValue(const char *line, unsigned int line_size, unsigned int index)
{
    if(this->value_ && line)
    {
        unsigned int i = 0;
        for(; i < line_size; i++)
        {
            if(line[i] == ENDLINE_SYMBOL)
                break;
            this->value_[index + i] = line[i];
        }
        this->value_[index + i] = ENDLINE_SYMBOL;
    }
}

void MyString::SetSizeParameters(unsigned int new_len)
{
    this->SetDoubledTextlenCapacity(new_len);
    this->SetTextLen(new_len);
}

void MyString::SetTextLen(unsigned int new_len)
{
    this->text_len_ = new_len;
}

void MyString::SetCapacity(unsigned int new_capacity)
{
    this->capacity_ = new_capacity;
}

void MyString::SetDoubledCapacity()
{
    if(this->capacity() > 1)
        this->capacity_ = (this->capacity() - 1) * 2 + 1;
    else if(this->capacity() == 1)
        this->capacity_ = this->capacity() * 2 + 1;
}

void MyString::SetDoubledTextlenCapacity(unsigned int text_len)
{
    this->SetCapacity(text_len * 2 + 1);
}

size_t max(size_t a, size_t b)
{
    return a > b ? a : b; 
}

// for suffix table creating
int suffix_match(const char *line_to_find, size_t line_size, size_t offset, size_t suffixlen)
{
    if (suffixlen < offset)
        return line_to_find[line_size - suffixlen - 1] != line_to_find[offset - suffixlen - 1] &&
            memcmp(line_to_find + line_size - suffixlen, line_to_find + offset - suffixlen, suffixlen) == 0;

    return memcmp(line_to_find + line_size - offset, line_to_find, offset) == 0;
}