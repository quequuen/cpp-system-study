#pragma once

#include "Person.h"

class Imployee: public Person
{
    private:
    int i_id;

    public:
    Imployee(const std::string& name_in = "-")
    : Person(name_in)
    {}

    friend std::ostream& operator << (std::ostream& out, const Imployee& imployee )
    {
        out << imployee.getName() << " " << imployee.i_id;
        return out;
    }

    
};