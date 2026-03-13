#pragma once

#include <iostream>
#include <string>

class Person
{
    private:
    std::string _name;

    public:
    Person(const std::string& name_in = "-")
        : _name(name_in)
    {}

    void setName(const std::string& name_in)
    {
        _name = name_in;
    }

    std::string getName() const
    {
        return _name;
    }

    void doSomething() const;
    
};