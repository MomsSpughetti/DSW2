#include "wet2util.h"


class permutation_modified
{

public:
    permutation_modified() : permutation(permutation_t::neutral()){}
    permutation_modified(const permutation_t& permutation) : permutation(permutation){}
    friend permutation_modified operator+(const permutation_modified& obj1, const permutation_modified& obj2);
    permutation_modified& operator+=(const permutation_modified& obj);
    friend permutation_modified operator-(const permutation_modified& obj1, const permutation_modified& obj2);
    permutation_modified& operator-=(const permutation_modified& obj);
private:
permutation_t permutation;

};


permutation_modified& permutation_modified::operator+=(const permutation_modified& obj)
{
    this->permutation * obj.permutation;
    return *this;
}

permutation_modified operator+(const permutation_modified& obj1, const permutation_modified& obj2)
{
    permutation_modified temp;
    temp += obj1;
    temp += obj2;
    return temp;
}

permutation_modified& permutation_modified::operator-=(const permutation_modified& obj)
{
    this->permutation = obj.permutation.inv() * this->permutation;
    return *this;

}

permutation_modified operator-(const permutation_modified& obj1, const permutation_modified& obj2)
{
    permutation_modified temp;
    temp -= obj1;
    temp -= obj2;
    return temp;
}