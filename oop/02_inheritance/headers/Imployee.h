#pragma once

#include "Person.h"

class Imployee: public Person
{
    private:
    int id;
    public:
    Imployee(const std::string& name_in = "-")
    : _name(name_in)
    {}

    void setName(const std::string& name_in)
    {
        _name = name_in;
    }

    std::string getName()
    {
        return _name;
    }
};