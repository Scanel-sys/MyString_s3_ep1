#include "MyString.h"


/*
    TO DO:
        > refactor shitty suffix table maker
        > in find function casting (int) change to c++ casts 

*/

//public functions

MyString::MyString()
{
    this->value_ = 0;
    this->SetTextLen(0);
    this->SetCapacity(9);
    this->AllocMemForValue();
}

MyString::MyString(std::initializer_list <char> list)
{
    this->SetTextLenWithCapacity(list.size());
    this->AllocMemForValue();
    unsigned int i = 0;
    for(auto element : list)
    {
        this->value_[i] = element;
        i++;
    }
}

MyString::MyString(const char *line)
{
    if(line)
    {
        this->SetTextLenWithCapacity(strlen(line));
        this->AllocAndCopyValue(line);
    }
}

MyString::MyString(const char *line, unsigned int line_size)
{
    if(line)
    {
        this->SetTextLenWithCapacity(line_size);
        this->AllocAndCopyValue(line, line_size);
    }
}

MyString::MyString(std::string str)
{
    this->SetTextLenWithCapacity(str.size());
    this->AllocAndCopyValue(str.c_str());
}

MyString::MyString(unsigned int count, char c)
{
    this->SetTextLenWithCapacity(count);
    this->AllocMemForValue();
    for(unsigned int i = 0; i < this->text_len_; i++)
        this->value_[i] = c;
    this->value_[this->text_len_] = '\0';
}

MyString::MyString(const MyString &other)
{
    this->SetTextLenWithCapacity(other.text_len_);
    this->AllocAndCopyValue(other.c_str());
}

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
    if(this->text_len_ == 0)
        return true;
    return false;
}

unsigned int MyString::capacity() const
{
    return this->capacity_;
}

void MyString::clear()
{
    this->value_[0] = '\0';
    this->SetTextLen(0);
}


void MyString::shrink_to_fit()
{
    if(this->text_len_ + 1 < this->capacity_)
    {
        this->SetCapacity(this->text_len_ + 1);
        this->Realloc(this->capacity_);
    }
}

void MyString::Realloc(unsigned int new_capacity)
{
    char * temp = new char(new_capacity);
    strncpy(temp, this->value_, this->text_len_);
    delete this->value_;
    this->value_ = temp; 
}

void MyString::ExtendAndRealloc()
{
    this->ExtendCapacity2TimesThanNeed();
    this->Realloc(this->capacity_);
}

void MyString::ExtendAndRealloc(unsigned int text_size)
{
    this->ExtendCapacity2TimesThanNeed(text_size);
    this->Realloc(this->capacity_);
}

void MyString::ExtendCapacity2TimesThanNeed()
{
    this->capacity_ = (this->capacity_ - 1) * 2 + 1;
}

void MyString::ExtendCapacity2TimesThanNeed(unsigned int text_size)
{
    this->capacity_ = text_size * 2 + 1;
}

void MyString::ExtendIfTiny(unsigned int concat_line_size)
{
    if(this->capacity_ - this->text_len_ - 1 < concat_line_size)
        this->ExtendAndRealloc(this->capacity_ - 1 + concat_line_size);
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


std::ostream& operator<<(std::ostream& out, const MyString& s)
{
    return out << s.c_str();
}

std::istream& operator>>(std::istream& in, MyString& s)
{
    bool if_skiws_set = std::cin.flags() & std::ios_base::skipws;
    char temp = ' ';
    unsigned int i = 0;
    in >> std::noskipws >> temp;
    while(!isspace(temp))
    {
        if(i == s.capacity_)
            s.ExtendAndRealloc();
        
        s.value_[i] = temp;
        in >> temp;
        i++;
    }
    s.SetTextLen(i);
    s.value_[s.text_len_] = '\0';
    if(!if_skiws_set)
        in >> std::skipws;
    
    std::cout << "\n";
    for(unsigned int i = 0; i < s.size(); i++)
        std::cout << s.value_[i];
    std::cout << "from operatr >>\n\n";

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
    if(a.size() > b.size())
        return true;
    if(a.size() < b.size())
        return false;
    
    for(unsigned int i = 0; i < a.size(); i++)
        if(a.value_[i] < b.value_[i])
            return false;
    
    return true;
}

bool operator<=(MyString const& a, MyString const& b)
{
    if(a.size() < b.size())
        return true;
    if(a.size() > b.size())
        return false;
    
    for(unsigned int i = 0; i < a.size(); i++)
        if(a.value_[i] > b.value_[i])
            return false;
    
    return true;
}

bool operator!=(MyString const& a, MyString const& b)
{
    if(a.size() != b.size())
        return true;
    
    for(unsigned int i = 0; i < a.size(); i++)
        if(a.value_[i] != b.value_[i])
            return true;

    return false;
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


void MyString::insert(unsigned int index, unsigned int count, char symbol)
{
    char * line_to_insert = new char(count + 1);
    for(unsigned int i = 0; i < count; i++)
        line_to_insert[i] = symbol;
    line_to_insert[count] = '\0';
    this->replace(index, 0, line_to_insert);
    delete line_to_insert;
}

void MyString::insert(unsigned int index, const char * line)
{
    this->replace(index, 0, line);
}

void MyString::insert(unsigned int index, const char * line, unsigned int count)
{
    char * line_to_insert = new char(count + 1);
    line_to_insert[0] = '\0';
    strncat(line_to_insert, line, count);
    this->replace(index, 0, line_to_insert);
    delete line_to_insert;
}

void MyString::insert(unsigned int index, std::string str)
{
    this->replace(index, 0, str.c_str());
}

void MyString::insert(unsigned int index, std::string str, unsigned int count)
{
    this->insert(index, str.c_str(), count);
}


void MyString::erase(unsigned int index, unsigned int count)
{
    unsigned int stop_index;
    if(index + count < this->size())
        stop_index = index + count;
    else
        stop_index = this->size();

    if(index != stop_index)
    {
        this->value_[index] = '\0';
        strcat(this->value_, &this->value_[stop_index]);
    }
    this->SetTextLen(this->size() - count);
}


void MyString::append(unsigned int count, const char symbol)
{
    std::cout << symbol << '\n';
    this->ExtendIfTiny(count);

    for(unsigned int i = 0; i < count; i++)
        this->value_[this->text_len_ + i] = symbol;
    this->SetTextLen(this->size() + count);
}

void MyString::append(const char * line)
{
    int line_size = strlen(line);
    this->ExtendIfTiny(line_size);

    for(int i = 0; i < line_size; i++)
        this->value_[this->text_len_ + i] = line[i];
    this->SetTextLen(this->size() + line_size);
}

void MyString::append(const char * line, unsigned int index, unsigned int count)
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
    this->ExtendIfTiny(chars_to_copy);

    for(unsigned int i = 0; i < chars_to_copy; i++)
        this->value_[this->text_len_ + i] = line[index + i];
    this->SetTextLen(this->size() + chars_to_copy);
}

void MyString::append(const std::string& str)
{
    this->append(str.c_str(), 0, str.size());
}

void MyString::append(const std::string& str, unsigned int index, unsigned int count)
{
    this->append(str.c_str(), index, count);
}

void MyString::append(const MyString& input_value)
{
    this->append(input_value.c_str());
}


void MyString::replace(unsigned int index, unsigned int count, const char * line)
{
    char * str_to_concat = NULL;
    unsigned int last_char_to_del = index + count;
    if(last_char_to_del < this->size())
    {
        unsigned int str_to_cat_size = this->size() - last_char_to_del;
        str_to_concat = new char(str_to_cat_size + 1);
        str_to_concat[0] = '\0';
        strncat(str_to_concat, &this->value_[last_char_to_del], str_to_cat_size);
    }

    unsigned int str_size = strlen(line);
    this->ExtendIfTiny(str_size - count);
    this->value_[index] = '\0';
    strncat(this->value_, line, str_size);
    
    if(str_to_concat != NULL)
    {
        strcat(this->value_, str_to_concat);
        delete str_to_concat;    
    }
}

void MyString::replace(unsigned int index, unsigned int count, std::string str)
{
    this->replace(index, count, str.c_str());
}


MyString MyString::substr(unsigned int pos, unsigned int count)
{
    if(pos < this->size())
    {
        if(count == 0)
        {
            MyString output(&this->value_[pos]);
            return output;
        }

        int chars_to_copy = count;
        if(pos + count >= this->size())
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

    size_t * suffix_table = new size_t(line_size);

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
                delete suffix_table;
                return this_pos;
            }
            --template_idx;
        }
        /*  not similar  */
        this_pos += max(suffix_table[template_idx], template_idx - stop_table[(int)this->value_[template_idx + this_pos]]);
        /*          ^^^         ^^^^               */
        /*         suffix     stop-symbol          */
    }
    delete suffix_table;
    return -1;
}


// private functions

// for suffix table creating
int MyString::suffix_match(const char *line_to_find, size_t line_size, size_t offset, size_t suffixlen) const
{
    if (suffixlen < offset)
        return line_to_find[line_size - suffixlen - 1] != line_to_find[offset - suffixlen - 1] &&
            memcmp(line_to_find + line_size - suffixlen, line_to_find + offset - suffixlen, suffixlen) == 0;

    return memcmp(line_to_find + line_size - offset, line_to_find, offset) == 0;
}

size_t MyString::max(size_t a, size_t b) const
{
    return a > b ? a : b; 
}

void MyString::AllocMemForValue()
{
    this->value_ = new char(this->capacity_);
}

void MyString::AllocAndCopyValue(const char *line)
{
    this->AllocMemForValue();
    if(this->value_)
        strncpy(this->value_, line, this->text_len_);
}

void MyString::AllocAndCopyValue(const char *line, unsigned int line_size)
{
    this->AllocMemForValue();
    if(this->value_)
        strncpy(this->value_, line, line_size);
}


void MyString::SetZeroLenCapacityPointer()
{
    this->capacity_ = 0;
    this->text_len_ = 0;
    this->value_ = 0;
}

void MyString::SetTextLenWithCapacity(unsigned int new_len)
{
    this->SetExtendedCapacity(new_len);
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

void MyString::SetExtendedCapacity(unsigned int text_len)
{
    this->SetCapacity(text_len * 2 + 1);
}

void MyString::SetZeroes()
{
    for(unsigned int i = 0; i < this->capacity_; i++)
        this->value_[i] = '\0';
}
